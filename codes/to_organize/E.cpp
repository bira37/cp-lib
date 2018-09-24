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
#define M 998244353
const double PI = acos(-1);

using namespace std;

inline int mod(int n, int m){ int ret = n%m; if(ret < 0) ret += m; return ret; }

int gcd(int a, int b){
  if(a == 0 || b == 0) return 0;
  else return abs(__gcd(a,b));
}

struct ZFunction{

  vector<int> z;
  
  ZFunction() {}
  
  void calculate(string t){
    int n = t.size();
    z.resize(n);
    z[0] = 0;
    int l = 0, r = 0;
    for(int i=1; i<n; i++){
      if(i > r){
        l = i;
        r = i;
      }
      z[i] = min(z[i-l], r-i+1);
      while(i + z[i] < n && t[i + z[i]] == t[z[i]]) z[i]++;
      if(i + z[i] > r){
        l = i;
        r = i + z[i]-1;
      }
    }
  }
  
};

int32_t main(){
  DESYNC;
  string a, l, r;
  cin >> a >> l >> r;
  ZFunction zl, zr;
  zl.calculate(l + a);
  zr.calculate(r + a);
  
  int dp[a.size()+1];
  dp[0] = 1;
  int pref[a.size()+1];
  pref[0] = 1;
  
  int lsz = l.size();
  int rsz = r.size();
  for(int i=0; i<a.size(); i++){
  
    int lo = i - rsz + 1;
    int hi = i - lsz + 1;
    
    //cout << lo << " " << hi << endl;
    
    dp[i+1] = 0;
    
    //check l 
    if(hi >= 0){
      int zhi = zl.z[hi+lsz];
      if(zhi < l.size() && l[zhi] > a[i + zhi]) hi--;
    }
    
    //check r
    if(lo >= 0){
      int zlo = zr.z[lo+rsz];
      if(zlo < r.size() && r[zlo] < a[i + zlo]) lo++;
    }
    
    //cout << "summing from " << lo << " to " << hi << endl;
    if(lo <= hi){
      if(hi >= 0) dp[i+1] += pref[hi];
      if(lo > 0) dp[i+1] -= pref[lo-1];
    }
    if(a[i] == '0' && l == "0") dp[i+1] += dp[i];
    dp[i+1] = mod(dp[i+1] , M);
    //cout << "dp[" << i+1 << "] = " << dp[i+1] << endl;
    if(i+1 < a.size() && a[i+1] != '0') pref[i+1] = pref[i] + dp[i+1];
    else pref[i+1] = pref[i];
    pref[i+1] = mod(pref[i+1], M);
  }
  cout << dp[a.size()] << endl;
}


