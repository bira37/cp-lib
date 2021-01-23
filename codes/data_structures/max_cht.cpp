/* Author: Ubiratan Neto
 * Max CHT Example (Suppose that lines are added in crescent order of a)
 */
struct ConvexHullTrick {
  ConvexHullTrick() {}
  struct Line {
    int id, a, b;
    Line() {}
    Line(int id, int a, int b) : id(id), a(a), b(b) {}
  };
  bool remove(Line& a, Line& b, Line& c) {
    if ((a.a - c.a) * (c.b - b.b) <= (b.a - c.a) * (c.b - a.b))
      return true;
    else
      return false;
  }
  vector<Line> cht;
  void add(Line& v) {
    if (cht.empty()) {
      cht.push_back(v);
    } else {
      if (cht.back().a == v.a) return;
      while (cht.size() > 1 && remove(cht[cht.size() - 2], cht.back(), v)) {
        cht.pop_back();
      }
      cht.push_back(v);
    }
  }

  void preprocess_cht(vector<Line>& v) {
    sort(v.begin(), v.end(), [](const Line& a, const Line& b) {
      return (a.a < b.a || (a.a == b.a && a.b > b.b));
    });
    cht.clear();
    for (int i = 0; i < v.size(); i++) {
      add(v[i]);
    }
  }

  int f(int i, int x) { return cht[i].a * x + cht[i].b; }

  // return Line index
  ii query(int x) {
    if (cht.size() == 0) return ii(-INF, -INF);
    if (cht.size() == 1) return ii(f(0, x), cht[0].id);
    int l = 0, r = cht.size() - 2;
    int ans = cht.size() - 1;
    while (l <= r) {
      int m = (l + r) / 2;
      int y1 = f(m, x);
      int y2 = f(m + 1, x);
      if (y1 >= y2) {
        ans = m;
        r = m - 1;
      } else
        l = m + 1;
    }
    return ii(f(ans, x), cht[ans].id);
  }
};
