#include <bits/stdc++.h>

#define int long long
#define double long double
#define ff first
#define ss second
#define endl '\n'
#define ii pair<int, int>
#define mp make_tuple
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

vector<bool> v;
int n;

int PA(int n){
  return (n*(n+1))/2;
}

int32_t main(){
  DESYNC;
  int t;
  cin >> t;
  while(t--){
    cin >> n;
    v.clear();
    v.resize(n);
    for(int i=0; i<n; i++){
      char c;
      cin >> c;
      if(c == '.') v[i] = false;
      else v[i] = true;
    }
    int l = 0;
    int cnt = 0; 
    int r = -1;
    vector< ii > seg;
    for(int i=0; i<n; i++){
      if(v[i]) r = i;
      else {
        if(l <= r)
          seg.pb(ii(l,r));
        l = i+1;
      }
    }
    if(l <= r) seg.pb(ii(l,r));
    if(seg.size() == 0){
      cout << 0 << endl;
      continue;
    }
    if(seg.size() == 1 && seg[0].ff == 0){
      cout << 0 << endl;
      continue;
    }   
    seg.pb(ii(n,n));
    int ans = 0;
    int cur = 0;
    for(int i=0; i<n; i++){
      if(v[i]){
        ans += (i - cur);
        cur++;
      }
    }
    cout << ans << endl;
    int acc = 0;
    for(int i=0; i<(int)seg.size()-1; i++){
      if(seg[i].ff == 0) continue;
      int x = seg[i].ff;
      int y = seg[i].ss;
      int nxt = seg[i+1].ff;
      int spaces = nxt - y - 1;
      ans += 2*PA(y-x);
      ans += 2*(y-x+1)*acc;
      int need = y-x+1;
      if(need < spaces){
        spaces -= need;
        int tira = min(acc, spaces);
        acc -= tira;
        spaces -= tira;
      }
      else {
        need -= spaces;
        acc += need;
      }
    }
    if(!acc) cout << ans << endl;
    else cout << -1 << endl;
  }
}


