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
  if(a == 0 || b == 0) return max(abs(a),abs(b));
  else return abs(__gcd(a,b));
}

int32_t main(){
  DESYNC;
  int n, ax, ay;
  cin >> n >> ax >> ay;
  map< ii, int> m;
  int ans = 0;
  for(int i=0; i<n; i++){
    int x,y;
    cin >> x >> y;
    int vx = x - ax;
    int vy = y - ay;
    int g = gcd(vx,vy);
    vx /= g;
    vy /= g;
    if(vx < 0){
      vx *= -1;
      vy *= -1;
    }
    else if(vx == 0 && vy < 0){
      vx *= -1;
      vy *= -1;
    }
    m[ii(vx,vy)]++;
  }
  cout << m.size() << endl;
}


