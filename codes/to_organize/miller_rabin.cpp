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

namespace NT {

  const int MAX_N = 1123456;
  
  bitset<MAX_N> prime;
  vector<int> primes;
  int lf[MAX_N];
  int totient[MAX_N];

  void Sieve(int n){
    for(int i=0; i<=n; i++) lf[i] = i;
    prime.set();
    prime[0] = false;
    prime[1] = false;
    for(int p = 2; p*p <= n; p++){
      if(prime[p]){
        for(int i=p*p; i<=n; i+=p){
          prime[i] = false;
          lf[i] = min(lf[i], p);
        }
      }
    }
    for(int i=2; i<=n; i++) if(prime[i]) primes.pb(i);
  }

  void EulerTotient(int n){
    for(int i=0; i<=n; i++) totient[i] = i;
    for(int p = 2; p <= n; p++){
      if(totient[p] == p){
        totient[p] = p-1;
        for(int i=p+p; i<=n; i+=p){
          totient[i] = (totient[i]/p) * (p-1);
        }
      }
    }
  }
  
};

int32_t main(){
  DESYNC;
  int a = 0 ,b = 1000000;
  int cnt = 0;
  for(int i=a; i<=b; i++){
    if(NT::PrimalityTest(i, 20)) cnt++;
  }
  NT::Sieve(1000000);
  cout << cnt << " " << NT::primes.size() << endl;
}
