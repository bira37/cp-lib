/* Range Update Binary Indexed Tree Implementation */
/* Tree is 1 - index */
/* Point Update Binary Indexed Tree operations are used as auxiliar */
/* N is defined as the maximum number of elements (given by the statement) */

#define N MAX_INPUT

int bit[2][N+1];

void init(int n){
	for(int i=1; i<=n; i++){
		bit[0][i] = 0;
		bit[1][i] = 0;
	}
}

//auxiliar functions

void update(int *bit, int idx, int val, int n){
	for(int i = idx; i <= n; i += i&-i){
		bit[i]+=val;
	}
}

int query(int *bit, int idx){
	int ans = 0;
	for(int i=idx; i>0; i -= i&-i){
		ans += bit[i];
	}
	return ans;
}

//end of auxiliar functions

void range_update(int l, int r, int val, int n){
	update(bit[0], l, val, n);
	update(bit[0], r+1, -val, n);
	update(bit[1], l, val*(l-1), n);
	update(bit[1], r+1, -val*r, n);
}

int prefix_query(int idx){
	return query(bit[0],idx)*idx - query(bit[1], idx);
}

int range_query(int l, int r){
	return prefix_query(r) - prefix_query(l-1);
}
