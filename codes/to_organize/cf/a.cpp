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

namespace Hash{
  int B1, B2, M1, M2;
  
  void init(){
    B1 = rand()%65536;
    B2 = rand()%65536;
    M1 = 1000000007;
    M2 = 1000000009;
  }
  
  struct RollingHash{
    
    vector< ii > hash;
    vector< ii > base;
    
    RollingHash() {}
    
    void calculate(string s){
      int n = s.size();
      hash.resize(n+1); base.resize(n+1);
      base[0] = ii(1, 1);
      hash[0] = ii(0, 0);
      for(int i=1; i<=n; i++){
        int val = (int)(s[i-1]);
        base[i] = ii(mod(base[i-1].ff*B1, M1), mod(base[i-1].ss*B2, M2));
        hash[i] = ii(mod(hash[i-1].ff*B1 + val, M1), mod(hash[i-1].ss*B2 + val, M2));
      }
    }
    
    ii query(int l, int r){
      ii ret;
      ret.ff = mod(hash[r].ff - hash[l-1].ff*base[r-l+1].ff, M1);
      ret.ss = mod(hash[r].ss - hash[l-1].ss*base[r-l+1].ss, M2);
      return ret;
    }
    
  };
  
}

int32_t main(){
  //DESYNC;
  int n;
  while(cin >> n){
    
    string s;
    cin >> s;
    cin.ignore();
    Hash::init();
    Hash::RollingHash rh;
    rh.calculate(s);
    ii hash_val = rh.query(1, s.size());
    int n = s.size();
    char c;
    int i = 0;
    queue<char> q;
    ii cur(0,0);
    while(c = getchar(), c!= '\n' && c != EOF){
      i++;
      q.push(c);
      int val = (int)(c);
      cur.ff = mod(cur.ff*Hash::B1 + val, Hash::M1);
      cur.ss = mod(cur.ss*Hash::B2 + val, Hash::M2);
      if(q.size() > n){
        val = q.front();
        q.pop();
        cur.ff = mod(cur.ff - rh.base[n].ff*val, Hash::M1);
        cur.ss = mod(cur.ss - rh.base[n].ss*val, Hash::M2); 
      }
      if(i >= n && hash_val == cur) cout << i-n << endl;
    }
    cout << endl;
  }     
}


