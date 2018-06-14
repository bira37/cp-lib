/* Z-function */
/* Calculate the size K of the largest substring which is a prefix */

struct ZFunction{

  vector<int> z;
  
	string t;
	
	ZFunction() {}
	
	ZFunction(string s){
	  t = s;
	  z.resize(t.size());
	}
	
  void calculate(){
	  int n = t.size();
	  z[0] = 0;
	  int l = 0, r = 0;
	  for(int i=1; i<n; i++){
		  if(i > r){
			  l = i;
			  r = i;
		  }
		  z[i] = min(z[i-l], r-i+1);
		  while(i + z[i] < n && t[i + z[i]] == t[z[i]]) z[i]++;
		  if(i + z[i] > r){
			  l = i;
			  r = i + z[i]-1;
		  }
	  }
  }
  
};
