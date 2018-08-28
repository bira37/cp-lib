/* Knuth - Morris - Pratt Algorithm */

struct KMP{
  vector<int> pi;
  
  vector<int> matches;
  
  KMP() {}

  void calculate(string t) {
    int n = t.size();
    pi.resize(n);
	  pi[0] = 0;
	  for(int i = 1; i < n; i++) {
		  pi[i] = pi[i-1];
		  while(pi[i] > 0 && t[i] != t[pi[i]]) pi[i] = pi[pi[i]-1];
		  if(t[i] == t[pi[i]]) pi[i]++;
	  }
  }

  void matching(string s){
	  int j = 0;
	  int n = s.size();
	  for(int i=0; i<n; i++){
		  while(j > 0 && s[i] != t[j]) j = pi[j-1];
		  if(s[i] == t[j]) j++;
		  if(j == t.size()){
			  matches.push_back(i-t.size()+1);
			  j = pi[j-1];
		  }
	  }
  }
  
};
