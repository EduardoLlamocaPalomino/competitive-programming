// añadir 1 vertice a la chull pero no permanentemente
#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0); cin.tie(nullptr)
#define rall(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(v) int(v.size())
#define ss second
#define ff first
#define endl '\n'
using namespace std;

typedef long long Long;
typedef pair<int, int> ii;
const Long INF = 1e17;
const int N = 255e3;

typedef long double ld;
const ld EPS = 1e-9;
const ld PI = acos(-1.0);

struct point { 
  ld x, y;
  point(ld x, ld y) : x(x), y(y) {}
  point() {}
  double norm2() { return *this * *this; }
  double norm() { return sqrt(norm2()); }
  bool operator == (const point& other) const {
    return abs(x - other.x) <= EPS && abs(y - other.y) <= EPS;
  }
  point operator + (const point& other) const {
    return point(x + other.x, y + other.y);
  }
  point operator - (const point& other) const {
    return point(x - other.x, y - other.y);
  }
  point operator * (ld t) const {
    return point(x * t, y * t);
  }
  point operator / (ld t) const {
    return point(x / t, y / t);
  }
  ld operator * (const point& other) const {
    return x * other.x + y * other.y;
  }
  ld operator ^ (const point& other) const { // cross product
    return x * other.y - y * other.x;
  }
  bool operator < (const point& other) const { // for sweep line
    return x < other.x - EPS || (abs(x - other.x) <= EPS && y < other.y - EPS);
  }
  point rotate(point r) {
    return point(*this ^ r, *this * r);
  }
  point rotate(ld ang) {
    return rotate(point(sin(ang), cos(ang)));
  }
};

point ccw90(1, 0);
point cw90(-1, 0);

ld dist2(point p, point q) { // squared distance
  return (p - q).norm2();
}

ld dist(point p, point q) {
  return sqrt(dist2(p, q));
}

ld area2(point a, point b, point c) { // two times signed area of triangle abc
  return (b - a) ^ (c - a);
}

bool left(point a, point b, point c) {
  return area2(a, b, c) > EPS;
}

bool right(point a, point b, point c) {
  return area2(a, b, c) < -EPS;
}

bool collinear(point a, point b, point c) {
  return abs(area2(a, b, c)) < EPS;
}

/* Finds the convex hull of a given set of points. This templates requires
 * the struct point defined in point_integer.cpp or in point_double.cpp
 *
 * p - (input) vector of points for which the convex hull will be found.
 * ch - convex hull of `p` in counter-clockwise order.
 * if chull == line returns lines if chull = point returns empty
 */

vector<point> convexHull(vector<point> p) {
  int n = sz(p);
	sort(p.begin(), p.end());
	vector<point> low, up;
	for(int i = 0; i < n; i++){
    while(sz(up) >= 2 && !right(up[sz(up)-2], up.back(), p[i]))
      up.pop_back();
    up.push_back(p[i]);
    while(sz(low) >= 2 && !left(low[sz(low)-2], low.back(), p[i]))
      low.pop_back();
    low.push_back(p[i]);
	}
  vector<point> ch;
	for(int i = 0; i < sz(low) - 1; i++) ch.push_back(low[i]);
	for(int i = sz(up) - 1; i >= 1; i--) ch.push_back(up[i]);
  return ch;
}

int fol(int ind, int n) { ind++; if(ind >= n) ind -= n; return ind; }

// If positive, the polygon is in ccw order. It is in cw order otherwise.
ld area(vector<point>& p) { // O(n)
  int n = sz(p);
  ld acum = 0;
  for(int i = 0; i < n; i++){
    acum += p[i] ^ p[fol(i, n)];
    // cout << acum << endl;
  }
  return abs(acum);
}

// points in edges are considered inside
bool has(const vector<point>& p, point q) { // O(log n). The polygon must be convex and in ccw order.
  int n = sz(p);
  if(right(p[0], p[1], q) || left(p[0], p[n - 1], q)) return 0;
  int lo = 1, hi = n;
  while(lo + 1 < hi) {
    int mid = (lo + hi) >> 1;
    if(!right(p[0], p[mid], q)) lo = mid;
    else hi = mid;
  }
  return hi != n ? !right(p[lo], p[hi], q) : !right(p[n - 2], p[n - 1], q);
}

ld get_ang(point cen, point bas, point p){
  ld cos = (bas - cen) * (p - cen);
  cos /= ((bas - cen).norm() * (p - cen).norm());
  ld ang = acos(cos);
  ld sen = (bas - cen) ^ (p - cen);
  if(sen < -EPS) ang = PI * 2 - ang;
  return ang;
}

int bin_neg(const vector<point>& chull, int tr, int fl, point q, int n, bool val){
  if(fl < tr) fl += n;
  while(fl - tr > 1){
    int mid = (tr + fl) >> 1;
    if(mid >= n){
      if(left(chull[mid - n], chull[fol(mid - n, n)], q) == val) tr = mid;
      else fl = mid;
    }
    else{
      if(left(chull[mid], chull[fol(mid, n)], q) == val) tr = mid;
      else fl = mid;
    }
  }
  if(fl >= n) fl -= n;
  if(tr >= n) tr -= n;
  if(val) return fl;
  return tr;
}

ld acu[N];

ld conti(const vector<point>& chull, int l, int r){
  ld ori =  acu[r] - acu[l] - area2(chull[0], chull[l], chull[r]);
  return ori;
}


void solve(){
  int n, k; cin >> n >> k;
  vector<point> pol(k);
  for(point& p: pol) cin >> p.x >> p.y;
  vector<point> quer;
  for(int i = 0; i < n - k; i++){
    point p; cin >> p.x >> p.y;
    quer.push_back(p);
  }
  vector<point> chull = convexHull(pol);
  point bar(0, 0);
  for(point p: chull) bar = bar + p;
  int h = sz(chull);
  bar = bar / h;
  ld arch = area(chull);
  acu[0] = 0.0;
  for(int i = 1; i < h; i++) acu[i] = acu[i - 1] + area2(chull[0], chull[i - 1], chull[i]);
  vector<ld> ang(h);
  for(int i = 0; i < h; i++) ang[i] = get_ang(bar, chull[0], chull[i]);
  ld ans = 0.0;
  for(point q: quer){
    if(has(chull, q)) continue;
    ld nang = get_ang(bar, chull[0], q);
    int ne = upper_bound(all(ang), nang) - ang.begin(); ne--;
    nang += PI; if(nang > PI * 2 - EPS) nang -= (PI * 2);
    int po = upper_bound(all(ang), nang) - ang.begin(); po--;
    int neg1 = bin_neg(chull, po, ne, q, h, 1);
    int neg2 = bin_neg(chull, ne, po, q, h, 0);
    int l = neg1, r = fol(neg2, h);
    ld res = conti(chull, min(l, r), max(l, r));
    if(l > r) res = arch - res;
    ans = max(ans, area2(chull[l], q, chull[r]) - res);
  }
  cout << (arch + ans)/2.0 << endl;
}

int main(){
  FAST_IO;
  cout << setprecision(1) << fixed;
  int t = 1;
  // cin >> t;
  while(t--) solve();
  return 0;
}
