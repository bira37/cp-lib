#include <bits/stdc++.h>

#define int long long
#define double long double
#define ff first
#define ss second
#define endl '\n'
#define ii pair<int, int>
#define mp make_pair
#define mt make_tuple
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
  if(a == 0) return b;
  else return gcd(b%a, a);
}

struct BIT2D{
  vector< vector<int> > bit;
  
  int n, m;
  
  BIT2D() {}

  BIT2D(int n, int m){
    bit.resize(n+1, vector<int>(m+1));
    this->n = n;
    this->m = m;
  }
  
  void update(int x, int y, int val){
    for(int i = x; i<=n; i += i&-i){
      for(int j = y; j<=m; j+= j&-j){
        bit[i][j] += val;
      }
    }
  }
  
  int prefix_query(int x, int y){
    int ans = 0;
    for(int i=x; i>0; i -= i&-i){
      for(int j=y; j>0; j -= j&-j){
        ans += bit[i][j];
      }
    }
    return ans;
  }
  
  int query(int x1, int y1, int x2, int y2){
    return prefix_query(x2, y2) + prefix_query(x1-1, y1-1) - prefix_query(x2, y1-1) - prefix_query(x1-1, y2);
  }
  
};  

int get_value(int a,int b, int c, int d){
  return a + b*91767624123 + c*17254712646 + d*75635172973;
} 

int32_t main(){
  DESYNC;
  BIT2D bit(5005, 5005);
  int q;
  cin >> q;
  vector< tuple<int,int,int,int> > rect(q+1);
  int qries = 0;
  while(q--){
    qries++;
    int qry;
    cin >> qry;
    if(qry == 1){
      int x1,y1,x2,y2;
      cin >> x1 >> y1 >> x2 >> y2;
      rect[qries] = mt(x1,y1,x2,y2);
      int hs = get_value(x1,y1,x2,y2);
      bit.update(x1,y1, hs);
      bit.update(x2+1, y2+1, hs);
      bit.update(x2+1, y1, hs);
      bit.update(x1, y2+1, hs);
    }
    else if(qry == 2){
      int j;
      cin >> j;
      int x1,y1,x2,y2;
      tie(x1,y1,x2,y2) = rect[j];
      int hs = get_value(x1,y1,x2,y2);
      bit.update(x1,y1, hs);
      bit.update(x2+1, y2+1, hs);
      bit.update(x2+1, y1, hs);
      bit.update(x1, y2+1, hs);
    }
    else {
      int x1,y1,x2,y2;
      cin >> x1 >> y1 >> x2 >> y2;
      if(bit.prefix_query(x1,y1) == bit.prefix_query(x2, y2)) cout << "Y";
      else cout << "N";
    }
  }
  cout << endl;
}


