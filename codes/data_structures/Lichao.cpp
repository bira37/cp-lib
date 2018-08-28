namespace Lichao{
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
  
  struct Tree {
  
    node * root;
    
    Tree() {
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
  
}
