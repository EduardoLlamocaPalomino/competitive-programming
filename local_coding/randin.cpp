
#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0); cin.tie(nullptr)
#define rall(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define sz(v) int(v.size())
#define ss second
#define ff first
#define endl '\n'
using namespace std;
typedef long long Long;
typedef pair<int, int> ii;
const Long INF = 1e17;
const int N = 1e6;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b){ return uniform_int_distribution<Long> (a, b) (rng); }

int main(){
  FAST_IO;
  int n = random(1, 1e4);
  cout << n << endl;
  for(int i = 0; i < n; i++) cout << random(1, 1e6) << " ";
  cout << endl;
  return 0;
}
