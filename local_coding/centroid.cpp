
bool vis[N];
int szc[N], fac[N];
int lev[N], dist[N][LG + 1];

int calc_sz(int from, int p, int h) {
  szc[from] = 1;
  if(h != - 1) dist[from][h] = dist[p][h] + 1;
  for(int to: adj[from]) {
    if(vis[to] || to == p) continue;
    szc[from] += calc_sz(to, from, h);
  }
  return szc[from];
}

void cen_dfs(int from, int p = -1, int sz = 0) {
  if(!sz) sz = calc_sz(from, p, p == -1 ? -1: lev[p]);
  for(int to: adj[from]) {
    if(vis[to] || szc[to] <= sz / 2) continue;
    szc[from] = 0;
    cen_dfs(to, p, sz);
    return;
  }
  if(p != -1) lev[from] = lev[p] + 1;
  fac[from] = p;
  vis[from] = 1;
  for(int to: adj[from]) if(!vis[to]) cen_dfs(to, from);
}

int lca(int u, int v) {
  if(lev[u] < lev[v]) swap(u, v);
  while(lev[u] > lev[v]) u = fac[u];
  while(u != v) {
    u = fac[u];
    v = fac[v];
  }
  return u;
}

int distance(int u, int v) {
  int w = lca(u, v);
  return dist[u][lev[w]] + dist[v][lev[w]];
}
