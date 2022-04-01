struct Edge { int to, rev; Long flow, cap; };

struct Dinic {
  int nodes, src, dst;
  vector<int> dist, q, work;
  vector<vector<Edge>> g;
  Dinic(int x) : nodes(x), g(x), dist(x), q(x), work(x) {}
  void add_edge(int s, int t, Long cap) {
    g[s].push_back((Edge) {t, g[t].size(), 0, cap});
    g[t].push_back((Edge) {s, g[s].size() - 1, 0, 0});
  }
  bool dinic_bfs(){
    fill(dist.begin(), dist.end(), -1);
    dist[src] = 0;
    int qt = 0; q[qt++] = src;
    for(int qh = 0; qh < qt; qh++) {
      int u = q[qh];
      for(int i = 0; i < sz(g[u]); i++) {
        Edge &e = g[u][i]; int v = g[u][i].to;
        if(dist[v] < 0 && e.flow < e.cap)
          dist[v] = dist[u] + 1, q[qt++] = v;
      }
    }
    return dist[dst] >= 0;
  }
  Long dinic_dfs(int u, Long f) {
    if(u == dst) return f;
    for(int &i = work[u]; i < sz(g[u]); i++) {
      Edge &e = g[u][i];
      if(e.cap <= e.flow) continue;
      int v = e.to;
      if(dist[v] == dist[u] + 1) {
        Long df = dinic_dfs(v, min(f, e.cap - e.flow));
        if(df > 0) { 
          e.flow += df; 
          g[v][e.rev].flow -= df; 
          return df;
        }
      }
    }
    return 0;
  }
  Long max_flow(int _src, int _dst) {
    src = _src; dst = _dst;
    Long result = 0;
    while(dinic_bfs()) {
      fill(work.begin(), work.end(), 0);
      while(Long delta = dinic_dfs(src, INF)) result += delta;
    }
    return result;
  }
};
// General: O(E * V^2), Unit Cap: O(E * min(E^(1/2) , V^(2/3))), Unit Network: O(E * V^(1/2))
// unit network is a network in which all the edges have unit capacity,
// and for any vertex except s and t either incoming or outgoing edge is unique.
