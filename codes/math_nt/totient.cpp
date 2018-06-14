
struct EulerTotient{

  vector<int> phi;
  
  EulerTotient() {}
  
  EulerTotient(int n){
    phi.resize(n);
    for(int i=0; i<=n; ++i) phi[i] = i;
  }
  
  void calculate(int n){
    
	  for(int i=2; i<=n; ++i){
	    if(phi[i] == i){
	      for(int j=i; j<=(int)1e6; j+=i){
				  phi[j] -= phi[j] / i;
		    }
		  }
    }
    
  }
  
};
