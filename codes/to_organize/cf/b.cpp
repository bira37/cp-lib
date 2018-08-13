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
#define INF 1e18
#define ROOT 1

using namespace std;

inline int mod(int n){ return (n%1000000007); }

int gcd(int a, int b){
  if(a == 0 || b == 0) return 0;
  if(b == 1) return b;
  else return gcd(b, a%b);
}

int ll[2123], rr[2123];
vector<int> pre, post;
bool vis[2123];
int label[2123];
int adj[2123];

void pre_order(int x){
  pre.pb(x);
  if(ll[x] != 0) pre_order(ll[x]);
  if(rr[x] != 0) pre_order(rr[x]);
}

void post_order(int x){
  if(ll[x] != 0) post_order(ll[x]);
  if(rr[x] != 0) post_order(rr[x]);
  post.pb(x);
}

int32_t main(){
	DESYNC;
	int t;
	cin >> t;
	for(int test = 1; test <= t; test++){
	  cout << "Case #" << test << ":";
	  int n,k;
	  cin >> n >> k;
	  pre.clear();
	  post.clear();
	  for(int i=1; i<=n; i++){
	    vis[i] = false;
	    cin >> ll[i] >> rr[i];
	  }
	  pre_order(1);
	  post_order(1);
	  for(int i=0; i<pre.size(); i++) adj[pre[i]] = post[i];
	  int cnt = 0;
	  for(int i=1; i<=n; i++){
	    if(vis[i]) continue;
	    int cur = i;
	    cnt++;
	    cnt = min(cnt, k);
	    while(!vis[cur]){
	      vis[cur] = true;
	      label[cur] = cnt;
	      cur = adj[cur];
	    }
	  }
	  int mx = 0;
	  for(int i=1; i<=n; i++) mx = max(mx, label[i]);
	  if(mx != k) cout << " Impossible" << endl;
	  else {
	    for(int i=1; i<=n; i++) cout << " " << label[i];
	    cout << endl;
	  }
	}
}


