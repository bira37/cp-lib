namespace RangeDynamicSegmentTree {

struct Node {
  Node *left, *right;
  int x = 0;
  int lazy = 0;
  Node() {
    left = nullptr;
    right = nullptr;
    x = 0;
    lazy = 0;
  }

  Node(Node* n) {
    left = n ? n->left : nullptr;
    right = n ? n->right : nullptr;
    x = n ? n->x : 0;
    lazy = n ? n->lazy : 0;
  }
};

void push(Node* cur, int l, int r) {
  if (!cur) return;
  if (!cur->lazy) return;
  cur->x += cur->lazy;
  if (l != r) {
    cur->left = new Node(cur->left);
    cur->left->lazy += cur->lazy;

    cur->right = new Node(cur->right);
    cur->right->lazy += cur->lazy;
  }
  cur->lazy = 0;
}

void merge(Node* cur) {
  cur->x =
      max((cur->left ? cur->left->x : 0), (cur->right ? cur->right->x : 0));
}

Node* update(Node* cur, int l, int r, int a, int b, int val) {
  assert(cur != nullptr);
  Node* new_cur = new Node(cur);
  push(new_cur, l, r);
  if (l == a && b == r) {
    new_cur->lazy += val;
    push(new_cur, l, r);
    return new_cur;
  }

  int m = (l + r) >> 1;
  if (b <= m) {
    if (!new_cur->left) new_cur->left = new Node();
    new_cur->left = update(new_cur->left, l, m, a, b, val);
    push(new_cur->right, m + 1, r);
  } else if (m < a) {
    if (!new_cur->right) new_cur->right = new Node();
    new_cur->right = update(new_cur->right, m + 1, r, a, b, val);
    push(new_cur->left, l, m);
  } else {
    if (!new_cur->left) new_cur->left = new Node();
    if (!new_cur->right) new_cur->right = new Node();
    new_cur->left = update(new_cur->left, l, m, a, m, val);
    new_cur->right = update(new_cur->right, m + 1, r, m + 1, b, val);
  }

  merge(new_cur);
  return new_cur;
}

int query(Node* cur, int l, int r, int a, int b) {
  assert(cur != nullptr);
  if (r < a || b < l) return 0;
  push(cur, l, r);
  if (a <= l and r <= b) {
    return cur->x;
  }
  int m = (l + r) >> 1;
  int ansl = 0, ansr = 0;
  if (cur->left) ansl = query(cur->left, l, m, a, b);
  if (cur->right) ansr = query(cur->right, m + 1, r, a, b);
  return max(ansl, ansr);
}

};  // namespace RangeDynamicSegmentTree
