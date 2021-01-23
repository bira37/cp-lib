struct Vector2D {
  int x, y;
  Vector2D() {}
  Vector2D(int x, int y) : x(x), y(y) {}
 
  bool operator<(Vector2D v) const { return tie(x, y) < tie(v.x, v.y); }
  bool operator==(Vector2D v) const { return tie(x, y) == tie(v.x, v.y); }
  bool operator>(Vector2D v) const { return tie(x, y) > tie(v.x, v.y); }
  bool operator<=(Vector2D v) const { return tie(x, y) <= tie(v.x, v.y); }
  bool operator>=(Vector2D v) const { return tie(x, y) >= tie(v.x, v.y); }
 
  Vector2D normalize() {
    if (x == 0) {
      return Vector2D(0, 1);
    }
    if (y == 0) {
      return Vector2D(1, 0);
    }
    int g = gcd(x, y);
    Vector2D norm(x / g, y / g);
    if (norm.y < 0) norm.x = -norm.x, norm.y = -norm.y;
    return norm;
  }
  Vector2D normalized_orthogonal() {
    if (x == 0) {
      return Vector2D(1, 0);
    }
    if (y == 0) {
      return Vector2D(0, 1);
    }
    int g = gcd(x, y);
    Vector2D ort = Vector2D(-y / g, x / g);
    if (ort.y < 0) ort.x = -ort.x, ort.y = -ort.y;
    return ort;
  }
};
