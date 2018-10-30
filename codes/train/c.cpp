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

int32_t main(){
  DESYNC;
  string s;
  cin >> s;
  int n = s.size();
  int flip1 = -1, flip2 = -1;
  string ret = string(n+1, 'b');
  for(int i=0; i<n; i++){
    if(s[i] != 'a') continue;
    
    string t1, t2;
    t1 = s;
    t2 = s;
    int lastb = -1;
    for(int j=i; j>=0; j--){
      if(lastb == -1 && s[j] == 'b') lastb = j;
    }
    if(lastb != -1) reverse(t1.begin(), t1.begin() + lastb+1);
    reverse(t1.begin(), t1.begin()+i+1);
    reverse(t2.begin(), t2.begin()+i+1);
    if(t1 <= t2 && t1 < ret){
      flip1 = lastb;
      flip2 = i;
    }
    else if(t2 <= t1 && t2 < ret){
      flip1 = -1;
      flip2 = i;
    }
  }
  int ans[n];
  for(int i=0; i<n; i++) ans[i] = 0;
  if(flip1 != -1) ans[flip1] = 1;
  if(flip2 !=  -1) ans[flip2] = 1;
  for(int i=0; i<n; i++) cout << ans[i] << " ";
  cout << endl;
}


