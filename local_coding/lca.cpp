
int fat[N][LG + 1], dep[N];

void lca_init(int root) {
  fat[root][0] = -1;
  dep[root] = 0;
  auto dfs = [&](auto&& dfs, int from) -> void {
    for(int i = 1; i <= LG; i++) {
      if(fat[from][i - 1] == -1) fat[from][i] = -1;
      else fat[from][i] = fat[fat[from][i - 1]][i - 1];
    }
    for(int to: adj[from]) {
      if(to == fat[from][0]) continue;
      dep[to] = dep[from] + 1;
      fat[to][0] = from;
      dfs(dfs, to);
    }
  };
  dfs(dfs, root);
}

int lca(int u, int v) {
  if(dep[u] < dep[v]) swap(u, v);
  for(int i = LG; i >= 0; i--) {
    if(dep[u] - (1 << i) >= dep[v]) u = fat[u][i];
  }
  if(u == v) return u;
  for(int i = LG; i >= 0; i--) {
    if(fat[u][i] != fat[v][i]) {
      u = fat[u][i];
      v = fat[v][i];
    }
  }
  return fat[u][0];
}
