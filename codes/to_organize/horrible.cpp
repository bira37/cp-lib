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

int v[112345];

namespace DynamicSegmentTree{

  struct node {
	  node *left, *right;
	  //attributes of node
	  int sum, lazy;
	  node() {
		  //initialize attributes
		  sum = 0;
		  lazy = 0;
		  left = NULL;
		  right = NULL;
	  }
  };

  struct DynamicSegTree{
  
    node * root;
    
    DynamicSegTree(){
      root = new node();
    }
    
    void combine(node *ans, node *left, node *right){
	    ans->sum = left->sum + right->sum;
    }
    
    void propagate(node * root, int l, int r){
      //check if exists lazy
      if(root->lazy == 0) return;
      
      //apply lazy on node
      root->sum += (r-l+1)*root->lazy;
      
      //propagate
      if(!root->left) root->left = new node();
	    if(!root->right) root->right = new node();
	    
	    if(l != r){
	      root->right->lazy += root->lazy;
	      root->left->lazy += root->lazy;
	    }
	    
	    //reset lazy
	    root->lazy = 0;
	  } 
    
    void build(node *root, int l, int r){
	    if(l == r){
		    root->sum = v[l];
		    return;
	    }
	    int m = (l+r) >> 1;
	    if(!root->left) root->left = new node();
	    if(!root->right) root->right = new node();
	    build(root->left, l, m);
	    build(root->right, m+1, r);
	    combine(root, root->left, root->right);
    }

    void update(node *root, int l, int r, int a, int b, int val){
      propagate(root, l, r);
	    if(l == a && r == b){
		    //do lazy operation
		    root->lazy += val;
		    return;
	    }
	    int m = (l+r) >> 1;
	    if(!root->left) root->left = new node();
	    if(!root->right) root->right = new node();
	    if(b <= m) update(root->left, l, m, a, b, val);
	    else if(m < a) update(root->right, m+1, r, a, b, val);
	    else {
	      update(root->left, l, m, a, m, val);
	      update(root->right, m+1, r, m+1, b, val);
	    }
	    propagate(root, l, r);
	    propagate(root->left, l, m);
	    propagate(root->right, m+1, r);
	    combine(root, root->left, root->right);
    }

    node* query(node *root, int l, int r, int a, int b){
      propagate(root, l, r);
	    if(l == a && r == b){
		    return root;
	    }
	    int m = (l+r) >> 1;
	    if(!root->left) root->left = new node();
	    if(!root->right) root->right = new node();
	    if(b <= m) return query(root->left, l, m, a, b);
	    else if(m < a) return query(root->right, m+1, r, a, b);
	    node *left = query(root->left, l,m,a,m);
	    node *right = query(root->right, m+1, r, m+1, b);
	    node *ans = new node();
	    combine(ans, left, right);
	    return ans;
    }
  };
  
}

int32_t main(){
  DESYNC;
  int t;
  cin >> t;
  while(t--){
    DynamicSegmentTree::DynamicSegTree st;
    int n, q;
    cin >> n >> q;
    while(q--){
      int op, l, r, val;
      cin >> op;
      if(op == 0){
        cin >> l >> r >> val;
        l--,r--;
        st.update(st.root, 0, n-1, l, r, val);
      }
      else {
        cin >> l >> r;
        l--,r--;
        cout << st.query(st.root, 0, n-1, l, r)->sum << endl;
      }
    }
  }
      
}
