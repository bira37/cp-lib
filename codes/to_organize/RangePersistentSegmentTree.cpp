struct node {
	node *left, *right;
	int sum,lazy;
	node() {
		sum = 0;
		lazy = 0;
		left = NULL;
		right = NULL;
	}
};

void combine(node *ans, node *left, node *right){
	ans->sum = left->sum + right->sum;
}

void build(node *root, int l, int r){
	if(l == r){
		return;
	}
	int m = (l+r) >> 1;
	if(!root->left) root->left = new node();
	if(!root->right) root->right = new node();
	build(root->left, l, m);
	build(root->right, m+1, r);
	combine(root, root->left, root->right);
}

void propagate(node *root, int l, int r){
	if(root->lazy == 0) return;
	root->sum += (r-l+1)*root->lazy;
	if(l != r){
		root->left->lazy += root->lazy;
		root->right->lazy += root->lazy;
	}
	root->lazy = 0;
}

node* update(node *root, int l, int r, int a, int b, int val){
	propagate(root, l, r);
	if(l == a && r == b){
		root->lazy += val;
		return root;
	}
	int m = (l+r) >> 1;
	node * new_root = new node();
	new_root->left = root->left;
	new_root->right = root->right;
	new_root->sum = root->sum;
	new_root->lazy = root->lazy;
	if(b <= m){
		if(!new_root->left) new_root->left = new node();
		new_root->left = update(new_root->left, l, m, a, b, val);
	}
	else if(m < a){
		if(!new_root->right) new_root->right = new node();
		new_root->right = update(new_root->right, m+1, r, a, b, val);
	}
	else {
		new_root->left = update(new_root->left, l, m, a, m, val);
		new_root->right = update(new_root->right, m+1, r, m+1, b, val);
	}
	propagate(new_root->left, l, m);
	propagate(new_root->right, m+1, r);
	combine(new_root, new_root->left, new_root->right);
	return new_root;
}

node* query(node *root, int l, int r, int a, int b){
	propagate(root, l, r);
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

vector< node* > root;
