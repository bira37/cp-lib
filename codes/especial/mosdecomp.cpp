struct query{
	int id, l, r, ans;
	bool operator<(const query & b) const {
	  return l/(int)sqrt(n) < b.l/(int)sqrt(n) || l/(int)sqrt(n) == b.l/(int)sqrt(n) && r < b.r;
	}
};

struct SqrtDecomposition {

  vector<query> q;
  
  void read(int sz){
    q.resize(sz);
    for(int i=0; i<q.size(); i++){
      q[i].id = i;
      scanf("%d%d", &q[i].l, &q[i].r);
      q[i].l--;
      q[i].r--;
    }
  }
  
  void add(int idx){
 
  }
  
  void remove(int idx){

  }
  
  int answer_query(){
  
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
  
  void print_ans(){
    sort(q.begin(), q.end(), [](const query & a, const query & b){
      return a.id < b.id;
    });
    
    for(query x : q){
      printf("%d\n", x.ans);
    }
  }
};
