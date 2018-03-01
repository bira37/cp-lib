void precompute(int* b, string & pattern){
	int i=0, j=-1;
	b[i] = j;
	while(i < pattern.size()){
		while(j>=0 && pattern[i] != pattern[j]) j = b[j];
		i++;
		j++;
		b[i] = j;
	}
}

int kmp(int * b, string & str, string & pattern){
	int i=0, j=0;
	while(i<str.size()){ 
		while(j >=0 && c != pattern[j]) j = b[j];
		j++;
		if(j == pattern.size()){
			cout << i-j+1 << endl;
			j = b[j];
		}
		i++;
	}
}
		
