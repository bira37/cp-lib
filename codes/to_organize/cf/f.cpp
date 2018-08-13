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

inline int mod(int n){ return (n%(1LL<<32)); }

int gcd(int a, int b){
  if(a == 0 || b == 0) return 0;
  if(b == 1) return b;
  else return gcd(b, a%b);
}

bitset<112345> prime;
vector<int> primes;
vector<int> seg_primes;

void run_sieve(int n){
	prime.set();
	prime[0] = false;
	prime[1] = false;
	for(int p = 2; p*p <= n; p++){
		if(prime[p]){
			for(int i=p*p; i<=n; i+=p){
				prime[i] = false;
			}
		}
	}
	for(int i=2; i<=n; i++) if(prime[i]) primes.pb(i);
}

void segmented_sieve(int l, int r){
  prime.set();
  seg_primes.clear();
  for(int p : primes){
    int start = l - l%p - p;
    while(start < l) start += p;
    if(p == start) start += p;
    for(int i = start; i<=r; i+=p){
      prime[i-l] = false;
    }
  }
  for(int i=0; i<r-l+1; i++){
    if(prime[i]){
      seg_primes.pb(l+i);
    }
  }
}
    

int f(int a, int b, int c,int d, int x){
  int val = mod(a*x);
  val = mod(val + b);
  val = mod(val*x);
  val = mod(val + c);
  val = mod(val*x);
  val = mod(val + d);
  return val;
}

int32_t main(){
	DESYNC;
	run_sieve(100000);
	int n,a,b,c,d;
	cin >> n >> a >> b >> c >>d;
	int ans = 0;
	for(int p : primes){
	  int acc = 0;
	  int cur = p;
	  while(cur <= n){
	    acc += n/cur;
	    cur*=p;
	  }
	  ans += mod(f(a,b,c,d,p)*acc);
	  ans = mod(ans);
	}
	int l = 100001, r = n;
	for(int i=l; i<=r; i+=100000){
	  segmented_sieve(i, min(i+100000-1, r));
	  for(int p : seg_primes){
	    int acc = 0;
	    int cur = p;
	    while(cur <= n){
	      acc += n/cur;
	      cur*=p;
	    }
	    ans += mod(f(a,b,c,d,p)*acc);
	    ans = mod(ans);
	  }
	}
	cout << ans << endl;
}


