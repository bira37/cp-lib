#include <bits/stdc++.h>

#define int long long
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

using namespace std;

inline int mod(int n){ return (n%1000000007); }

int gcd(int a, int b){
  if(a == 0 || b == 0) return 0;
  if(b == 1) return b;
  else return gcd(b, a%b);
}

struct Lichao{
  //min lichao tree
  
  struct line {
    int a, b;
    line() {
      a = 0;
      b = INF;
    }
    line(int a, int b) : a(a), b(b) {}
    int eval(int x){
      return a*x + b;
    }
  }; 
  
  struct node {
    node * left, * right;
    line ln;
    node(){
      left = NULL;
      right = NULL;
    }
  };
   
  node * root;
  
  Lichao(){
    root = new node();
  }
  
  void add(node * root, int l, int r, line ln){
    if(!root->left) root->left = new node();
    if(!root->right) root->right = new node();
    int m = (l+r)>>1;
    bool left = ln.eval(l) < (root->ln).eval(l);
    bool mid = ln.eval(m) < (root->ln).eval(m);
    
    if(mid){
      swap(root->ln, ln);
    }
    
    if(l == r) return;
    else if(left != mid) add(root->left, l, m, ln);
    else add(root->right, m+1, r, ln);
  }
  
  int query(node * root, int l, int r, int x){
    if(!root->left) root->left = new node();
    if(!root->right) root->right = new node();
    int m = (l+r)>>1;
    if(l == r) return (root->ln).eval(x);
    else if(x < m) return min((root->ln).eval(x), query(root->left, l, m, x));
    else return min((root->ln).eval(x), query(root->right, m+1, r, x));
  }
  
}; 

Lichao lichao;

int query(int x){
  return lichao.query(lichao.root, 0, 1000000, x);
}

void add(Lichao::line l){
  lichao.add(lichao.root, 0, 1000000, l);
}

int32_t main(){
	DESYNC;
	int n;
	cin >> n;
	int h[n], w[n];
	for(int i=0; i<n; i++) cin >> h[i];
	for(int i=0; i<n; i++) cin >> w[i];
	
	int dp[n];
	dp[0] = -w[0];
	add(line(-2LL*h[0], h[0]*h[0] + dp[0]));
	for(int i=1; i<n; i++){
	  dp[i] = query(h[i]) + h[i]*h[i] - w[i];
	  add(line(-2LL*h[i], h[i]*h[i] + dp[i]));
	}
	cout << dp[n-1] << endl;
}


