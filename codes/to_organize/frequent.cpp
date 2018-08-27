#include <bits/stdc++.h>

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

int v[112345];
int cnt[212345] = {0};
multiset < int, greater<int> > s;

namespace Mos {

  int sqr;

  struct query{
	  int id, l, r, ans;
	  bool operator<(const query & b) const {
	    if(l/sqr != b.l/sqr) return l/sqr < b.l/sqr;
	    return (l/sqr) % 2 ? r > b.r : r < b.r;
	  }
  };

  struct QueryDecomposition {

    vector<query> q;
    
    QueryDecomposition(int n, int nq){
      q.resize(nq);
      sqr = (int)2*sqrt(n);
    }
    
    void read(){
      for(int i=0; i<q.size(); i++){
        cin >> q[i].l >> q[i].r;
        q[i].l--, q[i].r--;
        q[i].id = i;
      }
    }
    
    void add(int idx){
      s.erase(s.find(cnt[v[idx]]));
      cnt[v[idx]]++;
      s.insert(cnt[v[idx]]);  
    }
    
    void remove(int idx){
      s.erase(s.find(cnt[v[idx]]));
      cnt[v[idx]]--;
      s.insert(cnt[v[idx]]);
    }
    
    int answer_query(){
      return *s.begin();
    }

    void calculate(){
	    sort(q.begin(), q.end());
	    int l = 0, r = -1;
	    for(int i=0; i<q.size(); i++){
		    while(q[i].l < l) add(--l);
		    while(r < q[i].r) add(++r);
		    while(q[i].l > l) remove(l++);
		    while(r > q[i].r) remove(r--);
		    q[i].ans = answer_query();
	    }
    }
    
    void print(){
      sort(q.begin(), q.end(), [](const query & a, const query & b){
        return a.id < b.id;
      });
      
      for(query x : q){
        cout << x.ans << endl;
      }
    }
  };
  
}

int32_t main(){
  DESYNC;
  int n, q;
  while(cin >> n, n != 0){
    cin >> q;
    s.clear();
    Mos::QueryDecomposition mos(n, q);
    for(int i=0; i<n; i++){
      cin >> v[i];
      v[i] += 100000;
      cnt[v[i]] = 0;
      s.insert(0);
    }
    mos.read();
    mos.calculate();
    mos.print();
  }
}
