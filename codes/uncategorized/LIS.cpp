/* Use upper_bound to swap to longest non decreasing subsequence */

struct LIS{

  vector<int> seq;
  
  LIS() {}

  LIS(int n){
    seq.resize(n+1);
  }
  
  void calculate(vector<int> & v){
    int n = v.size();
	  for(int i=1; i<=n; i++) seq[i] = INT_MAX;
	  seq[0] = INT_MIN;
	  for(int i=0; i<n; i++){
		  int index = lower_bound(seq.begin(), seq.end(), v[i]) - seq.begin();
		  index--;
		  seq[index+1] = min(seq[index+1], v[i]);
	  }
  }
  
}; 
	
