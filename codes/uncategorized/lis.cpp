/* Longest Increasing Subsequence Implementation */
/* N is defined as the maximum array size given by the statement */

#define N MAX_N

int v[N];
int lis[N+1];

void calculate_lis(int n){
	for(int i=1; i<=n; i++) lis[i] = INT_MAX;
	lis[0] = INT_MIN;
	for(int i=0; i<n; i++){
		int index = lower_bound(lis, lis+n+1, v[i]) - lis;
		index--;
		lis[index+1] = min(lis[index+1], v[i]);
	}
} 
	
