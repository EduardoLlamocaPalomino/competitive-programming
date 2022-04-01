Long Add(Long a, Long b) { a += b; if(a >= MOD) a -= MOD; return a; }
Long Sub(Long a, Long b) { a -= b; if(a < 0) a += MOD; return a; }
Long Mul(Long a, Long b) { return a * b % MOD; }
Long bin_pow(Long bas, Long exp){
  Long re = 1LL;
  while(exp > 0){
    if(exp & 1) re = Mul(re, bas);
    exp >>= 1;
    bas = Mul(bas, bas);
  }
  return re;
}
Long comb(int a, int b){
  if(b > a || b < 0) return 0LL;
  if(b == 0 || b == a) return 1LL;
  Long den = bin_pow(Mul(fact[b], fact[a - b]), MOD - 2);
  Long num = fact[a];
  return Mul(num, den);
}
// calcula fact me da pereza hacerlo ahora, pero cuando lo necesites copia y pega acá
