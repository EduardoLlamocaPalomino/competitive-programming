
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
