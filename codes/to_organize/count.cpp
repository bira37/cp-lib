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
  
  int mulmod(int a, int b, int c){
    int x = 0,y=a%c;
    
    while(b > 0){
    
      if(b%2 == 1){
        x = (x+y)%c;
      }
      
      y = (y*2)%c;
      b /= 2;
    }
    
    return x%c;
  }
  
  int expmod(int a, int k, int p){
    if(k == 0) return 1;
    if(k == 1) return a;
    
    int aux = expmod(a, k/2, p);
    aux = mulmod(aux, aux, p);
    
    if(k%2) aux = mulmod(aux, a, p);
    return aux;
  }
  
  bool MillerRabin(int p){
    if(p < 2) return false;
    if(p == 2) return true;
    if(p%2 == 0) return false;
    
    int s = p-1;
    while(s%2 == 0) s /= 2;
    
    int a = rand()%(p-1) + 1;
    int b = expmod(a, s, p);
    
    while(s != p-1 && b != 1 && b != p-1){
      b = mulmod(b,b,p);
      s *= 2;
    }
    
    if(b != p-1 && s%2 == 0) return false;
    
  } 
  
  bool PrimalityTest(int p, int iterations){
    //Miller Rabin Primality Test
    mt19937 mt_rand(time(0));
    
    if(p < 2) return false;
    if(p == 2) return true;
    if(p%2 == 0) return false;
    
    int fixed_s = p-1;
    while(fixed_s%2 == 0) fixed_s /= 2;
    
    for(int iter = 0; iter < iterations; iter++){

      int s = fixed_s;
      
      int a = mt_rand()%(p-1) + 1;
      int b = expmod(a, s, p);
      
      while(s != p-1 && b != 1 && b != p-1){
        b = mulmod(b,b,p);
        s *= 2;
      }
      
      if(b != p-1 && s%2 == 0) return false;
      
    }
    
    return true;
    
  }
  
}

namespace NT{
  
  int CountPrimeFactors(int x){
    
    int ans = 0;
    for(int i=2; i*i*i <= x; i++){
      while(x%i == 0){
        ans++;
        x/=i;
      }
    }
    
    if(PrimalityTest(x, 10)) ans++;
    else if((int)sqrt(x)*(int)sqrt(x) == x && PrimalityTest((int)sqrt(x), 10)) ans+=2;
    else if(x != 1) ans+=2;
    
    return ans;
    
  }
  
  int CountDivisors(int x){
    
    int ans = 1;
    for(int i=2; i*i*i <= x; i++){
      int cnt = 1;
      while(x%i == 0){
        cnt++;
        x/=i;
      }
      ans*=cnt;
    }
    
    if(PrimalityTest(x,15)) ans*=2;
    else if((int)sqrt(x)*(int)sqrt(x) == x && PrimalityTest((int)sqrt(x), 15)) ans*=3;
    else if(x != 1) ans*=4;
    
    return ans;
  }
}  

int32_t main(){
  DESYNC;
  int t;
  cin >> t;
  while(t--){
    int a,b;
    cin >> a >> b;
    int v[b-a+1];
    for(int i=a; i<=b; i++){
      v[i-a] = NT::CountPrimeFactors(i);
    }
    int dp[40];
    for(int i=0; i<40; i++) dp[i] = 0;
    for(int i=a; i<=b; i++){
      int sg = v[i-a];
      int dp2[40];
      for(int i=0; i<40; i++) dp2[i] = 0;
      dp2[sg]++;
      for(int i=0; i<40; i++){
        dp2[(i^sg)] += dp[i];
        dp2[(i^sg)] = mod(dp2[(i^sg)], M);
      }
      for(int i=0; i<40; i++){
        dp[i] += dp2[i];
        dp[i] = mod(dp[i], M);
      }
    }
    int ans = 0;
    for(int i=1; i<40; i++){
      ans += dp[i];
      ans = mod(ans, M);
    }
    cout << ans << endl;
  }
}
