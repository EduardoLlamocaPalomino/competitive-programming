/* Basic structure of polygon.
 *
 * This template depends on point_double.cpp since it can work with double coordinates.
 *
 * All operations' time complexity are O(1) unless stated otherwise.
 */

struct polygon {
  vector<point> p;
  int n;
  polygon() : n(0) {}
  polygon(vector<point> _p) {
    p = _p;
    n = sz(p);
  }
  void add(point q) {
    p.push_back(q);
    n++;
  }
  int ind(int i){
    while(i >= n) i -= n;
    return i;
  }
  // If positive, the polygon is in ccw order. It is in cw order otherwise.
  ld orientation() { // O(n)
    ld acum = 0;
    for(int i = 0; i < n; i++)
      acum += p[i] ^ p[ind(i + 1)];
    return acum;
  }
  ld area() { // O(n)
    return abs(orientation()) / 2.0;
  }
  void turnCcw() { // O(n)
    if(orientation() < -EPS)
      reverse(p.begin(), p.end());
  }
  // If already Ccw
  bool convex(){
    for(int i = 0; i < n; i++){
      if(right(p[i], p[ind(i + 1)], p[ind(i + 2)])) return 0;
    }
    return 1;
  }
  // points in edges are considered inside
  bool has(point q) { // O(log n). The polygon must be convex and in ccw order.
    assert(n > 2);
    if(right(p[0], p[1], q) || left(p[0], p[n - 1], q)) return 0;
    int lo = 1, hi = n;
    while(lo + 1 < hi) {
      int mid = (lo + hi) >> 1;
      if(!right(p[0], p[mid], q)) lo = mid;
      else hi = mid;
    }
    return hi != n ? !right(p[lo], p[hi], q) : !right(p[n - 2], p[n - 1], q);
  }
  // not strong tested; is the point inside the polygon ?; points in edges aren't considered inside
  // also only works for integers for now
  bool ray_test(point q){
    int cnt = 0;
    for(int i = 0; i < n; i++){
      point u = p[ind(i + 1)];
      point v = p[i];
      if(u.y < v.y) swap(u, v);
      if((u.y >= q.y && v.y < q.y) && (!right(q, v, u))) cnt++;
    }
    return cnt & 1;
  }
  ld calipers() { // O(n). The polygon must be convex and in ccw order.
    ld ans = 0;
    for(int i = 0, j = 1; i < n; i++) {
      point vec_i = p[ind(i + 1)] - p[i];
      while((vec_i ^ (p[ind(j + 1)] - p[j])) > EPS) 
        j = ind(j + 1);
      ans = max(ans, dist(p[i], p[j])); // Example with polygon diameter
    }
    return ans;
  }
  int extreme(const function<bool(point, point)> &cmp) {
    auto isExtreme = [&](int i, bool& curDir) -> bool {
      curDir = cmp(p[ind(i + 1)], p[i]);
      return !cmp(p[ind(i + n - 1)], p[i]) && !curDir;
    };
    bool lastDir, curDir;
    if(isExtreme(0, lastDir)) return 0;
    int lo = 0, hi = n; 
    while(lo + 1 < hi) {
      int m = (lo + hi) >> 1;
      if(isExtreme(m, curDir)) return m;
      bool relDir = cmp(p[m], p[lo]);
      if((!lastDir && curDir) || (lastDir == curDir && relDir == curDir)) {
          lo = m;
          lastDir = curDir;
      } else hi = m;
    }
    return lo;
  }
  pair<int, int> tangent(point q) { // O(log n) for convex polygon in ccw orientation
    // Finds the indices of the two tangents to an external point q
    auto leftTangent = [&](point r, point s) -> bool {
      return right(q, r, s);
    };
    auto rightTangent = [&](point r, point s) -> bool {
      return left(q, r, s);
    };
    return {extreme(leftTangent), extreme(rightTangent)};
  }
  int maximize(point v) { // O(log n) for convex polygon in ccw orientation
    // Finds the extreme point in the direction of the vector
    return extreme([&](point p, point q) {return p * v > q * v + EPS;});
  }
  void normalize() { // p[0] becomes the lowest leftmost point 
    rotate(p.begin(), min_element(p.begin(), p.end()), p.end());
  }
  polygon operator + (polygon& other) { // Minkowsky sum
    vector<point> sum;
    normalize();
    other.normalize();
    ld dir;
    for(int i = 0, j = 0; i < n || j < other.n; i += dir > -EPS, j = dir < EPS) {
      sum.push_back(p[ind(i)] + other.p[other.ind(j)]);
      dir = (p[ind(i + 1)] - p[ind(i)]) ^ (other.p[other.ind(j + 1)] - other.p[other.ind(j)]);
    }
    return polygon(sum);
  }        
};
