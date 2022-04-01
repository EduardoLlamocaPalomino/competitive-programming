#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0); cin.tie(nullptr)
#define rall(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define ss second
#define ff first
#define endl '\n'
using namespace std;
typedef long long Long;
typedef pair<int, int> ii;
const int INF = 1e6;

struct Edge{
  int from, to, cap, flow, index;
  Edge(int from, int to, int cap, int flow, int index) :
    from(from), to(to), cap(cap), flow (flow), index(index) {}
};

struct PushRelabel{
  int N;
  vector<vector<Edge>> G;
  vector<Long> excess;
  vector<int> dist, active, count;
  queue<int> Q;
  PushRelabel(int N) : N(N), G(N), excess(N), dist(N), active(N), count(2*N), bip(N) {}
  void Add_Edge(int from, int to, int cap){
    G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
    if(from == to) G[from].back().index++;
    G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
  }
  void Enqueue(int v){
    if(!active[v] && excess[v] > 0){
      active[v] = true;
      Q.push(v);
    }
  }
  void Push(Edge &e){
    int amt = int(min(excess[e.from], (Long) e.cap - e.flow));
    if(dist[e.from] <= dist[e.to] || amt == 0) return;
    e.flow += amt;
    G[e.to][e.index].flow -= amt;
    excess[e.to] += amt;
    excess[e.from] -= amt;
    Enqueue(e.to);
  }
  void Gap(int k){
    for(int v = 0; v < N; v++){
      if(dist[v] < k) continue;
      count[dist[v]]--;
      dist[v] = max(dist[v], N+1);
      count[dist[v]]++;
      Enqueue(v);
    }
  }
  void Relabel(int v){
    count[dist[v]]--;
    dist[v] = 2 * N;
    for(int i = 0; i < G[v].size(); i++)
      if(G[v][i].cap - G[v][i].flow > 0)
        dist[v] = min(dist[v], dist[G[v][i].to] + 1);
    count[dist[v]]++;
    Enqueue(v);
  }
  void Discharge(int v){
    for(int i = 0; excess[v] > 0 && i < G[v].size(); i++)
      Push(G[v][i]);
    if(excess[v] > 0){
      if(count[dist[v]] == 1) Gap(dist[v]);
      else Relabel(v);
    }
  }
  Long Max_Flow(int s, int t){
    count[0] = N-1;
    count[N] = 1;
    dist[s] = N;
    active[s] = active[t] = 1;
    for(int i = 0; i < G[s].size(); i++){
      excess[s] += G[s][i].cap;
      Push(G[s][i]);
    }
    while(!Q.empty()){
      int v = Q.front();
      Q.pop();
      active[v] = 0;
      Discharge(v);
    }
    Long totflow = 0;
    for(int i = 0; i < G[s].size(); i++) totflow += G[s][i].flow;
    return totflow;
  }
};

void solve(int n, int m){
  PushRelabel net(n + 1);
  vector<ii> edges;
  for(int i = 0; i < m; i++){
    int u, v, w; cin >> u >> v >> w;
    edges.push_back({u, v});
    net.Add_Edge(u, v, w);
    net.Add_Edge(v, u, w);
  }
  Long cut = net.Max_Flow(1, 2);
  net.dfs(1, 1);
  net.dfs(2, 2);
  for(ii par: edges){
    int u = par.ff; int v = par.ss;
    if(net.bip[u] == net.bip[v]) continue;
    cout << u << " " << v << endl;
  }
  cout << endl;
}

int main(){
  FAST_IO;
  int n, m;
  while(1){
    cin >> n >> m;
    if(n == 0 && m == 0) return 0;
    solve(n, m);
  }
  return 0;
}

