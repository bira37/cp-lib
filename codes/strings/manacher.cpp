// Finds all Palindromes with odd and even length
struct Manacher{
  
  vector<int> d_e, d_o;
  Manacher(){}
  
  Manacher(int n){
    d_e.resize(n);
    d_o.resize(n);
  }
  
  void calculate(string & s){
    
    int n = d_e.size();
    //calculate for odd
    for (int i = 0, l = 0, r = -1; i < n; i++) {
      d_o[i] = (i > r) ? 1 : min(d_o[l + r - i], r - i + 1);
      while(i - d_o[i] >= 0 and i + d_o[i] < n and s[i-d_o[i]] == s[i+d_o[i]]) d_o[i]++;
      if(i + d_o[i]-1 > r){
        l = i-d_o[i]+1;
        r = i+d_o[i]-1;
      }
    }
    
    //calculate for even
    for (int i = 0, l = 0, r = -1; i < n; i++) {
      d_e[i] = (i > r) ? 0 : min(d_e[l + r - i + 1], r - i + 1);
      while(i - d_e[i] - 1 >= 0 and i + d_e[i] < n and s[i-d_e[i]-1] == s[i+d_e[i]]) d_e[i]++;
      if(i + d_e[i]-1 > r){
        l = i-d_e[i];
        r = i+d_e[i]-1;
      }
    }
    
  }
  
};
