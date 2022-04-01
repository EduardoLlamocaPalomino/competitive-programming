
 
// Fear is freedom! Subjugation is liberation! Contradiction is truth!
 
#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0); cin.tie(nullptr)
#define rall(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(v) int(v.size())
#define ss second
#define ff first
#define endl '\n'
using namespace std;
using Long = long long;
using ii = pair<int, int>;
using Real = long double;
const int INF = 1e9;
const int MOD = 1e9 + 9;
const int N = 1.8e4;
const int LG = 31 - __builtin_clz(N);

int main() {
  FAST_IO;
  int n; cin >> n;
  while(n != -1) {
    cout << (n & -n) << endl;
    cin >> n;
  }
  return 0;
}
