//Erasthostenes Sieve

bool prime[N];

void run_sieve(int n){
	for(int i = 0; i<=n; i++) prime[i] = true;
	prime[0] = false;
	prime[1] = false;
	for(int p = 2; p*p <= n; p++){
		if(prime[p]){
			for(int i=p+p; i<=n; i+=p){
				prime[i] = false;
			}
		}
	}
}
