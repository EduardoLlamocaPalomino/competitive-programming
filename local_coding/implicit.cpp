
int neut = INT_MAX;
template<typename U, typename L>
struct Stree {
  int tl, dr;
  U val = U (); L lazy = neut;
  Stree *left = nullptr, *right = nullptr;
  Stree(int tl, int dr) : tl(tl), dr(dr) {}
  void assimilate(L upt){
    val.sum = 1LL * upt * (dr - tl);
    val.mpre = max(val.sum, 0LL);
    lazy = upt;
  }
  static U merge(const U& a, const U& b) {
    return {a.sum + b.sum, max(a.mpre, a.sum + b.mpre)};
  }
  void push(){
    if(!left){
      int md = (tl + dr) >> 1;
      left = new Stree(tl, md);
      right = new Stree(md, dr);
    }
    if(lazy == neut) return;
    left -> assimilate(lazy);
    right -> assimilate(lazy);
    lazy = neut;
  }
  void update(int l, int r, L upt){
    if(dr <= l || r <= tl) return;
    if(l <= tl && dr <= r) assimilate(upt);
    else{
      push();
      left -> update(l, r, upt);
      right -> update(l, r, upt);
      val = merge(left -> val, right -> val);
    }
  }
  U query(int l, int r){
    if(l <= tl && dr <= r) return val;
    push();
    if(r <= right -> tl) return left -> query(l, r);
    if(left -> dr <= l) return right -> query(l, r);
    return merge(left -> query(l, r), right -> query(l, r));
  }
  int lower_bound(int l, int r, const U& cot, U& adv){
    if(dr <= l) return dr;
    if(r <= tl) return tl;
    if(l <= tl && dr <= r){
      if(merge(adv, val).mpre < cot.mpre){
        adv = merge(adv, val);
        return dr;
      }
      if(tl + 1 == dr) return tl;
    }
    push();
    int pos = left -> lower_bound(l, r, cot, adv);
    if(pos < right -> tl) return pos;
    return right -> lower_bound(l, r, cot, adv);
  }
  int lower_bound(int l, int r, const U& cot) { U adv = U (); return lower_bound(l, r, cot, adv); }
};
