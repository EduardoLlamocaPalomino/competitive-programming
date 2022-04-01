
Long add[N];

void solve() {
  int n, m;
  cin >> n >> m;
  Stree<Long, Long> st(n);

  map<int, int> inter;
  inter[0] = 1;
  inter[n] = 0;
  auto split = [&](int x) {
    auto it = prev(inter.upper_bound(x));
    inter[x] = it->ss;
  };

  for(int i = 0; i < m; i++) {
    string s; cin >> s;
    if(s[0] == 'C') {
      int l, r, c; cin >> l >> r >> c;
      split(l - 1);
      split(r);
      auto it = inter.lower_bound(l - 1);
      while(it->ff != r) {
        st.update(it->ff, next(it)->ff, add[it->ss] - add[c]);
        it = inter.erase(it);
      }
      inter[l - 1] = c;
    }
    else if(s[0] == 'A') {
      int c, x; cin >> c >> x;
      add[c] += x;
    }
    else {
      int x; cin >> x;
      split(x - 1);
      cout << st.query(x - 1, x) + add[inter[x - 1]] << endl;
    }
  }
}

int main() {
  FAST_IO;
  int t = 1;
  while(t--) solve();
  return 0;
}
