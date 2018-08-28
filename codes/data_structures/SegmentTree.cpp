namespace SegmentTree{
  
  struct node{
	  //attributes of node
	  int lazy = 0;
	  node() {}
  };

  struct Tree{
    vector<node> st;
    Tree(){}
    
    Tree(int n){
      st.resize(4*n);
    }
  
    node combine(node a, node b){
	    node res;
	    //combine operations
	    return res;
    }

    void propagate(int cur, int l , int r){
	    //return if there is no update
	    //update tree using lazy node
	    if(l != r){
		    //propagate for left and right child
	    }
	    //reset lazy node
    }
    
    void build(int cur, int l, int r){
      if(l == r){
        //leaf operation
        return;
      }
      
      int m = (l+r)>>1;
      build(2*cur, l, m);
      build(2*cur + 1, m+1, r);
      st[cur] = combine(st[2*cur], st[2*cur+1]);
      
    }

    void range_update(int cur, int l, int r, int a, int b, long long val){
	    propagate(cur, l, r);
	    if(l == a && r == b){
		    //lazy operation using val
		    return;
	    }
	
	    int m = (l+r)/2;
	
	    if(b <= m) range_update(2*cur, l, m, a, b, val);
	    else if(m < a) range_update(2*cur+1, m+1, r, a, b, val);
	    else {
		    range_update(2*cur, l, m, a, m, val);
		    range_update(2*cur+1, m+1, r, m+1, b, val);
	    }
	
	    propagate(cur, l , r);
	    propagate(2*cur, l, m);
	    propagate(2*cur+1, m+1, r);
	    st[cur] = combine(st[2*cur], st[2*cur+1]);
    }

    node query(int cur, int l, int r, int a, int b){
	    propagate(cur, l, r);
	    if(l == a && r == b) return st[cur];
	
	    int m = (l+r)/2;
	    if(b <= m) return query(2*cur, l, m, a, b);
	    else if(m < a) return query(2*cur+1, m+1, r, a, b);
	    else {
		    node left = query(2*cur, l, m, a, m);
		    node right = query(2*cur+1, m+1, r, m+1, b);
		    node ans = combine(left, right);
		    return ans;
	    }
    }
  };
  
}
