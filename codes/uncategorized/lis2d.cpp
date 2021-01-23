/* Author: Ubiratan Correia Barbosa Neto
 * Longest Increasing Subsequence 2D
 */

struct LIS2D {
  struct node {
    node *left, *right;
    int mx = (int)1e18 + 1;
    node() {
      mx = (int)1e18 + 1;
      left = NULL;
      right = NULL;
    }
  };

  LIS2D() {}

  vector<node *> lis;
  int L, R, size;

  void combine(node *ans, node *left, node *right) {
    if (left && right)
      ans->mx = min(left->mx, right->mx);
    else if (left)
      ans->mx = left->mx;
    else if (right)
      ans->mx = right->mx;
    else
      ans->mx = (int)1e18 + 1;
  }

  void update(node *root, int l, int r, int idx, int val) {
    if (l == r) {
      root->mx = min(root->mx, val);
      return;
    }
    int m = (l + r) >> 1;
    if (idx <= m) {
      if (!root->left) root->left = new node();
      update(root->left, l, m, idx, val);
    } else {
      if (!root->right) root->right = new node();
      update(root->right, m + 1, r, idx, val);
    }
    combine(root, root->left, root->right);
  }

  int query(node *root, int l, int r, int a, int b) {
    if (l == a && r == b) {
      return root->mx;
    }
    int m = (l + r) >> 1;
    if (b <= m) {
      if (!root->left)
        return (int)1e18 + 1;
      else
        return query(root->left, l, m, a, b);
    } else if (m < a) {
      if (!root->right)
        return (int)1e18 + 1;
      else
        return query(root->right, m + 1, r, a, b);
    }
    int left = (int)1e18 + 1;
    int right = (int)1e18 + 1;
    if (root->left) left = query(root->left, l, m, a, m);
    if (root->right) right = query(root->right, m + 1, r, m + 1, b);
    return min(left, right);
  }

  bool check(int id, int x, int y) {
    int val = query(lis[id], L, R, L, x - 1);
    return val < y;
  }

  void calculate(vector<ii> &v) {
    int n = v.size();
    lis.resize(n + 1);
    set<int> sx;
    vector<int> aux;
    for (int i = 0; i < n; i++) {
      sx.insert(v[i].ff);
    }
    for (int x : sx) aux.pb(x);
    L = -1, R = sx.size();
    for (int i = 0; i < n; i++) {
      v[i].ff = lower_bound(aux.begin(), aux.end(), v[i].ff) - aux.begin();
    }
    for (int i = 0; i <= n; i++) {
      lis[i] = new node();
    }
    update(lis[0], L, R, L, -(int)1e18 - 1);
    size = 0;
    for (ii par : v) {
      int x = par.ff, y = par.ss;
      int l = 0, r = n - 1;
      int ans = 0;
      while (l <= r) {
        int m = (l + r) >> 1;
        if (check(m, x, y)) {
          ans = m;
          l = m + 1;
        } else
          r = m - 1;
      }
      size = max(size, ans + 1);
      update(lis[ans + 1], L, R, x, y);
    }
  }
};

int32_t main() {
  int n;
  scanf("%d", &n);
  vector<ii> v(n);
  set<int> sx;
  vector<int> aux;
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &v[i].ff, &v[i].ss);
  }
  LIS2D lis2d;
  lis2d.calculate(v);
  printf("%d\n", lis2d.size);
}
