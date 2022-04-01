
struct Hash {
  int P[2] = {1777771, 173}, MOD[2] = {99727999, 1070777777};
  vector<int> h[2], p[2];
  Hash(string& s) {
    for(int i: {0, 1}) h[i] = p[i] = vector<int> (sz(s) + 1, 0);
    for(int i: {0, 1}) {
      p[i][0] = 1;
      for(int j = 1; j <= sz(s); j++) {
        h[i][j] = (1LL * P[i] * h[i][j - 1] + s[j - 1]) % MOD[i];
        p[i][j] = (1LL * p[i][j - 1] * P[i]) % MOD[i];
      }
    }
  }
  Long Query(int l, int r) {
    Long h0 = (1LL * h[0][r] - 1LL * p[0][r - l] * h[0][l]) % MOD[0];
    if(h0 < 0) h0 += MOD[0];
    Long h1 = (1LL * h[1][r] - 1LL * p[1][r - l] * h[1][l]) % MOD[1];
    if(h1 < 0) h1 += MOD[1];
    return (h0 << 32) | h1;
  }
};
