namespace SegmentTree{

  //val type example
  struct val_type{
    int val;
    val_type() {}
    val_type(int val) : val(val){}
  };
  
  //node type example
  struct node{
    int val = 0;
    int lazy = 0;
    node(){}
    node(int val, int lazy) : val(val), lazy(lazy) {}
    node neutral(){ return node(0,0); };
    bool no_update() { return lazy == 0; }
    void update_lazy(val_type val) {lazy += val.val;}
    void apply(int l, int r) { val += (r-l+1)*lazy; }
    void reset_lazy() { lazy = 0; }
    node propagate(node b) { b.lazy += lazy; return b; }
    node combine(node b) { node ans; ans.val = b.val + val; return ans; }
  };
  
  template<class node_t, class update_t>
  class Tree{
  public:
    vector<node_t> st;
    Tree(){}
    Tree(int n){
      st.resize(4*n);
    } 
    void propagate(int cur, int l , int r){
      if(st[cur].no_update()) return;
      st[cur].apply(l, r);
      if(l != r){
        st[2*cur] = st[cur].propagate(st[2*cur]);
        st[2*cur+1] = st[cur].propagate(st[2*cur+1]);
      }
      st[cur].reset_lazy();
    }
    void update(int cur, int l, int r, int a, int b, update_t val){
      propagate(cur, l, r);
      if(b < l || r < a) return;
      if(a <= l && r <= b){
        st[cur].update_lazy(val);
        propagate(cur, l, r);
        return;
      }
      int m = (l+r)/2;
      update(2*cur, l, m, a, b, val);
      update(2*cur+1, m+1, r, a, b, val);
      st[cur] = st[2*cur].combine(st[2*cur+1]);
    }
    node_t query(int cur, int l, int r, int a, int b){
      propagate(cur, l, r);
      if(b < l || r < a) return st[cur].neutral();
      if(a <= l && r <= b) return st[cur];
      int m = (l+r)/2;
      node_t left = query(2*cur, l, m, a, b);
      node_t right = query(2*cur+1, m+1, r, a, b);
      node_t ans = left.combine(right);
      return ans;
    }
  };
}
