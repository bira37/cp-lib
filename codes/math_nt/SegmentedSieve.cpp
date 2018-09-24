/* Segmented Erathostenes Sieve */
/* Needs primes up to sqrt(N) - Use normal sieve to get them */

namespace NT {
  
  const int MAX_N = 1123456;
  bitset<MAX_N> prime;
  vector<int> primes;
  vector<int> seg_primes;

  void Sieve(int n){
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

  void SegmentedSieve(int l, int r){
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
      if(prime[i] && l+i > 1){
        seg_primes.pb(l+i);
      }
    }
  }
  
}
