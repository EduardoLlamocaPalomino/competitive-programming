
struct Hash {
  int P = 1753, Q = 1021, MOD = 99727999;
  vector<vector<Long>> h;
  vector<Long> p, q;
  Hash(vector<string>& tab){
    h = vector<vector<Long>> (sz(tab) + 1, vector<Long> (sz(tab[0]) + 1, 0));
    p = vector<Long> (sz(tab) + 1, 1);
    q = vector<Long> (sz(tab[0]) + 1, 1);
    for(int j = 1; j <= sz(tab); j++)  p[j] = p[j - 1] * P % MOD;
    for(int j = 1; j <= sz(tab[0]); j++)  q[j] = q[j - 1] * Q % MOD;
    for(int i = 1; i <= sz(tab); i++){
      for(int j = 1; j <= sz(tab[0]); j++){
        h[i][j] = (h[i - 1][j] * P + h[i][j - 1] * Q - h[i - 1][j - 1] * P * Q + tab[i - 1][j - 1]) % MOD;
        if(h[i][j] < 0) h[i][j] += MOD;
      }
    }
  }
  Long Query(int a, int b, int x, int y){
    Long a1 = h[x][y];
    Long r1 = h[a][y] * p[x - a] % MOD;
    Long r2 = h[x][b] * q[y - b] % MOD; 
    Long a2 = (h[a][b] * p[x - a] % MOD) * q[y - b] % MOD;
    Long re = a1 - r1 - r2 + a2;
    while(re < 0) re += MOD;
    while(re >= MOD) re -= MOD;
    return re;
  }
};
