struct ConvexHullTrick {
  //max cht
    
  vector<line> cht;
  
  ConvexHullTrick() {}
  
  struct line{
    int id, a, b;
    line() {}
    line(int id, int a, int b) : id(id), a(a), b(b) {}
  };

  bool cmp(const line & a, const line & b){
	  return (a.a < b.a || (a.a == b.a && a.b > b.b));
  } 

  bool remove(line & a, line & b, line & c){
	  if((a.a - c.a)*(c.b - b.b) <= (b.a - c.a)*(c.b - a.b)) return true;
	  else return false;
  }

  void add(line & v){
	  if(cht.empty()){
	    cht.push_back(v);
	  }
	  else {
		  if(cht.back().a == v.a) return;
		  while(cht.size() > 1 && remove(cht[cht.size()-2], cht.back(), v)){
		    cht.pop_back();
		  }
		  cht.push_back(v);
	  }
  }

  void preprocess_cht(vector< line > & v){
    sort(v.begin(), v.end(), cmp);
    cht.clear();
    for(int i=0; i<v.size(); i++){
      add(v[i]);
    }
  }

  int f(int i, int x){
    return cht[i].a*x + cht[i].b;
  }

  //return line index
  int query(int x){
    if(cht.size() == 0) return -1;
    if(cht.size() == 1) return 0;
    int l = 0, r = cht.size()-2;
    int ans= cht.size()-1;
    while(l <= r){
      int m = (l+r)/2;
      int y1 = f(m, x);
      int y2 = f(m+1, x);
      if(y1 >= y2){
        ans = m;
        r = m-1;
      }
      else l = m+1;
    }
    return ans;
  }

};
