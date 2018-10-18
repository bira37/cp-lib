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

vector<int> adj[312345];
vector<bool> adjc[312345];
bool vis[312345][2] = {0};

int32_t main(){
  DESYNC;
  int n, m;
  cin >> n >> m;
  for(int i=0; i<m; i++){
    int u,v,c;
    cin >> u >> v >> c;
    adj[u].pb(v);
    adj[v].pb(u);
    adjc[u].pb(c);
    adjc[v].pb(c);
  }
  
  int s,t;
  cin >> s >> t;
  stack< ii > q;
  vis[s][0] = 0;
  q.push(ii(s, 0));
  while(!q.empty()){
    int u = q.top().ff;
    bool art = q.top().ss;
    
    q.pop();
    
    for(int i=0; i<adj[u].size(); i++){
      int v = adj[u][i];
      bool c = adjc[u][i];
      c |= art;
      if(vis[v][c]) continue;
      vis[v][c] = true;
      q.push(ii(v,c));
    }
  }
  if(vis[t][1]) cout << "YES" << endl;
  else cout << "NO" << endl;       
}


