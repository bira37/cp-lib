/* Knuth - Morris - Pratt Algorithm */
/* Failure Function for String Matching */


int pi[N];
string s, t;

void prefix(int n) {
	pi[0] = 0;
	for(int i = 1; i < n; i++) {
		pi[i] = pi[i-1];
		while(pi[i] > 0 && t[i] != t[pi[i]]) pi[i] = pi[pi[i]-1];
		if(t[i] == t[pi[i]]) pi[i]++;
	}
}

void matching(int n){
	int j = 0;
	for(int i=0; i<n; i++){
		while(j > 0 && s[i] != t[j]) j = pi[j-1];
		if(s[i] == t[j]) j++;
		if(j == t.size()){
			cout << "match in " << j-t.size()+1 << endl;
			j = pi[j-1];
		}
	}
}
