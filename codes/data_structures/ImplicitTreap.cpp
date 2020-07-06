/* Author: Ubiratan Neto */
/* Implicit Treap */
/* Example with Range Sum Query / Range Sum Update */

namespace Treap {
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
  Node *l, *r;
  int prior;
  int sz;

  /* Edit here */
  int sum;
  int lazy;
  int val;

  Node(int x = -1) {
    prior = rng();
    sz = 1;
    l = nullptr;
    r = nullptr;

    /* Problem Info */
    sum = x;
    val = x;
    lazy = 0;
  }

  Node(Node *n) {
    prior = n->prior;
    sz = n->sz;
    l = n->l;
    r = n->r;

    /* Problem Info */
    sum = n->sum;
    val = n->val;
    lazy = n->lazy;
  }
};

void combine(Node *root) {
  int left = 0, right = 0;
  if (root->l) left = root->l->sum;
  if (root->r) right = root->r->sum;
  root->sum = root->val + left + right;
}

int get_sz(Node *root) { return root ? root->sz : 0; }

void update_sz(Node *root) {
  if (root) root->sz = get_sz(root->l) + 1 + get_sz(root->r);
}

void propagate(Node *root) {
  // Check if lazy exists
  if (!root || !root->lazy) return;

  // Apply lazy to current node
  root->val += root->lazy;
  root->sum += (root->lazy) * get_sz(root);

  // Propagate
  if (root->l) root->l->lazy += root->lazy;
  if (root->r) root->r->lazy += root->lazy;

  // Reset lazy
  root->lazy = 0;
}

void apply(Node *root) {
  if (!root) return;
  update_sz(root);
  propagate(root->l);
  propagate(root->r);
  combine(root);
}

void split(Node *root, Node *&l, Node *&r, int pos) {
  if (!root) {
    l = nullptr;
    r = nullptr;
    return;
  }
  propagate(root);
  if (get_sz(root->l) <= pos) {
    split(root->r, root->r, r, pos - get_sz(root->l) - 1);
    l = root;
  } else {
    split(root->l, l, root->l, pos);
    r = root;
  }
  apply(root);
}

void merge(Node *&root, Node *l, Node *r) {
  propagate(l);
  propagate(r);
  if (!l || !r)
    root = (l ? l : r);
  else if (l->prior > r->prior) {
    merge(l->r, l->r, r);
    root = l;
  } else {
    merge(r->l, l, r->l);
    root = r;
  }
  apply(root);
}

Node *get(Node *&root, int l, int r = -1) {
  if (r == -1) r = l;

  Node *L, *R, *M;
  split(root, L, M, l - 1);
  split(M, M, R, r - l);
  Node *ret = new Node(M);
  merge(L, L, M);
  merge(root, L, R);

  return ret;
}

void update(Node *&root, int x, int l, int r = -1) {
  if (r == -1) r = l;

  Node *L, *R, *M;
  split(root, L, M, l - 1);
  split(M, M, R, r - l);

  /* Alter below */
  M->lazy += x;
  /* Alter above*/

  merge(L, L, M);
  merge(root, L, R);
}

void insert_after(Node *&root, int i, int x) {
  Node *L, *R;
  split(root, L, R, i);
  Node *new_node = new Node(x);
  merge(L, L, new_node);
  merge(root, L, R);
}

void insert_before(Node *&root, int i, int x) {
  Node *L, *R;
  split(root, L, R, i - 1);
  Node *new_node = new Node(x);
  merge(L, L, new_node);
  merge(root, L, R);
}

Node *remove(Node *&root, int i) {
  Node *L, *R, *M;
  split(root, L, R, i - 1);
  split(R, M, R, 0);
  Node *ret = new Node(M);
  merge(root, L, R);
  return ret;
}

};  // namespace Treap
