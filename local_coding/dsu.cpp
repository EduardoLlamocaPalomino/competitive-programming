
int parent[N], sz[N];
void MakeSet(int u){
  parent[u] = u;
  sz[u] = 1;
}
int Find(int u){
  if (parent[u] == u) return u;
  return parent[u] = Find(parent[u]);
}
void Join(int u, int v){
  u = Find(u);
  v = Find(v);
  if(u != v){
    if(sz[u] > sz[v]) swap(u, v);
    parent[u] = v;
    sz[v] += sz[u];
  }
}
