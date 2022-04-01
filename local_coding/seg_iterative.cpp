
struct Stree {
  vector<int> t;
  int n;
  Stree(const int* pt, int n) : t(n << 1), n(n) { build(pt); }
  void build(const int* pt) {  // build the tree
    for(int i = 0; i < n; i++) t[n + i] = pt[i];
    for(int i = n - 1; i > 0; i--) t[i] = t[i << 1] & t[i << 1 | 1];
  }
  void update(int p, int value) {  // set value at position p
    for(t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = t[p] & t[p ^ 1];
  }
  int query(int l, int r) {  // sum on interval [l, r)
    int res = (1 << 23) - 1;
    for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if(l & 1) res &= t[l++];
      if(r & 1) res &= t[--r];
    }
    return res;
  }
};
