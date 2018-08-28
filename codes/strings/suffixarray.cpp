/* Suffix Array using Counting Sort Implementation */
/* rnk is inverse of sa array */
/* aux arrays are needed for sorting step */
/* inverse sorting (using rotating arrays and blocks of power of 2) */
/* rmq data structure needed for calculating lcp of two non adjacent suffixes sorted */

struct SuffixArray{
  
  vector<int> rnk,tmp,sa, sa_aux, lcp;
  
  int block, n;
  
  string s;
  
  SuffixArray() {}
  
  SuffixArray(string t){
    s = t;
    n = t.size();
    rnk.resize(n+1);
    tmp.resize(max(257LL, n+1));
    sa.resize(n+1);
    sa_aux.resize(n+1);
    lcp.resize(n+1);
    block = 0;
  }

  bool suffixcmp(int i, int j){ 
	  if(rnk[i] != rnk[j]) return rnk[i] < rnk[j];
	  i+=block, j+=block;
	  i%=n;
	  j%=n;
	  return rnk[i] < rnk[j];
  }

  void suffixSort(int MAX_VAL){
    for(int i=0; i<=MAX_VAL; i++) tmp[i] = 0;
    for(int i=0; i<n; i++) tmp[rnk[i]]++;
    for(int i=1; i<=MAX_VAL; i++) tmp[i] += tmp[i-1];
    for(int i = n-1; i>=0; i--){
        int aux = sa[i]-block;
        aux%=n;
        if(aux < 0) aux+=n;
        sa_aux[--tmp[rnk[aux]]] = aux;
    }
    for(int i=0; i<n; i++) sa[i] = sa_aux[i];
    tmp[0] = 0;
	  for(int i=1; i<n; i++) tmp[i] = tmp[i-1] + suffixcmp(sa[i-1], sa[i]);
	  for(int i=0; i<n; i++) rnk[sa[i]] = tmp[i];
  }

  void calculate(){ 
	  s+='\0';
	  n++;
	  for(int i=0; i<n; i++){
		  sa[i] = i;
		  rnk[i] = s[i];
		  tmp[i] = 0;
	  }
	  suffixSort(256);
	  block = 1;
	  while(tmp[n-1] != n-1){
		  suffixSort(tmp[n-1]);
		  block*=2;
	  }
	  for(int i=0; i<n-1; i++) sa[i] = sa[i+1];
	  n--;
	  tmp[0] = 0;
	  for(int i=1; i<n; i++) tmp[i] = tmp[i-1] + suffixcmp(sa[i-1], sa[i]);
	  for(int i=0; i<n; i++) rnk[sa[i]] = tmp[i];
	  s.pop_back();
  }

  void calculate_lcp(){
	  int last = 0;
	  for(int i=0; i<n; i++){
		  if(rnk[i] == n-1) continue;
		  int x = rnk[i];
		  lcp[x] = max(0LL,last-1);
		  while(sa[x] + lcp[x] < n && sa[x+1] + lcp[x] < n && s[sa[x]+lcp[x]] == s[sa[x+1]+lcp[x]]){
			  lcp[x]++;
		  }
		  last = lcp[x];
	  }
  }
  
  void build_lcp() {} // todo
  
  int lcp(int x, int y){
	  if(x == y) return n - x;
	  if(rnk[x] > rnk[y]) swap(x,y);
	  return rmq(rnk[x], rnk[y]-1);
  }

};
