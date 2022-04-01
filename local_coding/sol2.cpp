
// Fear is freedom! Subjugation is liberation! Contradiction is truth!

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define endl '\n'

using namespace std;
using namespace __gnu_pbds;
using Long = long long;
using Double = long double;
using ii = pair<int, int>;

const int INF = 1e9;
const int MOD = 998244353;
const int N = 1e5;
const int LG = 31 - __builtin_clz(N);

int P;
vector<int> primes;

int Add(int a, int b) { a += b; if(a >= P - 1) a -= (P - 1); return a; }
int Sub(int a, int b) { a -= b; if(a < 0) a += (P - 1); return a; }
int bin_pow(Long bas, int exp){
  Long re = 1LL;
  while(exp > 0){
    if(exp & 1) re = (re * bas) % P;
    exp >>= 1;
    bas = (bas * bas) % P;
  }
  return re;
}

struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    // http://xorshift.di.unimi.it/splitmix64.c
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};

const int B = 300;
struct BSGS {
  int gg, bg;
  gp_hash_table<int, int, custom_hash> gs;
  BSGS(int g) : gg(bin_pow(g, B)), bg(bin_pow(g, P - 2)) {
    Long act = 1;
    for(int i = 0; i * B < P - 1; i++) {
      gs[act] = i;
      act = (act * gg) % P;
    }
  }
  int query(Long a) {
    for(int i = 0; i < B; i++) {
      auto it = gs.find(a);
      if(it != gs.end()) return gs[a] * B  + i;
      a = (a * bg) % P; 
    }
    return -1;
  }
};

int get_root() {
  int gua = P - 1;
  for(int i = 2; i * i < P; i++) {
    if(gua % i != 0) continue;
    primes.push_back(i);
    while(gua % i == 0) gua /= i;
  }
  if(gua > 1) primes.push_back(gua);
  int g = 2;
  while(true) {
    bool flg = 0;
    for(int& p: primes) {
      flg = (bin_pow(g, (P - 1) / p) == 1);
      if(flg) break;
    }
    if(!flg) break;
    g++;
  }
  return g;
}

int gcd(int a, int b) { 
  return b ? gcd(b, a % b) : a; 
}

template<typename T, typename U>
struct Stree {
  int n;
  vector<U> t;
  Stree(int n) : n(n), t(4 * n) {}
  Stree(const T *pt, int n) : Stree(n) { if(n) build(pt, 1, 0, n); }
  U merge(const U& x, const U& y) { return gcd(x, y); }
  void build(const T *pt, int id, int tl, int dr) {
    if(tl + 1 == dr) t[id] = U (pt[tl]);
    else {
      int md = (tl + dr) >> 1;
      build(pt, 2 * id, tl, md);
      build(pt, 2 * id + 1, md, dr);
      t[id] = merge(t[2 * id], t[2 * id + 1]);
    }
  }
  void update(int pos, T val, int id, int tl, int dr) {
    if(tl + 1 == dr) t[id] = Add(t[id], val);
    else {
      int md = (tl + dr) >> 1;
      if(pos < md) update(pos, val, 2 * id, tl, md);
      else update(pos, val, 2 * id + 1, md, dr);
      t[id] = merge(t[2 * id], t[2 * id + 1]);
    }
  }
  U query(int l, int r, int id, int tl, int dr) {
    if(l <= tl && dr <= r) return t[id];
    int md = (tl + dr) >> 1;
    if(md <= l) return query(l, r, 2 * id + 1, md, dr);
    if(r <= md) return query(l, r, 2 * id, tl, md);
    return merge(query(l, r, 2 * id, tl, md), query(l, r, 2 * id + 1, md, dr));
  }
  void update(int pos, T val) { if(n) return update(pos, val, 1, 0, n); }
  U query(int l, int r) { if(n) return query(l, r, 1, 0, n); return 0; }
};

struct Bit {
  vector<int> t;
  int n;
  Bit(int n) : t(n + 1), n(n) {}
  void update(int i, int val) {
    while(i > 0) {
      t[i] = Add(t[i], val);
      i -= (i & -i);
    }
  }
  int query(int i) {
    int re = 0;
    while(i <= n) {
      re = Add(re, t[i]);
      i += (i & -i);
    }
    return re;
  }
};

int arr[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> P >> n >> q;
  for(int i = 0; i < n; i++) cin >> arr[i];
  
  int g = get_root();
  BSGS dis_log(g);
  for(int i = 0; i < n; i++) arr[i] = dis_log.query(arr[i]);
  vector<int> dif(n - 1);
  for(int i = 0; i < n - 1; i++) dif[i] = Sub(arr[i + 1], arr[i]);

  Bit ft(n + 1);
  Stree<int, int> st(dif.data(), n - 1);
  int t, l, r, x;
  while(q--) {
    cin >> t >> l >> r;
    l--; r--;
    if(t == 1) {
      cin >> x;
      x = dis_log.query(x);
      if(l != 0) st.update(l - 1, x);
      if(r != n - 1) st.update(r, Sub(0, x));
      ft.update(r + 1, x);
      ft.update(l, Sub(0, x));
    }
    else {
      int ans = Add(ft.query(l + 1), arr[l]);
      if(l == r) cout << (P - 1) / gcd(P - 1, ans) << endl;
      else {
        ans = gcd(ans, st.query(l, r));
        cout << (P - 1) / gcd(P - 1, ans) << endl;
      }
    }
  }

  return 0;
}
