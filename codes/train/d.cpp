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

//Graph - Tarjan Bridges Algorithm

//calculate bridges, articulations and all connected components

map<string, int> s_to_id;
map<int, string> id_to_s;
vector<int> adj[112345];

struct Tarjan{
  int cont = 0;
  vector<int> st;
  vector<int> low;
  vector< ii > bridges;
  vector<bool> isArticulation;
  
  Tarjan() {}
  
  Tarjan(int n){
    st.resize(n+1);
    low.resize(n+1);
    isArticulation.resize(n+1);
    cont = 0;
    bridges.clear();
  }
  
  void calculate(int u, int p = -1){
    st[u] = low[u] = ++cont;
    int son = 0;
    for(int i=0; i<adj[u].size(); i++){
      if(adj[u][i]==p){
        p = 0;
        continue;
      }
      if(!st[adj[u][i]]){
        calculate(adj[u][i], u);
        low[u] = min(low[u], low[adj[u][i]]);
        if(low[adj[u][i]] >= st[u]) isArticulation[u] = true; //check articulation

        if(low[adj[u][i]] > st[u]){ //check if its a bridge
          bridges.push_back(ii(u, adj[u][i]));
        }

        son++;
      }
      else low[u] = min(low[u], st[adj[u][i]]);
    }

    if(p == -1){
      if(son > 1) isArticulation[u] = true;
      else isArticulation[u] = false;
    }
  }
};

int32_t main(){
  DESYNC;
  int n;
  int test = 1;
  bool vaitomarnocu  = false;
  while(cin >> n, n != 0){
    if(vaitomarnocu) cout << endl;
    else vaitomarnocu = true;
    s_to_id.clear();
    id_to_s.clear();
    for(int i=0; i<=n; i++) adj[i].clear();
    for(int i=1; i<=n; i++){
      string s;
      cin>> s;
      s_to_id[s] = i;
      id_to_s[i] = s;
    }
    
    int m;
    cin >> m;
    for(int i=0; i<m; i++){
      string a,b;
      cin >> a >> b;
      
      int u = s_to_id[a];
      int v = s_to_id[b];
      adj[u].pb(v);
      adj[v].pb(u);
    }
    
    Tarjan tj(n);
    
    for(int i=1; i<=n; i++){
      if(tj.st[i]) continue; 
      tj.calculate(i);
    }
    
    vector<string> ans;
    for(int i=1; i<=n; i++) if(tj.isArticulation[i]) ans.pb(id_to_s[i]);
    sort(ans.begin(), ans.end());
    cout << "City map #" << test++ << ": " << ans.size() << " camera(s) found" << endl;
    for(int i=0; i<ans.size(); i++){
      cout << ans[i] << endl;
    }
  }        
}


