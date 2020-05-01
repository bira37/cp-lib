/* Author: Ubiratan Correia Barbosa Neto
 * Mos Algorithm Structure
 */

namespace Mos {

int sqr;

struct query {
  int id, l, r, ans;
  bool operator<(const query& b) const {
    if (l / sqr != b.l / sqr) return l / sqr < b.l / sqr;
    return (l / sqr) % 2 ? r > b.r : r < b.r;
  }
};

struct QueryDecomposition {
  vector<query> q;

  QueryDecomposition(int n, int nq) {
    q.resize(nq);
    sqr = (int)sqrt(n);
  }

  void read() {}

  void add(int idx) {}

  void remove(int idx) {}

  int answer_query() {}

  void calculate() {
    sort(q.begin(), q.end());
    int l = 0, r = -1;
    for (int i = 0; i < q.size(); i++) {
      while (q[i].l < l) add(--l);
      while (r < q[i].r) add(++r);
      while (q[i].l > l) remove(l++);
      while (r > q[i].r) remove(r--);
      q[i].ans = answer_query();
    }
  }

  void print() {
    sort(q.begin(), q.end(),
         [](const query& a, const query& b) { return a.id < b.id; });

    for (query x : q) {
      cout << x.ans << endl;
    }
  }
};

}  // namespace Mos
