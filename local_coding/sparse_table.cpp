
const int LG = 31 - __builtin_clz(N);

struct Sparse{
  int tree[N][LG + 1];
  void Build(){
    for(int i = 0; i < n; i++) tree[i][0] = ;
    for(int lg = 1; lg < LG; lg++){
      for(int i = 0; i + (1 << lg) <= n; i++){
        tree[i][lg] = max(tree[i][lg - 1], tree[i + (1 << (lg - 1))][lg - 1]);
      }
    }
  }
  int Query(int l, int r){
    int len = (r - l + 1);
    int lg = 31 - __builtin_clz(len);
    int re = max(tree[l][lg][j], tree[r + 1 - (1 << lg)][lg][j]);
    return re;
  }
} st;
