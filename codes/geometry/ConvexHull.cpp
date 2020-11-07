/* Author: Ubiratan Correia Barbosa Neto
 * Convex Hull
 */

namespace Geo2D {

struct ConvexHull {
  vector<Point> points, lower, upper;

  ConvexHull() {}

  void calculate(vector<Point> v) {
    sort(v.begin(), v.end());
    lower.clear();
    upper.clear();
    if (v.size() < 3) {
      for (Point p : v) upper.pb(p), lower.pb(p);
      return;
    }
    for (int i = 0; i < v.size(); i++) {
      while (upper.size() >= 2 &&
             (Point(upper[upper.size() - 2], upper.back()) ^
              Point(upper.back(), v[i])) >= 0LL)
        upper.pop_back();
      upper.push_back(v[i]);
    }
    reverse(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
      while (lower.size() >= 2 &&
             (Point(lower[lower.size() - 2], lower.back()) ^
              Point(lower.back(), v[i])) >= 0LL)
        lower.pop_back();
      lower.push_back(v[i]);
    }
    for (int i = upper.size() - 2; i >= 0; i--) points.push_back(upper[i]);
    for (int i = lower.size() - 2; i >= 0; i--) points.push_back(lower[i]);
    reverse(lower.begin(), lower.end());
  }

  double area() {
    double area = points.back().x * points[0].y - points.back().y * points[0].x;
    for (int i = 0; i < points.size() - 1; i++) {
      area += points[i].x * points[i + 1].y - points[i].y * points[i + 1].x;
    }
    return area / 2.;
  }

  int area2() {
    int area2 = points.back().x * points[0].y - points.back().y * points[0].x;
    for (int i = 0; i < points.size() - 1; i++) {
      area2 += points[i].x * points[i + 1].y - points[i].y * points[i + 1].x;
    }
    return area2;
  }

  double perimeter() {
    double val = Point(points[0], points.back()).size();
    for (int i = 0; i < points.size() - 1; i++) {
      val += Point(points[i], points[i + 1]).size();
    }
    return val;
  }

  bool insideHull(Point p) {
    auto it = lower_bound(lower.begin(), lower.end(), p);
    if (it != lower.end() && *it == p) return true;
    it = lower_bound(upper.begin(), upper.end(), p);
    if (it != upper.end() && *it == p) return true;

    if (p.x == upper[0].x) {
      if (p.y > upper[0].y) {
        // upper
        if (upper[1].x != upper[0].x)
          return false;
        else if (p.y <= upper[1].y)
          return true;
      } else {
        // lower
        if (lower[1].x != lower[0].x)
          return false;
        else if (p.y >= lower[1].y)
          return true;
      }
      return false;
    }
    Point v1, v2;
    // upper or lower
    int ansu = -1, ansl = -1;
    int l = 0, r = upper.size() - 2;
    while (l <= r) {
      int m = (l + r) >> 1LL;
      if (upper[m].x < p.x && p.x <= upper[m + 1].x) {
        ansu = m;
        break;
      } else if (upper[m + 1].x < p.x)
        l = m + 1;
      else
        r = m - 1;
    }
    l = 0, r = lower.size() - 2;
    while (l <= r) {
      int m = (l + r) >> 1LL;
      if (lower[m].x < p.x && p.x <= lower[m + 1].x) {
        ansl = m;
        break;
      } else if (lower[m + 1].x < p.x)
        l = m + 1;
      else
        r = m - 1;
    }
    if (ansu == -1 || ansl == -1) return false;
    bool oku = false, okl = false;
    v1 = Point(upper[ansu], upper[ansu + 1]);
    v2 = Point(upper[ansu], p);
    oku = ((v1 ^ v2) <= 0);
    v1 = Point(lower[ansl], lower[ansl + 1]);
    v2 = Point(lower[ansl], p);
    okl = ((v1 ^ v2) >= 0);
    if (oku && okl)
      return true;
    else
      return false;
  }
  
  int _f_dot_product(Point a, Point b) { return a.x * b.x + a.y * b.y; }
  int _maximize_dot_product(Point p, const vector<Point>& envelope) {
    if (envelope.size() < 3) {
      int result = -INF;
      for (Point q : envelope) {
        result = max(result, _f_dot_product(p, q));
      }
      return result;
    }
    int l = 0, r = envelope.size() - 2;
    int ans = 0;
    while (l <= r) {
      int m1 = (l + r) >> 1;
      int m2 = m1 + 1;
      if (_f_dot_product(p, envelope[m1]) <= _f_dot_product(p, envelope[m2])) {
        l = m1 + 1;
      } else {
        ans = m1;
        r = m1 - 1;
      }
    }
    int result = max(_f_dot_product(p, envelope.front()),
                     _f_dot_product(p, envelope.back()));
    result = max(result, _f_dot_product(p, envelope[ans]));
    result = max(result, _f_dot_product(p, envelope[ans + 1]));
    return result;
  }

  int max_dot_product(Point p) {
    if (p.y < 0) {
      return _maximize_dot_product(p, lower);
    } else {
      return _maximize_dot_product(p, upper);
    }
  }
};

}  // namespace Geo2D
