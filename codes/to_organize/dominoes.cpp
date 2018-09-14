#include <bits/stdc++.h>

#define int long long
#define double long double
#define ff first
#define ss second
#define endl '\n'
#define ii pair<int, int>
#define DESYNC ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define pb push_back
#define vi vector<int>
#define vii vector< ii >
#define EPS 1e-9
#define INF 1e18
#define ROOT 1
#define M 1000000007
const double PI = acos(-1);

using namespace std;

inline int mod(int n, int m){ int ret = n%m; if(ret < 0) ret += m; return ret; }

int gcd(int a, int b){
  if(a == 0 || b == 0) return 0;
  else return abs(__gcd(a,b));
}

struct Dinic {

  struct FlowEdge{
    int v, rev, c, cap;
    FlowEdge() {}
    FlowEdge(int v, int c, int cap, int rev) : v(v), c(c), cap(cap), rev(rev) {}
  };
  
  vector< vector<FlowEdge> >  adj;
  vector<int> level, used;
  int src, snk;
  int sz;
  int max_flow;
  Dinic(){}
  Dinic(int n){
    src = 0;
    snk = n+1;
    adj.resize(n+2, vector< FlowEdge >());
    level.resize(n+2);
    used.resize(n+2);
    sz = n+2;
    max_flow = 0;
  }
  
  void add_edge(int u, int v, int c){
    int id1 = adj[u].size();
    int id2 = adj[v].size();
    adj[u].pb(FlowEdge(v, c, c, id2));
    adj[v].pb(FlowEdge(u, 0, 0, id1));
  }
  
  void add_to_src(int v, int c){
    adj[src].pb(FlowEdge(v, c, c, -1));
  }
  
  void add_to_snk(int u, int c){
    adj[u].pb(FlowEdge(snk, c, c, -1));
  }
  
  bool bfs(){
    for(int i=0; i<sz; i++){
      level[i] = -1;
    }
    
    level[src] = 0;
    queue<int> q; q.push(src);
    
    while(!q.empty()){
      int cur = q.front();
      q.pop();
      for(FlowEdge e : adj[cur]){
        if(level[e.v] == -1 && e.c > 0){
          level[e.v] = level[cur]+1;
          q.push(e.v);
        }
      }
    }
    
    return (level[snk] == -1 ? false : true);
  }
  
  int send_flow(int u, int flow){
    if(u == snk) return flow;
    
    for(int &i = used[u]; i<adj[u].size(); i++){
      FlowEdge &e = adj[u][i];
      
      if(level[u]+1 != level[e.v] || e.c <= 0) continue;
      
      int new_flow = min(flow, e.c);
      int adjusted_flow = send_flow(e.v, new_flow);
      
      if(adjusted_flow > 0){
        e.c -= adjusted_flow;
        if(e.rev != -1) adj[e.v][e.rev].c += adjusted_flow;
        return adjusted_flow;
      }
    }
    
    return 0;
  }
  
  void calculate(){
    if(src == snk){max_flow = -1; return;} //not sure if needed
    
    max_flow = 0;
    
    while(bfs()){
      for(int i=0; i<sz; i++) used[i] = 0;
      while(int inc = send_flow(src, INF)) max_flow += inc;
    }
    
  }
  
  vector< ii > mincut(){
    bool vis[sz];
    for(int i=0; i<sz; i++) vis[i] = false;
    queue<int> q;
    q.push(src);
    vis[src] = true;
    while(!q.empty()){
      int cur = q.front();
      q.pop();
      for(FlowEdge e : adj[cur]){
        if(e.c > 0 && !vis[e.v]){
          q.push(e.v);
          vis[e.v] = true;
        }
      }
    }
    vector< ii > cut;
    for(int i=1; i<=sz-2; i++){
      if(!vis[i]) continue;
      for(FlowEdge e : adj[i]){
        if(1 <= e.v && e.v <= sz-2 && !vis[e.v] && e.cap > 0 && e.c == 0) cut.pb(ii(i, e.v));
      }
    }
    return cut;
  }
  
};

int n;
int dx[] = {0,1,0,-1};
int dy[] = {1, 0, -1, 0};

int f(int x, int y){
  return (x-1)*n + y;
}

int32_t main(){
  DESYNC;
  int k;
  cin >> n >> k;
  if(n == 1){
    cout << "No" << endl;
    return 0;
  }
  set< ii > s;
  Dinic dinic(n*n + n*n);
  for(int i=1; i<=n; i++){
    for(int j=1; j<=n; j++){
      s.insert(ii(i,j));
    }
  }
  for(int i=0; i<k; i++){
    int x,y;
    cin >> x >> y;
    s.erase(s.find(ii(x,y)));
  }
  
  for(ii x : s){
    dinic.add_to_src(f(x.ff, x.ss), INF);
    dinic.add_to_snk(f(x.ff,x.ss) + n*n, INF);
    dinic.add_edge(f(x.ff, x.ss), f(x.ff,x.ss) + n*n, 1);
    for(int i = 0; i<4; i++){
      int nx = dx[i] + x.ff;
      int ny = dy[i] + x.ss;
      if(!s.count(ii(nx,ny))) continue;
      dinic.add_edge(f(x.ff,x.ss) + n*n, f(nx,ny), INF);
    }
  }
  
  dinic.calculate();
  
  if(dinic.max_flow != s.size()){
    cout << "No" << endl;
    return 0;
  }
  
  set< ii > used;
  set< ii > ver, hor;
  for(int i=1; i<=n; i++){
    for(int j=1; j<=n; j++){
      for(Dinic::FlowEdge e : dinic.adj[f(i,j)]){
        if(e.v != f(i,j) + n*n) continue;
        if(e.cap - e.c == 1) used.insert(ii(i,j));
      }
    }
  }
  set< ii > vis;
  for(ii x : used){
    if(vis.count(x)) continue;
    int nx = x.ff + 1;
    int ny = x.ss;
    if(used.count(ii(nx,ny)) && !vis.count(ii(nx,ny))){
      ver.insert(x);
      vis.insert(x); vis.insert(ii(nx,ny));
      continue;
    }
    nx = x.ff;
    ny = x.ss+1;
    if(used.count(ii(nx,ny)) && !vis.count(ii(nx,ny))){
      hor.insert(x);
      vis.insert(x); vis.insert(ii(nx,ny));
      continue;
    }
  }
  if(2*(ver.size() + hor.size()) != dinic.max_flow){
    cout << "No" << endl;
    return 0;
  }
  cout << "Yes" << endl; 
  cout << ver.size() << endl;
  for(ii x : ver) cout << x.ff << " " << x.ss << endl;
  cout << hor.size() << endl;
  for(ii x : hor) cout << x.ff << " " << x.ss << endl;            
}


