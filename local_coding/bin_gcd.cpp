
Long gcd(Long u, Long v) {
  if(u == 0 || v == 0) return u + v;
  int shift = __builtin_ctzll(u | v);
  u >>= __builtin_ctzll(u);
  do {
    v >>= __builtin_ctzll(v);
    if (u > v) swap(u, v);
    v -= u;
  } while (v != 0);
  return u << shift;
}
