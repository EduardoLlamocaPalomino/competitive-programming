
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

vector<int> ftors;
int arr[N], P;

int bin_pow(Long bas, int exp){
  Long re = 1LL;
  while(exp > 0){
    if(exp & 1) re = (re * bas) % P;
    exp >>= 1;
    bas = (bas * bas) % P;
  }
  return re;
}

int ord(int x) {
  int re = P - 1;
  for(int& p: ftors) {
    while(re % p == 0 && bin_pow(x, re / p) == 1) {
      re /= p;
    }
  }
  return re;
}

int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}

int lcm(int a, int b) {
  int d = gcd(a, b);
  return (a / d) * b;
}

template<typename T, typename U>
struct Stree {
  int n;
  vector<U> t;
  Stree(int n) : n(n), t(4 * n) {}
  Stree(const T *pt, int n) : Stree(n) { if(n) build(pt, 1, 0, n); }
  U merge(const U& x, const U& y) { return lcm(x, y); }
  void build(const T *pt, int id, int tl, int dr) {
    if(tl + 1 == dr) t[id] = ord (pt[tl]);
    else {
      int md = (tl + dr) >> 1;
      build(pt, 2 * id, tl, md);
      build(pt, 2 * id + 1, md, dr);
      t[id] = merge(t[2 * id], t[2 * id + 1]);
    }
  }
  void update(int pos, T val, int id, int tl, int dr) {
    if(tl + 1 == dr) t[id] = ord(val);
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
  void update(int pos, T val) { if(n) update(pos, val, 1, 0, n); }
  U query(int l, int r) { return query(l, r, 1, 0, n); }
};

struct Bit {
  vector<int> t;
  int n;
  Bit(int n) : t(n + 1, 1), n(n) {}
  void update(int i, int x) {
    while(i > 0) {
      t[i] = (1LL * t[i] * x) % P;
      i -= (i & -i);
    }
  }
  int query(int i) {
    Long re = 1LL;
    while(i <= n) {
      re = (re * t[i]) % P;
      i += (i & -i);
    }
    return re;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> P >> n >> q;
  
  int gua = P - 1;
  for(int i = 2; i * i < P; i++) {
    if(gua % i != 0) continue;
    ftors.push_back(i);
    while(gua % i == 0) gua /= i;
  }
  if(gua > 1) ftors.push_back(gua);

  for(int i = 0; i < n; i++) cin >> arr[i];
  vector<int> sal(n - 1);
  for(int i = 0; i < n - 1; i++) {
    sal[i] = (1LL * arr[i + 1] * bin_pow(arr[i], P - 2)) % P;
  }

  Stree<int, int> st(sal.data(), n - 1);
  Bit ft(n + 1);
  int t, l, r, x;
  while(q--) {
    cin >> t >> l >> r;
    l--; r--;
    if(t == 1) {
      cin >> x;
      if(l != 0) {
        sal[l - 1] = (1LL * sal[l - 1] * x) % P;
        st.update(l - 1, sal[l - 1]);
      }
      if(r != n - 1) {
        sal[r] = (1LL * sal[r] * bin_pow(x, P - 2)) % P;
        st.update(r, sal[r]);
      }
      ft.update(r + 1, x);
      ft.update(l, bin_pow(x, P - 2));
    }
    else {
      int ans = ord((1LL * ft.query(l + 1) * arr[l]) % P);
      if(l != r) ans = lcm(ans, st.query(l, r));
      cout << ans << endl;
    }
  }

  return 0;
}
