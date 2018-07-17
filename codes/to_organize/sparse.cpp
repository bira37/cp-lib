#include <bits/stdc++.h>

#define ff first
#define ss second
#define endl '\n'
#define ii pair<int, int>
#define DESYNC ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define pb push_back
#define vi vector<int>
#define vii vector< ii >
#define EPS 1e-9
#define INF (int)2e9
#define ROOT 1

using namespace std;

inline int mod(int n){ return (n%1000000007); }

int gcd(int a, int b){
  if(a == 0 || b == 0) return 0;
  if(b == 1) return b;
  else return gcd(b, a%b);
}
int v[112345];
int sp[22][112345];

int32_t main(){
  DESYNC;
  int t;
  cin >> t;
  int scen = 0;
  while(t--){
    cout << "Scenario #" << ++scen << ": " << endl;
    int n,q;
    cin >> n >> q;
    for(int i=0; i<22; i++){
      for(int j=0; j<n; j++) sp[i][j] = INF;
    }
    for(int i=0; i<n; i++){
      cin >> v[i];
    }
    for(int i=0; i<n; i++){
      sp[0][i] = v[i];
    }
    for(int p=1; p<=21; p++){
      for(int i = 0; i<n; i++){
        int nxt = i + (1<<(p-1))-1;
        nxt = min(nxt, n-1);
        sp[p][i] = min(sp[p-1][i], sp[p-1][nxt]);
        //cout << "min from " << i << " to " << nxt << " is " << sp[p][i] << endl;
      }
    }
    while(q--){
      int l, r;
      cin >> l >> r;
      l--, r--;
      if(l > r) swap(l, r);
      int ans = INF;
      int step = log2(r-l+1);
      cout << "step " << step << " " << endl;
      cout << "l " << l << " r " << l + (1<<step) -1 << endl;
      ans = min(ans, sp[step][l]);
      int offset = (1<<step);
      l = r - offset + 1;
      cout << "new l " << l << " " << "new r " << l + offset-1 << endl;
      ans = min(ans, sp[step][l]);
      cout << ans << endl;
    }
  }
} 


