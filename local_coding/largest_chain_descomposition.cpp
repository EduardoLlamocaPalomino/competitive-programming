 
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
const int MOD = 1e9 + 7;
const int N = 2e4 + 100;
const int LG = 31 - __builtin_clz(N);

vector<int> adj[N], chain[N];
vector<ii> ask[N];
vector<int> head;
int ans[50010];

void pre_dfs(int from, int p = 0) {
  int best = 0;
  for(int to: adj[from]) {
    if(to == p) continue;
    pre_dfs(to, from);
    if(!best || chain[to].size() > chain[best].size()) best = to;
  }
  if(best != 0) swap(chain[from], chain[best]);
  chain[from].push_back(from);
}

void dfs(int from, int p = 0) {
  head.push_back(from);
  // responde queries
  for(ii p: ask[from]) {
    int d = p.ff, id = p.ss;
    if(d >= head.size() && d >= chain[from].size()) ans[id] = 0;
    else if(d < head.size()) ans[id] = head[head.size() - d - 1];
    else ans[id] = chain[from][chain[from].size() - d - 1];
  }
  head.pop_back();

  int big_ch = 0;
  if(chain[from].size() >= 2) big_ch = chain[from][chain[from].size() - 2];
  for(int to: adj[from]) {
    if(to == big_ch || to == p) continue;
    bool flg = (chain[from].size() - 1 > head.size());
    if(flg) {
      chain[from].pop_back();
      swap(head, chain[from]);
    }
    head.push_back(from);
    dfs(to, from);
    head.pop_back();
    if(flg) {
      swap(head, chain[from]);
      chain[from].push_back(from);
    }
  }
  int lit_big = 0;
  for(int to: adj[from]) {
    if(to == big_ch || to == p) continue;
    if(!lit_big || chain[to].size() > chain[lit_big].size()) lit_big = to;
  }
  if(big_ch != 0) {
    chain[from].pop_back();
    swap(chain[big_ch], chain[from]);
    bool flg = (lit_big && chain[lit_big].size() > head.size());
    if(flg) swap(chain[lit_big], head);
    head.push_back(from);
    dfs(big_ch, from);
    head.pop_back();
    if(flg) swap(chain[lit_big], head);
    swap(chain[big_ch], chain[from]);
    chain[from].push_back(from);
  }
}

int main() {
  FAST_IO;
  int n, q; cin >> n >> q;
  for(int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  for(int i = 0; i < q; i++) {
    int u, d; cin >> u >> d;
    ask[u].emplace_back(d, i);
  }
  pre_dfs(1);
  dfs(1);
  for(int i = 0; i < q; i++) cout << ans[i] << endl;
  return 0;
}
