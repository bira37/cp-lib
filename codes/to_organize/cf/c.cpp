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
	int n,m;
	cin >> n >> m;
	int sum = 0;
	int pos = 0;
	int neg = 0;
	ii q[m];
	for(int i=0; i<m; i++){
	  cin >> q[i].ff >> q[i].ss;
	  sum += q[i].ff;
	  if(q[i].ss > 0) pos+= q[i].ss;
	  else neg += q[i].ss;
	}
	int v[n];
	for(int i=0; i<n; i++) v[i] = sum;
  int fac = 0;
  for(int i=0; i<n; i++){
    v[i] += fac*pos;
    fac++;
  }
	fac = 0;
	for(int i=n/2; i<n; i++){
	  v[i] += fac*neg;
	  fac++;
	}
	fac = 0;
	for(int i=n/2; i>=0; i--){
	  v[i] += fac*neg;
	  fac++;
	}
	int acc = 0;
	for(int i=0; i<n; i++) acc += v[i];
	cout << fixed << setprecision(9) << (double)acc/(double)n << endl;
}


