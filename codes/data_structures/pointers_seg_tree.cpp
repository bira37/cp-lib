/* Segment Tree implementation using pointers */
/* Can be adapted to Persistent Segment Tree */

struct node {
	node *left, *right;
	//attributes of node
	node() {
		//initialize attributes
		left = NULL;
		right = NULL;
	}
};
void combine(node *ans, node *left, node *right){
	//combine operation
}
void build(node *root, int l, int r){
	if(l == r){
		root->sum = v[l];
		return;
	}
	int m = (l+r) >> 1;
	if(!root->left) root->left = new node();
	if(!root->right) root->right = new node();
	build(root->left, l, m);
	build(root->right, m+1, r);
	combine(root, root->left, root->right);
}

void update(node *root, int l, int r, int idx, int val){
	if(l == r && l == idx){
		//do leaf operation
		return;
	}
	int m = (l+r) >> 1;
	if(idx <= m){
		if(!root->left) root->left = new node();
		update(root->left, l, m, idx, val);
	}
	else {
		if(!root->right) root->right = new node();
		update(root->right, m+1, r, idx, val);
	}
	combine(root, root->left, root->right);
}

node* query(node *root, int l, int r, int a, int b){
	if(l == a && r == b){
		return root;
	}
	int m = (l+r) >> 1;
	if(b <= m){
		if(!root->left) root->left = new node();
		return query(root->left, l, m, a, b);
	}
	else if(m < a){
		if(!root->right) root->right = new node();
		return query(root->right, m+1, r, a, b);
	}
	if(!root->left) root->left = new node();
	if(!root->right) root->right = new node();
	node *left = query(root->left, l,m,a,m);
	node *right = query(root->right, m+1, r, m+1, b);
	node *ans = new node();
	combine(ans, left, right);
	return ans;
}
