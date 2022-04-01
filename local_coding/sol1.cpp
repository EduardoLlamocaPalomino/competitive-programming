
// Fear is freedom! Subjugation is liberation! Contradiction is truth!

#include <bits/stdc++.h>
#define endl '\n'

using namespace std;
using Long = long long;
using Double = long double;
using ii = pair<int, int>;

const int INF = 1e9;
const int MOD = 998244353;
const int N = 1e5;
const int LG = 31 - __builtin_clz(N);

/**
 * Description: Barrett reduction computes $a \% b$ about 4 times faster than usual 
 	* where $b>1$ is constant but not known at compile time. Division by $b$ is replaced
 	* by multiplication by $m$ and shifting right 64 bits.
 * Source: KACTL
 	* https://github.com/kth-competitive-programming/kactl/blob/master/content/various/FastMod.h
 	* https://en.wikipedia.org/wiki/Barrett_reduction
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=1045
 */

using ul = uint64_t; using L = __uint128_t;
struct FastMod {
	ul b, m; FastMod(ul b = 1) : b(b), m(-1ULL / b) {}
	ul reduce(ul a) {
		ul q = (ul)((__uint128_t(m) * a) >> 64), r = a - q * b;
		return r - (r >= b) * b; 
  }
} mod;

Long bin_pow(Long bas, int exp){
  Long re = 1LL;
  while(exp > 0){
    if(exp & 1) {
      re *= bas;
      re = mod.reduce(re);
    }
    exp >>= 1;
    bas *= bas;
    bas = mod.reduce(bas);
  }
  return re;
}

int neut = 1;
template<typename T, typename U, typename L>
struct Stree {
  int n, exp;
  struct Node {
    U val; L lazy = neut;
    void assimilate(L upt) {
      if(val != 0) {
        val *= upt;
        val = mod.reduce(val);
      }
      lazy *= upt;
      lazy = mod.reduce(lazy);
    }
  };
  U merge(const U& x, const U& y) {
    if(x == y && x != 0) return x;
    return 0;
  }
  vector<Node> t;
  Stree(const T *pt, int n, int exp) : t(4 * n), n(n), exp(exp) { build(pt, 1, 0, n); }
  void build(const T *pt, int id, int tl, int dr) {
    if(tl + 1 == dr) t[id].val = bin_pow(pt[tl], exp);
    else {
      int md = (tl + dr) >> 1;
      build(pt, 2 * id, tl, md);
      build(pt, 2 * id + 1, md, dr);
      t[id].val = merge(t[2 * id].val, t[2 * id + 1].val);
    }
  }
  void push(int id) {
    if(t[id].lazy == neut) return;
    t[2 * id].assimilate(t[id].lazy);
    t[2 * id + 1].assimilate(t[id].lazy);
    t[id].lazy = neut;
  }
  void update(int l, int r, L upt, int id, int tl, int dr) {
    if(dr <= l || r <= tl) return;
    if(l <= tl && dr <= r) t[id].assimilate(upt);
    else {
      int md = (tl + dr) >> 1;
      push(id);
      update(l, r, upt, 2 * id, tl, md);
      update(l, r, upt, 2 * id + 1, md, dr);
      t[id].val = merge(t[2 * id].val, t[2 * id + 1].val);
    }
  }
  U query(int l, int r, int id, int tl, int dr) {
    if(l <= tl && dr <= r) return t[id].val;
    int md = (tl + dr) >> 1;
    push(id);
    if(r <= md) return query(l, r, 2 * id, tl, md);
    if(md <= l) return query(l, r, 2 * id + 1, md, dr);
    return merge(query(l, r, 2 * id, tl, md), query(l, r, 2 * id + 1, md, dr));
  }
  void update(int l, int r, L upt) { upt = bin_pow(upt, exp); update(l, r, upt, 1, 0, n); }
  U query(int l, int r) { return query(l, r, 1, 0, n); }
};

bool mark[N];
int arr[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int P, n, q;
  cin >> P >> n >> q;
  for(int i = 0; i < n; i++) cin >> arr[i];
  mod = FastMod(P);
  
  vector<int> primes;
  for(int i = 2; i < N; i++) {
    if(mark[i]) continue;
    primes.push_back(i);
    for(int j = i; j < N; j += i) mark[j] = 1;
  }

  vector<ii> deco;
  int gua = P - 1;
  for(int x: primes) {
    int act = 1;
    while(gua % x == 0) {
      act *= x;
      deco.emplace_back(act, x);
      gua /= x;
    }
  }
  if(gua > 1) deco.emplace_back(gua, gua);

  vector<Stree<int, Long, Long>> st;
  for(int i = 0; i < deco.size(); i++) {
    st.emplace_back(arr, n, (P - 1) / deco[i].first);
  }

  while(q--) {
    int t; 
    cin >> t;
    if(t == 1) {
      int l, r, x;
      cin >> l >> r >> x;
      for(auto& it: st) it.update(l - 1, r, x);
    }
    else {
      int l, r; 
      cin >> l >> r;
      int ans = P - 1;
      for(int i = 0; i < deco.size(); i++) {
        if(st[i].query(l - 1, r) == 1) ans /= deco[i].second;
      }
      cout << ans << endl;
    }
  }

  return 0;
}
