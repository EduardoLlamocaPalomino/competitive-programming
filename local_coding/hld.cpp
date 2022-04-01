
int sz[N], dep[N], fat[N], tin[N], head[N];

void hld_init(int root) {
  fat[root] = -1;
  dep[root] = 0;
  auto dfs = [&](auto&& dfs, int from) -> void {
    for(int to: adj[from]) {
      if(to == fat[from]) continue;
      dep[to] = dep[from] + 1;
      fat[to] = from;
      dfs(dfs, to);
      sz[from] += sz[to];
    }
  };
  dfs(dfs, root);
  int cur_pos = 0;
  auto hld = [&](auto&& hld, int from, int prog) -> void {
    tin[from] = cur_pos++;
    head[from] = prog;
    int big_ch = -1;
    for(int to: adj[from]) {
      if(to == fat[from]) continue;
      if(big_ch < 0 || sz[big_ch] < sz[to]) big_ch = to;
    }
    if(big_ch >= 0) hld(hld, big_ch, prog);
    for(int to: adj[from]) {
      if(to == fat[from] || to == big_ch) continue;
      hld(hld, to, to);
    }
  };
  hld(hld, root, root);
}

int query(int u, int v, Stree<int, int>& st) {
  int re = 0;
  while(head[u] != head[v]) {
    if(dep[head[u]] < dep[head[v]]) swap(u, v);
    re = re + st.query(tin[head[u]], tin[u] + 1);
    u = fat[head[u]];
  }
  if(dep[u] < dep[v]) swap(u, v);
  re = re + st.query(tin[v], tin[u] + 1);
  return re;
}

// when querying edges: if(u != v) query(tin[v] + 1, tin[u] + 1)
