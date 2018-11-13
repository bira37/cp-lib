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
  if(a == 0 || b == 0) return 0;
  else return abs(__gcd(a,b));
}

vector< tuple<int,int,int> > g[312345];
vector< ii > ng[312345];
int d[312345];
int dg[312345];
int L[312345];
bool vis[312345];

void dfs(int u){ 
  vis[u] = true;
  for(ii v : ng[u]){
    if(vis[v.ff]) continue;
    L[v.ff] = L[u] + 1;
    dfs(v.ff);
  }
}  

int32_t main(){
  DESYNC;
  int n,m,k;
  cin >> n >> m >> k;
  for(int i=0; i<=n; i++) d[i] = (int)1e16;
  for(int i=0; i<m; i++){
    int u,v,c;
    cin >> u >> v >> c;
    g[u].pb(mt(v,c, i+1));
    g[v].pb(mt(u,c, i+1));
  }
  
  set< tuple<int,int> > s;
  d[1] = 0;
  s.insert(mt(d[1], 1));
  while(!s.empty()){
    int u,dst;
    tie(dst,u) = *s.  begin();
    s.erase(s.begin());
    if(d[u] != dst) continue;
    for(auto v : g[u]){
      int ad, id, dst;
      tie(ad, dst, id) = v;
      if(d[u] + dst < d[ad]){
        d[ad] = dst + d[u];
        s.insert(mt(d[ad], ad));
      }
    }
  }
  
  bool keep[m+1];
  for(int i=0; i<=m; i++) keep[i] = false;
  int cnt = 0;
  for(int u =1; u<=n; u++){
    for(auto v : g[u]){
      int ad, id, dst;
      tie(ad, dst, id) = v;
      if(d[ad] == d[u] + dst){
        keep[id] = true;
        cnt++;
        ng[ad].pb(ii(u, id));
        dg[u]++;
      }
    }
  }
  
  for(int i=1; i<=n; i++){
    if(dg[i] > 0) continue;
    L[i] = 0;
    dfs(i);
  }
  
  set< tuple<int,int,int> > s2;
  for(int i=1; i<=n; i++){
    if(ng[i].size() == 0) continue;
    s2.insert(mt(-ng[i].size(), L[i], i));
  }
  while(!s2.empty() && cnt > k){
    int ad, l, u;
    tie(ad, l, u) = *s2.begin(); 
    s2.erase(s2.begin());
    int mark = ng[u][ng[u].size() + ad].ss;
    ad++;
    keep[mark] = false;
    cnt--;
    if(ng[u].size() + ad == 0) continue;       
    s2.insert(mt(ad, L[u], u));
  }
  cout << cnt << endl;
  for(int i=1; i<=m; i++) if(keep[i]) cout << i << " ";
  cout << endl;
}


