/* Erasthostenes Sieve Implementation */
/* Calculate primes from 2 to N */
/* lf[i] stores the lowest prime factor of i(logn factorization) */

bitset<N> prime;
int lf[N];

void run_sieve(int n){
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
}
