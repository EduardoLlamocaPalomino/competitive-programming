
int neut = 0;
template<typename U, typename L>
struct Stree {
  struct Node {
    U val; L lazy = neut; int tl, dr;
    void assimilate(L upt) {
      val += upt;
      lazy += upt;
    }
  };
  U merge(const U& x, const U& y) { return max(x, y); }
  vector<Node> t;
  Stree(int n) : t(4 * n) { build(1, 0, n); }
  // Stree(const T *pt, int n) : t(4 * n) { build(pt, 1, 0, n); }
  void build(int id, int tl, int dr) {
    t[id].tl = tl, t[id].dr = dr;
    if(tl + 1 == dr) /*t[id].val = U (pt[tl])*/; 
    else {
      int md = (tl + dr) >> 1;
      build(2 * id, tl, md);
      build(2 * id + 1, md, dr);
      t[id].val = merge(t[2 * id].val, t[2 * id + 1].val);
    }
  }
  void push(int id) {
    if(t[id].lazy == neut) return;
    t[2 * id].assimilate(t[id].lazy);
    t[2 * id + 1].assimilate(t[id].lazy);
    t[id].lazy = neut;
  }
  void update(int l, int r, L upt, int id) {
    if(t[id].dr <= l || r <= t[id].tl) return;
    if(l <= t[id].tl && t[id].dr <= r) t[id].assimilate(upt);
    else {
      push(id);
      update(l, r, upt, 2 * id);
      update(l, r, upt, 2 * id + 1);
      t[id].val = merge(t[2 * id].val, t[2 * id + 1].val);
    }
  }
  U query(int l, int r, int id) {
    if(l <= t[id].tl && t[id].dr <= r) return t[id].val;
    push(id);
    if(r <= t[2 * id + 1].tl) return query(l, r, 2 * id);
    if(t[2 * id].dr <= l) return query(l, r, 2 * id + 1);
    return merge(query(l, r, 2 * id), query(l, r, 2 * id + 1));
  }
  int lower_bound(int l, int r, const U& cot, U& adv, int id) {
    if(t[id].dr <= l) return t[id].dr;
    if(r <= t[id].tl) return t[id].tl;
    if(l <= t[id].tl && t[id].dr <= r) {
      if(merge(adv, t[id].val) < cot) {
        adv = merge(adv, t[id].val);
        return t[id].dr;
      }
      if(t[id].tl + 1 == t[id].dr) return t[id].tl;
    }
    push(id);
    int pos = lower_bound(l, r, cot, adv, 2 * id);
    if(pos < t[2 * id + 1].tl) return pos;
    return lower_bound(l, r, cot, adv, 2 * id + 1);
  }
  void update(int l, int r, L upt) { update(l, r, upt, 1); }
  U query(int l, int r) { return query(l, r, 1); }
  int lower_bound(int l, int r, const U& cot) { U adv = U (); return lower_bound(l, r, cot, adv, 1); }
};
