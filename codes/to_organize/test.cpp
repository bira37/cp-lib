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

int32_t main(){
	DESYNC;
	int n;
	cin >> n;
	set<int, greater<int> >s;
	for(int i=0; i<n; i++){
	    int x;
	    cin >> x;
	    if(s.count(x)) s.erase(s.find(x));
	    else s.insert(x);
	}
	set<int> q;
	for(int x : s){
	    if(x%2 == 0) q.insert(x);
	}
	for(int x : q) s.erase(s.find(x));
	vector< ii > ans;
	vector<int> v;
	for(int x : s) v.pb(x);
	vector<bool> vis(v.size());
	for(int i=0; i<v.size(); i++) vis[i] = false;
	for(int i=0; i<v.size(); i++){
	  if(vis[i]) continue;
	  for(int j=i+1; j<v.size(); j++){
	    if(vis[j]) continue;
	    if(q.count(v[i] - v[j])){
	      vis[i] = true;
	      vis[j] = true;
	      q.erase(q.find(v[i] - v[j]));
	      ans.pb(ii(v[i], v[i]-v[j]));
	      break;
	    }
	  }
	}
	int sum = 0;
	for(bool x : vis) sum += x;
	if(sum < s.size()){
	    cout << -1 << endl;
	    return 0;
	}
  for(int x : q){
    ans.pb(ii(x, x/2));
  }
  cout << ans.size() << endl;
  for(ii x : ans) cout << x.ff << " " << x.ss << endl;
}
