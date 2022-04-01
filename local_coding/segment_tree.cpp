
template<typename T, typename U>
struct Stree {
  int n;
  vector<U> t;
  Stree(int n) : n(n), t(4 * n) {}
  Stree(const T *pt, int n) : Stree(n) { build(pt, 1, 0, n); }
  U merge(const U& x, const U& y) { return x + y; }
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
    if(tl + 1 == dr) t[id] = U (val);
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
  int lower_bound(const U& cot, U& adv, int l, int r, int id, int tl, int dr) {
    if(dr <= l) return dr;
    if(r <= tl) return tl;
    if(l <= tl && dr <= r) {
      if(merge(adv, t[id]) < cot) {
        adv = merge(adv, t[id]);
        return dr;
      }
      if(tl + 1 == dr) return tl;
    }
    int md = (tl + dr) >> 1;
    int pos = lower_bound(cot, adv, l, r, 2 * id, tl, md);
    if(pos < md) return pos;
    return lower_bound(cot, adv, l, r, 2 * id + 1, md, dr);
  }
  int lower_bound(int l, int r, const U& cot) { U adv = U (); return lower_bound(cot, adv, l, r, 1, 0, n); }
  void update(int pos, T val) { return update(pos, val, 1, 0, n); }
  U query(int l, int r) { return query(l, r, 1, 0, n); }
};
