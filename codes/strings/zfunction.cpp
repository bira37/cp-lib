/* Z-function */
/* Calculate the size K of the largest substring which is a prefix */

vector<int> z;
	
void make(string s){
	int n = s.size();
	z.resize(n);
	z[0] = 0;
	int l = 0, r = 0;
	for(int i=1; i<n; i++){
		if(i > r){
			l = i;
			r = i;
		}
		z[i] = min(z[i-l], r-i+1);
		while(i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
		if(i + z[i] > r){
			l = i;
			r = i + z[i]-1;
		}
	}
}
