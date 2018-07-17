#include <bits/stdc++.h>

#define int long long
#define ff first
#define ss second
#define endl '\n'
#define ii pair<int, int>
#define DESYNC ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define pb push_back
#define vi vector<int>
#define vii vector< ii >
#define EPS 1e-9
#define INF (int)1e9
#define ROOT 1

using namespace std;

inline int mod(int n){ return (n%1000000007); }

int gcd(int a, int b){
  if(a == 0 || b == 0) return 0;
  if(b == 1) return b;
  else return gcd(b, a%b);
}

struct edge{
  int u,v,c;
  edge() {}
  edge(int u, int v, int c) : u(u), v(v), c(c) {}
  bool operator<(const edge & e) const {
	  return c < e.c;
  }
};
vector< ii > adj[112];
int cost[112];
int P[112];
int uf[112];
int L[112];

int find(int u){
  if(uf[u] == u) return u;
  else return uf[u] = find(uf[u]);
}

void merge(int u, int v){
  int a = find(u);
  int b = find(v);
  if(rand()%2) uf[a] = b;
  else uf[b] = a;
}

void dfs(int u, int p){
  for(ii e : adj[u]){
    int v = e.ff;
    int cst = e.ss;
    if(v == p) continue;
    P[v] = u;
    cost[v] = cst;
    L[v] = L[u]+1;
    dfs(v, u);
  }
}

vector<edge> edges;
vector<edge> test;
int32_t main(){
  DESYNC;
	int t;
	cin >> t;
	int tot = t;
	while(t--){
	  int n,m;
	  cin >> n >> m;
	  edges.clear();
	  test.clear();
	  for(int i=0; i<=n; i++){
	    adj[i].clear();
	    uf[i] = i;
	    P[i] = -1;
	  }
	  
	  for(int i=0; i<m; i++){
	    int u,v,c;
	    cin >> u >> v >> c;
	    edges.pb(edge(u,v,c));
	  }
	  sort(edges.begin(), edges.end());
	  int total_cost = 0;
	  int unions = 0;
	  for(edge e : edges){
	    if(find(e.u) == find(e.v)){
	      test.pb(e);
	      continue;
	    }
	    unions++;
	    merge(e.u, e.v);
	    total_cost += e.c;
	    adj[e.u].pb(ii(e.v, e.c));
	    adj[e.v].pb(ii(e.u, e.c));
	  }
	  if(unions != n-1){
	    cout << "Case #" << tot-t << " : No way" << endl;
	    continue;
	  }
	  L[1] = 0;
	  dfs(1, -1);
	  int second_cost = INF;
	  bool second_way = false;
	  for(edge e : test){
	    
	    //try to add another edge and keep same cost
	    int u = e.u, v = e.v;
      int maximum = 0;
      while(u != v){
        if(L[u] < L[v]) swap(u,v);
        maximum = max(maximum, cost[u]);
        u = P[u];
      }
      second_way = true;
      second_cost = min(second_cost, total_cost - maximum + e.c);
    }
    if(second_way) cout << "Case #" << tot-t << " : " << second_cost << endl;
    else cout << "Case #" << tot-t << " : No second way" << endl;  	 
  }   
}


