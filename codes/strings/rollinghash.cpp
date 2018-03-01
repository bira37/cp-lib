//Rolling Hash

long long BASE = //bate a cabeça no teclado
long long PRIME = (int)1e9+7;

long long hash[N];
long long base[N];

void calculate(string a){
	base[0] = 1;
	hash[0] = 0;
	for(int i=1; i<=a.size(); i++){
		hash[i]+= BASE*hash[i-1] + a[i-1];
		hash[i] % = PRIME;
		base[i] = base[i-1]*BASE;
		base[i] %= PRIME;
	}
}

long long range_hash(int i, int j){
	return h[j] - h[i-1]*base[j-i+1];
} 
