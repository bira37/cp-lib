namespace PersistentSegmentTree {

struct Node {
  Node *left, *right;
  int x;
  Node() {
    left = nullptr;
    right = nullptr;
    x = 0;
  }

  Node(Node* n) {
    left = n->left;
    right = n->right;
    x = n->x;
  }
};

Node* update(Node* cur, int l, int r, int x, int val) {
  assert(cur != nullptr);
  Node* new_cur = new Node(cur);
  if (l == r) {
    new_cur->x = val;
    return new_cur;
  }

  int m = (l + r) >> 1;
  if (x <= m) {
    if (!new_cur->left) new_cur->left = new Node();
    new_cur->left = update(new_cur->left, l, m, x, val);
  } else {
    if (!new_cur->right) new_cur->right = new Node();
    new_cur->right = update(new_cur->right, m + 1, r, x, val);
  }
  new_cur->x = max((new_cur->left ? new_cur->left->x : 0),
                   (new_cur->right ? new_cur->right->x : 0));
  return new_cur;
}

int query(Node* cur, int l, int r, int a, int b) {
  assert(cur != nullptr);
  if (r < a || b < l) return 0;
  if (a <= l and r <= b) return cur->x;
  int m = (l + r) >> 1;
  int ansl = 0, ansr = 0;
  if (cur->left) ansl = query(cur->left, l, m, a, b);
  if (cur->right) ansr = query(cur->right, m + 1, r, a, b);
  return max(ansl, ansr);
}

};  // namespace PersistentSegmentTree
