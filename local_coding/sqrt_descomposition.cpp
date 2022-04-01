
const int S = sqrt(N) + 1;
struct Sqrt {
  Long t[N];
  Long lazy[S];
  void push(int id) {
    if(lazy[id] == 0) return;
    for(int i = id * S; i < min(N, (id + 1) * S); i++) {
      t[i] += lazy[id];
    }
    lazy[id] = 0;
  }
  void update(int l, int r, int k) {
    int bl = l/S, br = r/S;
    if(bl == br) {
      push(bl);
      for(int i = l; i <= r; i++) t[i] += k;
      return;
    }
    for(int i = bl + 1; i < br; i++) lazy[i] += k;
    push(bl);
    for(int i = l; i < min(N, (bl + 1) * S); i++) t[i] += k;
    push(br);
    for(int i = br * S; i <= min(N - 1, r); i++) t[i] += k;
  }
  Long query(int pos) {
    int bl = pos/S;
    return t[pos] + lazy[bl];
  }
} sq;
