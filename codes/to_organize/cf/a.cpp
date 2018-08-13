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

char mat[3][1123];
int dp[3][1123][4][2];
bool vis[3][1123][4][2];
int mx;

int solve(int l, int c, int t, int e){
  if(l < 0 || l >= 3) return 0;
  if(c < 0 || c >= mx) return 0;
  if(mat[l][c] == '#') return 0;
  if(l == 0 && c == 0 && t == 2 && e == 0) return 1;
  if(l == 0 && c == 0) return 0;
  if(vis[l][c][t][e]){
    if(dp[l][c][t][e] != -1) return dp[l][c][t][e];
    else return 0;
  }
  vis[l][c][t][e] = true;
  if(t == 0){
    if(e == 0) dp[l][c][t][e] = solve(l-1, c, 1, 1) + solve(l-1, c, 2, 0);
    else dp[l][c][t][e] = solve(l, c+1, 2, 1) + solve(l, c+1, 3, 1);
  }
  else if(t == 1){
    if(e == 0) dp[l][c][t][e] = solve(l+1, c, 0, 1) + solve(l+1, c, 3, 0);
    else dp[l][c][t][e] = solve(l, c+1, 2, 1) + solve(l, c+1, 3, 1);
  }
  else if(t == 2){
    if(e == 0) dp[l][c][t][e] = solve(l, c-1, 1, 0) + solve(l, c-1, 0, 0);
    else dp[l][c][t][e] = solve(l+1, c, 3, 0) + solve(l+1, c, 0, 1);
  }
  else {
    if(e == 0) dp[l][c][t][e] = solve(l, c-1, 0, 0) + solve(l, c-1, 1, 0);
    else dp[l][c][t][e] = solve(l-1, c, 2, 0) + solve(l-1, c, 1, 1);
  }
  dp[l][c][t][e] = mod(dp[l][c][t][e]);
  return dp[l][c][t][e];
}
  

int32_t main(){
	DESYNC;
	int t;
	cin >> t;
	for(int test = 1; test <= t; test++){
	  cout << "Case #" << test << ":";
	  int n;
	  cin >> n;
	  mx = n;
	  for(int i=0; i<3; i++){
	    for(int j = 0; j<n; j++){
	      cin >> mat[i][j];
	      dp[i][j][0][0] = dp[i][j][1][0] = dp[i][j][2][0] = dp[i][j][3][0] = dp[i][j][0][1] = dp[i][j][1][1] = dp[i][j][2][1] = dp[i][j][3][1] = -1;
	      vis[i][j][0][0] = vis[i][j][1][0] = vis[i][j][2][0] = vis[i][j][3][0] = vis[i][j][0][1] = vis[i][j][1][1] = vis[i][j][2][1] = vis[i][j][3][1] = false;
	    }
	  }
	  cout << " " << solve(2, n-1, 0, 0) << endl;
	} 
}


