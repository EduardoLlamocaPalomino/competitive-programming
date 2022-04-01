
// Fear is freedom! Subjugation is liberation! Contradiction is truth!

#include <bits/stdc++.h>
#define endl '\n'

using namespace std;
using Long = long long;
using Double = long double;
using ii = pair<int, int>;

const Long INF = 1e18;
const int MOD = 998244353;
const int N = 1e6;
const int LG = 31 - __builtin_clz(N);

// In case edge weights are negative, read comments on fix_potential below

struct Mcmf {
  int n;
  priority_queue<pair<Long, int>, vector<pair<Long, int>>, greater<pair<Long, int>>> pq;
  vector<Long> dist, pot, fat, flow;
  struct Edge { 
    Long to, f, cap, cost; 
    Edge(Long to, Long f, Long cap, Long cost) : to(to), f(f), cap(cap), cost(cost) {}
  };
  vector<vector<int>> g;
  vector<Edge> edges;
  Mcmf(int n) : n(n), g(n), dist(n), pot(n), fat(n), flow(n) {}
  void add_edge(int u, int v, Long cap, Long cost){
    g[u].emplace_back(edges.size());
    g[v].emplace_back(edges.size() ^ 1);
    edges.emplace_back(v, 0, cap, cost);
    edges.emplace_back(u, cap, cap, -cost);
  }
  pair<int, Long> get_flow(int s, int t, int amt) {
    int cur_flow = 0;
    Long cost = 0;
    while(cur_flow < amt) {
      fill(dist.begin(), dist.end(), INF);
      pq.emplace(0, s);
      dist[s] = 0;
      flow[s] = amt - cur_flow;
      while(!pq.empty()) {
        auto [d, from] = pq.top();
        pq.pop();
        if(d > dist[from]) continue;
        for(int& i : g[from]) {
          Edge& e = edges[i];
          int to = e.to;
          Long nd = d + e.cost + pot[from] - pot[to];
          if(e.f == e.cap || nd >= dist[to]) continue;
          dist[to] = nd;
          fat[to] = i;
          flow[to] = min(flow[from], e.cap - e.f);
          pq.emplace(nd, to);
        }
      }
      if(dist[t] == INF) break;
      for(int i = 0; i < n; i++) dist[i] += pot[i] - pot[s];
      cost += dist[t] * flow[t];
      cur_flow += flow[t];
      for(int i = t; i != s; i = edges[fat[i] ^ 1].to) {
        edges[fat[i]].f += flow[t];
        edges[fat[i] ^ 1].f -= flow[t];
      }
      dist.swap(pot);
    }
    return {cur_flow, cost};
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;
  vector<int> a(n), b(n);
  for(int& x : a) cin >> x;
  for(int& x : b) cin >> x;

  Mcmf mesh(n + 2);
  for(int i = 0; i < n; i++) {
    mesh.add_edge(0, i + 1, 1, a[i]);
    mesh.add_edge(i + 1, n + 1, 1, b[i]);
    if(i < n - 1) mesh.add_edge(i + 1, i + 2, INF, 0);
  }

  cout << mesh.get_flow(0, n + 1, k).second << endl;

  return 0;
}
