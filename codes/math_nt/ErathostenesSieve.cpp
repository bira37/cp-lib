/* Erasthostenes Sieve Implementation + Euler's Totient */
/* Calculate primes from 2 to N */
/* lf[i] stores the lowest prime factor of i(logn factorization) */

namespace NT {

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
