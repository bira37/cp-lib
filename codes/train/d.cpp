#include <bits/stdc++.h>

#define int long long
#define double long double
#define ff first
#define ss second
#define endl '\n'
#define ii pair<int, int>
#define mp make_pair
#define mt make_tuple
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
  if(a == 0) return b;
  else return gcd(b%a, a);
}

vector<int> adj[112345];
vector<int> loop(112345, false);
vector<int> vis(112345, 0);
vector<int> g(112345);

bool ok = false;
vector<int> st;

void dfs(int u){
  vis[u] = 1;
  st.pb(u);
  for(int v : adj[u]){
    if(vis[v] == 2) continue;
    if(vis[v] == 1){
      bool valid = false;
      bool has_loop = false;
      if(g[v] > 0) valid = true;
      if(loop[v]) has_loop = true;
      while(st.size() > 0 && st.back() != v){
        if(g[st.back()] > 0) valid = true;
        if(loop[st.back()]) has_loop = true;
        st.pop_back();
      }
      if(valid && has_loop) ok = true;
    }
    if(vis[v] == 0) dfs(v);
  }
  if(st.back() == u) st.pop_back();
  vis[u] = 2;
}

void calc(int u){
  vis[u] = 1;
  for(int v : adj[u]){
    if(vis[v] != 0) continue;
    calc(v);
    g[u] += g[v];
  }
  if(loop[u] && g[u] > 0) ok = true;
}

void solve(){
  int n;
  cin >> n;
  for(int i=1; i<=n; i++){
    vis[i] = 0;
    loop[i] = false;
    adj[i].clear();
  }
  ok = false;
  st.clear();
  for(int i=1; i<=n; i++){
    int a,b;
    cin >> a >> b;
    if(a == i){
      loop[i] = true;
    }
    else adj[a].pb(i);
    if(b == i){
      loop[i] = true;
    }
    else adj[b].pb(i);
  }
  for(int i=1; i<=n; i++) cin >> g[i];
  dfs(1);
  if(ok){
    cout << "UNBOUNDED" << endl;
    return;
  }
  for(int i=1; i<=n; i++){
    vis[i] = 0;
  }
  calc(1);
  if(ok){
    cout << "UNBOUNDED" << endl;
    return;
  }
  cout << g[1] << endl; 
}

int32_t main(){
  DESYNC;
  int t;
  cin >> t;
  int tt = 1;
  while(t--){
    cout << "Case #" << tt++ << ": ";
    solve();
  }
}


