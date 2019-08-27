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

struct node {
  int fst, lst, sum;
  node(){}
  node(int fst, int lst, int sum) : fst(fst), lst(lst), sum(sum) {}
};

node st[812345];
int v[812345];

node merge(node a, node b){
  return node(0,0, a.sum + b.sum);
}

void build(int cur, int l, int r){
  if(l == r){
    st[cur] = node(0,0,v[l]);
    return;
  }
  
  int m = (l+r)>>1;
  
  build(2*cur, l, m);
  build(2*cur+1, m+1, r);
  
  st[cur] = merge(st[2*cur], st[2*cur+1]);
}

void propagate(int cur, int l, int r){
  if(st[cur].fst == 0) return;
  
  st[cur].sum += ((st[cur].fst + st[cur].lst)*(r-l+1))/2;
  
  if(l != r){
    int m = (l+r)>>1;
    
    int step = (st[cur].lst - st[cur].fst)/(r-l);
    
    st[2*cur].fst += st[cur].fst;
    st[2*cur].lst += st[cur].fst + (m-l)*step;
    st[2*cur+1].fst += st[cur].fst + (m-l+1)*step;
    st[2*cur+1].lst += st[cur].fst + (r-l)*step;
    
  }
  
  st[cur].fst = st[cur].lst = 0;
}

void update(int cur, int l, int r, int a, int b){
  propagate(cur, l, r);
  if(b < l or r < a) return;
  if(a <= l and r <= b){
    //lazy stuff
    st[cur].fst = (l-a+1);
    st[cur].lst = (r-a+1);
    propagate(cur, l, r);
    return;
  }
  
  int m = (l+r)>>1;
  
  update(2*cur, l, m, a, b);
  update(2*cur+1, m+1, r, a, b);
  
  st[cur] = merge(st[2*cur], st[2*cur+1]);
}

node query(int cur, int l, int r, int a, int b){
  propagate(cur, l, r);
  if(b < l or r < a) return node(0,0,0);
  if(a <= l and r <= b){
    return st[cur];
  }
  
  int m = (l+r)>>1;
  
  node lft = query(2*cur, l, m, a, b);
  node rgt = query(2*cur+1, m+1, r, a, b);
  return merge(lft, rgt);
}

int32_t main(){
  DESYNC;
  int n,q;
  cin >> n >> q;
  for(int i=0; i<n; i++) cin >> v[i];
  build(1, 0, n-1);
  while(q--){
    int t, l, r;
    cin >> t >> l >> r;
    if(t == 1) update(1, 0, n-1, l-1, r-1);
    else cout << query(1, 0, n-1, l-1, r-1).sum << endl;
  }
}


