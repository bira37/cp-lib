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

  int GCD(int a, int b){
    if(a == 0) return b;
    else return GCD(b%a, a);
  }
  
  tuple<int,int> ExtendedEuclidean(int a, int b){
    //solves ax+by = gcd(a,b)
    //careful when a or b equal to 0
    if(a == 0) return make_tuple(0,1);
    int x,y;
    tie(x,y) = ExtendedEuclidean(b%a, a);
    return make_tuple(y - (b/a)*x, x);
  }
  
  bool FailDiophantine = false;
  
  tuple<int,int> Diophantine(int a, int b, int c){
    FailDiophantine = false;
    //finds a solution for ax+by = c
    //given a solution (x,y), all solutions have the form (x + m*(b/gcd(a,b)), y - m*(a/(gcd(a,b))), multiplied by (c/g)
    
    int g = GCD(a,b);
    
    if(g == 0 || c%g != 0) {
      FailDiophantine = true;
      return make_tuple(0,0);
    }
    
    int x,y;
    
    tie(x,y) = ExtendedEuclidean(a, b);
    
    return make_tuple(x*(c/g), y*(c/g));
  }
  
  bool FailCRT = false;
  tuple<int,int> CRT(vector<int> & a, vector<int> & n){
    FailCRT = false;
    for(int i=0; i<a.size(); i++) a[i] = mod(a[i], n[i]);
    int ans = a[0];
    int modulo = n[0];
    
    for(int i=1; i<a.size(); i++){
      int x,y;
      tie(x,y) = ExtendedEuclidean(modulo, n[i]);
      int g = GCD(modulo, n[i]);
      
      if(g == 0 || (a[i] - ans)%g != 0){
        FailCRT = true;
        return make_tuple(0,0);
      }
      
      ans = mod(ans + (x*(a[i] - ans)/g)%(n[i]/g) * modulo, modulo*n[i]/g);
      modulo = modulo*n[i]/g;
    }
    
    return make_tuple(ans, modulo); 
  }

}
  
  
int32_t main(){
  //DESYNC;
  int n;
  cin >> n;
  vector<int> a(n), m(n);
  for(int i=0; i<n; i++) cin >> a[i] >> m[i];
  int ans, lcm;
  tie(ans, lcm) = NT::CRT(a, m);
  if(NT::FailCRT) cout << "No solution" << endl;
  else cout << "ans = " << ans << " " << lcm << endl;
  int k;
  cin >> k;
  
  for(int i=0; i<k; i++){
    int na,nb, nc;
    cin >> na >> nb >> nc;
    int x,y;
    tie(x,y) = NT::Diophantine(na, nb, nc);
    if(NT::FailDiophantine) cout << "No solution" << endl;
    else cout << "ans = (" << x << ", " << y << ")" << endl;
  }
}


