namespace NT{

  int GCD(int a, int b){
    if(a == 0) return b;
    else return GCD(b%a, a);
  }
  
  tuple<int,int> ExtendedEuclidean(int a, int b){
    //solves ax+by = gcd(a,b)
    //careful when a or b equal to 0
    if(a == 0) return make_tuple(0,1);
    int x,y;
    tie(x,y) = ExtendedEuclidean(b%a, a);
    return make_tuple(y - (b/a)*x, x);
  }
  
  bool FailDiophantine = false;
  
  tuple<int,int> Diophantine(int a, int b, int c){
    FailDiophantine = false;
    //finds a solution for ax+by = c
    //given a solution (x,y), all solutions have the form (x + m*(b/gcd(a,b)), y - m*(a/(gcd(a,b))), multiplied by (c/g)
    
    int g = GCD(a,b);
    
    if(g == 0 || c%g != 0) {
      FailDiophantine = true;
      return make_tuple(0,0);
    }
    
    int x,y;
    
    tie(x,y) = ExtendedEuclidean(a, b);
    int s1 = x*(c/g), s2 = y*(c/g);
    
    //shifts solution
    int l = 0, r = 1e9;
    int ans = -1;
    while(l <= r){
      int m = (l+r)>>1;
      if(s2 + m*(a/g) >= 0){
        ans = m;
        r = m-1;
      }
      else l = m+1;
    }
    if(ans != -1){
      s1 = s1 - ans*(b/g);
      s2 = s2 + ans*(a/g);
    }
    
    l = 0, r = 1e9;
    ans = -1;
    while(l <= r){
      int m = (l+r)>>1;
      if(s1 + m*(a/g) >= 0){
        ans = m;
        r = m-1;
      }
      else l = m+1;
    }
    if(ans != -1){
      s1 = s1 + ans*(b/g);
      s2 = s2 - ans*(a/g);
    }
    
    l = 0, r = 1e9;
    ans = -1;
    while(l <= r){
      int m = (l+r)>>1;
      if(s1 - m*(a/g) <= s2 + m*(b/g)){
        ans = m;
        r = m-1;
      }
      else l = m+1;
    }
    if(ans != -1){
      s1 = s1 - ans*(b/g);
      s2 = s2 + ans*(a/g);
    }
    
    return make_tuple(s1, s2);
  }
  
  bool FailCRT = false;
  
  tuple<int,int> CRT(vector<int> & a, vector<int> & n){
    FailCRT = false;
    for(int i=0; i<a.size(); i++) a[i] = mod(a[i], n[i]);
    int ans = a[0];
    int modulo = n[0];
    
    for(int i=1; i<a.size(); i++){
      int x,y;
      tie(x,y) = ExtendedEuclidean(modulo, n[i]);
      int g = GCD(modulo, n[i]);
      
      if(g == 0 || (a[i] - ans)%g != 0){
        FailCRT = true;
        return make_tuple(0,0);
      }
      
      ans = mod(ans + (x*((a[i] - ans)/g))%(n[i]/g) * modulo, modulo*(n[i]/g));
      modulo = modulo*(n[i]/g);
    }
    
    return make_tuple(ans, modulo); 
  }

}
