const int MAXN = (1 << 20);
// MAXN must be power of 2 !!
// MOD-1 needs to be a multiple of MAXN !!
// big mod and primitive root for NTT:
typedef Long tf;
typedef vector<tf> poly;
const tf MOD = 998244353, RT = 3;

// FFT
struct CD{
	double r, i;
	CD(double r = 0, double i = 0): r(r), i(i) {}
	double real() const { return r; }
	void operator /=(const int c) { r/=c, i/=c; }
};
CD operator *(const CD& a, const CD& b) { return CD(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r); }
CD operator +(const CD& a, const CD& b) { return CD(a.r + b.r, a.i + b.i); }
CD operator -(const CD& a, const CD& b) { return CD(a.r - b.r, a.i - b.i); }
const double pi = acos(-1.0);

// NTT
/*
struct CD {
	tf x;
	CD(tf x): x(x) {}
	CD() {}
};
tf Add(tf a, tf b) { a += b; if(a >= MOD) a -= MOD; return a; }
tf Sub(tf a, tf b) { a -= b; if(a < 0) a += MOD; return a; }
tf Mul(Long a, Long b) { return ((a * b) % MOD); }
tf pm(tf bas, tf exp){
  tf re = 1;
  while(exp > 0){
    if(exp & 1) re = Mul(re, bas);
    bas = Mul(bas, bas);
    exp >>= 1;
  }
  return re;
}
CD operator* (const CD& a, const CD& b) { return CD(Mul(a.x, b.x)); }
CD operator+ (const CD& a, const CD& b) { return CD(Add(a.x, b.x)); }
CD operator- (const CD& a, const CD& b) { return CD(Sub(a.x, b.x)); }
vector<tf> rts(MAXN + 9, -1);
CD root(int n, bool inv){
	tf r = (rts[n] < 0 ? rts[n] = pm(RT, (MOD - 1)/n): rts[n]);
	return CD(inv ? pm(r, MOD - 2): r);
}
*/

CD cp1[MAXN + 9], cp2[MAXN + 9];
int R[MAXN + 9];
void dft(CD* a, int n, bool inv){
	for(int i = 0; i < n; i++) if(R[i] < i) swap(a[R[i]] ,a[i]);
	for(int m = 2; m <= n; m *= 2){
		double z = 2 * pi/m * (inv ? -1: 1); // FFT
		CD wi = CD(cos(z), sin(z)); // FFT
		// CD wi = root(m, inv); // NTT
		for(int j = 0; j < n; j += m){
			CD w(1);
			for(int k = j, k2 = j + m/2; k2 < j + m; k++, k2++){
				CD u = a[k]; CD v = a[k2] * w; 
        a[k] = u + v; a[k2] = u - v; 
        w = w * wi;
			}
		}
	}
	if(inv) for(int i = 0; i < n; i++) a[i]/=n; // FFT
	/*
  if(inv){ // NTT
		CD z(pm(n, MOD-2)); // pm: modular exponentiation
		for(int i = 0; i < n; i++) a[i] = a[i] * z;
	}
  */
}
poly multiply(poly& p1, poly& p2){
	int n = sz(p1) + sz(p2) + 1;
	int m = 1,cnt = 0;
	while(m <= n) m += m, cnt++;
	for(int i = 0; i < m; i++){ 
    R[i] = 0; 
    for(int j = 0; j < cnt; j++) R[i] = (R[i] << 1) | ((i >> j) & 1);
  }
	for(int i = 0; i < m; i++) cp1[i] = 0, cp2[i] = 0;
	for(int i = 0; i < sz(p1); i++) cp1[i] = p1[i];
	for(int i = 0; i < sz(p2); i++) cp2[i] = p2[i];
	dft(cp1, m, 0); dft(cp2, m, 0);
	for(int i = 0; i < m; i++) cp1[i] = cp1[i] * cp2[i];
	dft(cp1, m, 1);
	poly res;
	n -= 2;
	for(int i = 0; i < n; i++) res.push_back((tf) floor(cp1[i].real() + 0.5)); // FFT
	// for(int i = 0; i < n; i++) res.push_back(cp1[i].x); // NTT
	return res;
}
