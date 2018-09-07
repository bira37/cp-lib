#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

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
using namespace __gnu_pbds;

typedef tree<
string,
null_type,
less<string>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

inline int mod(int n, int m){ int ret = n%m; if(ret < 0) ret += m; return ret; }

int gcd(int a, int b){
  if(a == 0 || b == 0) return 0;
  else return abs(__gcd(a,b));
}

struct query{
  int idx;
  string s;
  int ord;
  int ans = 0;
  bool operator<(const query & q) const {
    return ord < q.ord || (ord == q.ord && idx < q.idx);
  }
};

map<string, int> data;
ordered_set s;

int _query(string t){
  int lb = 0, ub = s.size()-1;
  int acc = 0;
  for(int i=0; i<t.size(); i++){
    if(lb > ub) break;
    char c = t[i];
    int l = lb, r = ub;
    int lef = ub+1;
    while(l <= r){
      int m = (l+r)/2;
      string k = *s.find_by_order(m);
      if((k.size() <= i)){
        l = m + 1;
      }
      else if(k[i] >= c){
        lef = m;
        r = m-1;
      }
      else l = m+1;
    }
    
    l = lb, r = ub;
    int rig = lb-1;
    while(l <= r){
      int m = (l+r)/2;
      string k = *s.find_by_order(m);
      if((k.size() <= i)){
        l = m + 1;
      }
      else if(k[i] <= c){
        rig = m;
        l = m + 1;
      }
      else r = m - 1;
    }
    acc += max(0, rig-lef+1);
    lb = lef, ub = rig;
  }
  return acc;
}

int32_t main(){
  DESYNC;
  int n;
  cin >> n;
  
  vector<string> vs(n);
  for(int i=0; i<n; i++){
    string t;
    cin >> t;
    vs[i] = t;
    data[t]  = i;
  }
  
  int q;
  cin >> q;
  
  query v[q];
  
  for(int i=0; i<q; i++){
    cin >> v[i].s;
    v[i].idx = i;
    if(data.count(v[i].s)) v[i].ord = data[v[i].s];
    else v[i].ord = n-1;
  }
  
  sort(v, v+q);
  data.clear();
  reverse(vs.begin(), vs.end());
  int p =0;
  for(int i=0; i<q; i++){
  
    while(p <= v[i].ord){
      s.insert(vs.back());
      vs.pop_back();
      p++;
    }
    
    v[i].ans = _query(v[i].s) + v[i].ord + 1;
    
  }
  sort(v, v+q, [](const query & a, const query & b){ return a.idx < b.idx; });
  
  for(int i=0; i<q; i++) cout << v[i].ans << endl;
}

