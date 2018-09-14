namespace DynamicSegmentTree{

  struct node {
    node *left, *right;
    //attributes of node
    node() {
      //initialize attributes
      left = NULL;
      right = NULL;
    }
  };
    
  void combine(node *ans, node *left, node *right){
    //combine operation
  }
  
  void propagate(node * root, int l, int r){
    //check if exists lazy
    
    //apply lazy on node
    
    //propagate
    if(!root->left) root->left = new node();
    if(!root->right) root->right = new node();
    
    if(l != r){
      //propagate operation
    }
    
    //reset lazy
  } 
  
  void build(node *root, int l, int r){
    if(l == r){
      //leaf operation
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
  
}
