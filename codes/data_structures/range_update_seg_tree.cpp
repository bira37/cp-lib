/* Range update Segment Tree Implementation */
/* The first node (ROOT) is defined to 1 (1 - index impl) */
/* N is the maximum number of elements given by the statement */
/* Lazy can be inside node structure instead of being another structure */

#define ROOT 1
#define N MAX_INPUT

struct node{
	//attributes of node
};

node tree[4*N];
node lazy[4*N];

node combine(node a, node b){
	node res;
	//combine operations
	return res;
}

void propagate(int root, int l , int r){
	//return if there is no update
	//update tree using lazy node
	if(l != r){
		//propagate for left and right child
	}
	//reset lazy node
}

void range_update(int root, int l, int r, int a, int b, long long val){
	if(l == a && r == b){
		//lazy operation using val
		return;
	}
	
	int m = (l+r)/2;
	
	if(b <= m) range_update(2*root, l, m, a, b, val);
	else if(m < a) range_update(2*root+1, m+1, r, a, b, val);
	else {
		range_update(2*root, l, m, a, m, val);
		range_update(2*root+1, m+1, r, m+1, b, val);
	}
	
	propagate(root, l , r);
	propagate(2*root, l, m);
	propagate(2*root+1, m+1, r);
	tree[root] = combine(tree[2*root], tree[2*root+1]);
}

node query(int root, int l, int r, int a, int b){
	propagate(root, l, r);
	if(l == a && r == b) return tree[root];
	
	int m = (l+r)/2;
	if(b <= m) return query(2*root, l, m, a, b);
	else if(m < a) return query(2*root+1, m+1, r, a, b);
	else {
		node left = query(2*root, l, m, a, m);
		node right = query(2*root+1, m+1, r, m+1, b);
		node ans = combine(left, right);
		return ans;
	}
}
