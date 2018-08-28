struct BIT {
  
  vector<int> bit;

  BIT() {}
  
  int n;
   
  BIT(int n) {
    this->n = n;
    bit.resize(n+1);
  }

  void update(int idx, int val){
	  for(int i = idx; i <= n; i += i&-i){
		  bit[i]+=val;
	  }
  }

  int prefix_query(int idx){
	  int ans = 0;
	  for(int i=idx; i>0; i -= i&-i){
		  ans += bit[i];
	  }
	  return ans;
  }
  
  int query(int l, int r){
	  return prefix_query(r) - prefix_query(l-1);
  }
  
};


