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

namespace NT{

  tuple<int,int> ExtendedEuclidean(int a, int b){
    //solves ax+by = gcd(a,b)
    //careful when a or b equal to 0
    if(a == 0) return make_tuple(0,1);
    int x,y;
    tie(x,y) = ExtendedEuclidean(b%a, a);
    return make_tuple(y - (b/a)*x, x);
  }
  
  tuple<int,int> Diophantine(int a, int b, int c){
    //finds a solution for ax+by = c
    //need to check first if gcd(a,b) divides c
    //given a solution (x,y), all solutions have the form (x + m*(b/gcd(a,b)), y - m*(a/(gcd(a,b))), multiplied by (c/g)
    int g = gcd(a,b);
    
    int x,y;
    
    tie(x,y) = ExtendedEuclidean(a, b);
    
    return make_tuple(x*(c/g), y*(c/g));
  }

}

int32_t main(){
  DESYNC;
  int a,b;
  cin >> a >> b;
  int x,y;
  tie(x,y) = NT::ExtendedEuclidean(a,b);
  cout << x << " " << y << " " << gcd(a,b) << endl;  
}
