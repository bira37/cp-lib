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

struct edges {
  int u, v, weight;
  edges(int u , int v, int weight) :
  u(u),
  v(v),
  weight(weight) {}
};

vector< edges > e;

struct BellmanFord{

  vector<int> dist;
  
  bool cycle = false;
  
  BellmanFord(){}
  
  BellmanFord(int n){
    dist.resize(n+1);
  }

  void calculate(int source){
    for(int i=0; i<dist.size(); i++){
      dist[i] = INF;
    }
    dist[source] = 0;
    for(int k=0; k<dist.size()-1; k++){
      for(int i=0; i<e.size(); i++){
        if(dist[e[i].v] > dist[e[i].u] + e[i].weight){
          dist[e[i].v] = dist[e[i].u] + e[i].weight;
        }
      }
    }
    for(int i=0; i<e.size(); i++){
      if(dist[e[i].v] > dist[e[i].u] + e[i].weight){
        cycle = true;
      }
    }
  }
  
};

int32_t main(){
  DESYNC;
  int t;
  cin >> t;
  while(t--){
    int n,m;
    cin >> n >> m;
    BellmanFord bf(n);
    e.clear();
    for(int i=0; i<m; i++){
      int u,v,c;
      cin >> u >> v >> c;
      u++, v++;
      e.pb(edges(u,v,c));
    }
    bf.calculate(1);
    if(bf.cycle) cout << "possible" << endl;
    else cout << "not possible" << endl;
  }
}
