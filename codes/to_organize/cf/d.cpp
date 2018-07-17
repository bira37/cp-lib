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

int32_t main(){
	DESYNC;
	int n,m;
	cin >> n >> m;
	vector< ii > e;
	if(n-1 > m){
	  cout << "Impossible" << endl;
	  return 0;
	}
	for(int i=1; i<=n; i++){
	  for(int j=i+1; j<=n; j++){
	    if(__gcd(i, j) == 1){
	      e.pb(ii(i,j));
	    }
	    if(e.size() == m){
	      cout << "Possible" << endl;
	      for(int i=0; i<m; i++) cout << e[i].ff << " " << e[i].ss << endl;
	      return 0;
	    }
	  }
	}
	cout << "Impossible" << endl;
}


