/* Suffix Array using Counting Sort Implementation */
/* rnk is inverse of sa array */
/* aux arrays are needed for sorting step */
/* inverse sorting (using rotating arrays and blocks of power of 2) */
/* rmq data structure needed for calculating lcp of two non adjacent suffixes sorted */
  
int rnk[N],tmp[N], sa[N], sa_aux[N], lcp[N];
int block=0, n;
string s;

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

void build_sa(){ 
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
}

void calculate_lcp(){
	int last = 0;
	for(int i=0; i<n; i++){
		if(rnk[i] == n-1) continue;
		int x = rnk[i];
		lcp[x] = max(0,last-1);
		while(sa[x] + lcp[x] < n && sa[x+1] + lcp[x] < n && s[sa[x]+lcp[x]] == s[sa[x+1]+lcp[x]]){
			lcp[x]++;
		}
		last = lcp[x];
	}
}

int lcp(int x, int y){
	if(x == y) return n - x;
	if(rnk[x] > rnk[y]) swap(x,y);
	return rmq(rnk[x], rnk[y]-1);
}
