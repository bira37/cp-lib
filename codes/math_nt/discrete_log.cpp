/* Baby-Step Giant-Step Shank's Algorithm */

namespace NT {

  int discrete_log(int a, int b, int p){
    a %= p, b %= p;
	
    if(b == 1) return 0;
	
    int cnt = 0, t = 1;
    for(int g = gcd(a, p); g != 1; g = gcd(a, p)){
      if(b % g) return -1;
		
      p /= g, b /= g, t = t * a / g % p;
      cnt++;
		
      if(b == t) return cnt;
    }

    map<int, int> hash;
    int m = (sqrt(p) + 1);
    int base = b;
	
    for(int i = 0; i != m; ++i){
      hash[base] = i;
      base = base * a % p;
    }
	
    base = 1;
    for(int i=0; i<m; i++){
      base = (base*a)%p;
    }

    int cur = t;
    for(int i = 1; i <= m + 1; ++i){
      cur = cur * base % p;
      if(hash.count(cur)) return i * m - hash[cur] + cnt;
    }
    return -1;
  }
  
}
