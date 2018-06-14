/* Rolling Hash Implementation */
/* Uses 1-indexed string */

struct RollingHash{

  long long BASE = 137
  long long PRIME = (int)1e9+9;
  
  string a;
  vector<long long> hash;
  vector<long long> base;
  vector<long long> invBase;

  RollingHash() {}
  
  RollingHash(string s){
    a = s;
    hash.resize(s.size());
    base.resize(s.size());
    invBase.resize(s.size());
  }
  
  long long expo(long long a, long long k){
	  if(k == 0) return 1LL;
	  else if(k == 1) return a;
	  long long aux = expo(a, k/2);
	  aux %= PRIME;
	  aux *= aux;
	  aux %= PRIME;
	  if(k%2) aux *= a;
	  aux %= PRIME;
	  return aux;
  }

  void calculate(string a){
	  base[0] = 1;
	  invBase[0] = 1;
	  hash[0] = 0;
	  for(int i=1; i<=a.size(); i++){
		  hash[i]+= BASE*hash[i-1] + a[i-1];
		  hash[i] % = PRIME;
		  base[i] = base[i-1]*BASE;
		  base[i] %= PRIME;
		  invBase[i] = expo(base[i], PRIME-2);
	  }
  }

  long long query(int i, int j){
	  return ((h[j] - h[i-1])*invBase[j-i+1] + PRIME)%PRIME;
  }
  
}; 
