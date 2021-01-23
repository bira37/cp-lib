/* Author: Ubiratan Neto
 * LiChao with Doubles
 */

namespace Lichao {

struct Line {
  double a, b;
  Line() {
    a = 0;
    b = INF;
  }
  Line(double a, double b) : a(a), b(b) {}
  double eval(double x) { return a * x + b; }
};

struct node {
  node *left, *right;
  Line ln;
  node() {
    left = NULL;
    right = NULL;
  }
};

struct Tree {
  node* root;

  Tree() { root = new node(); }

  void add(node* root, double l, double r, Line ln) {
    if (!root->left) root->left = new node();
    if (!root->right) root->right = new node();
    double m = (l + r) / 2.;
    bool left = ln.eval(l) < (root->ln).eval(l);
    bool mid = ln.eval(m) < (root->ln).eval(m);

    if (mid) {
      swap(root->ln, ln);
    }

    if (abs(r - l) <= 1e-9)
      return;
    else if (left != mid)
      add(root->left, l, m, ln);
    else
      add(root->right, m, r, ln);
  }

  double query(node* root, double l, double r, double x) {
    if (!root->left) root->left = new node();
    if (!root->right) root->right = new node();
    double m = (l + r) / 2.;
    if (abs(r - l) <= 1e-9)
      return (root->ln).eval(x);
    else if (x < m)
      return min((root->ln).eval(x), query(root->left, l, m, x));
    else
      return min((root->ln).eval(x), query(root->right, m, r, x));
  }
};

}  // namespace Lichao
