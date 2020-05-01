/* Author: Ubiratan Correia Barbosa Neto
 * 3D Rotation
 */

struct Vec3d {
  double x, y, z;
  Vec3d operator+(const Vec3d& rhs) const {
    return {x + rhs.x, y + rhs.y, z + rhs.z};
  }
  Vec3d operator*(const double k) const { return {k * x, k * y, k * z}; }
  Vec3d operator-(const Vec3d& rhs) const { return *this + rhs * -1; }
  Vec3d operator/(const double k) const { return {x / k, y / k, z / k}; }
  double operator*(const Vec3d& rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z;
  }
  double norm_sq() { return (*this) * (*this); }
  double norm() { return sqrt(norm_sq()); }
};

Vec3d rotate(Vec3d p, Vec3d u /*unit vector*/, double ang) {
  double dot = p * u;
  double co = cos(ang);
  double si = sin(ang);
  double x = u.x * dot * (1 - co) + p.x * co + (u.y * p.z - u.z * p.y) * si;
  double y = u.y * dot * (1 - co) + p.y * co + (u.z * p.x - u.x * p.z) * si;
  double z = u.z * dot * (1 - co) + p.z * co + (u.x * p.y - u.y * p.x) * si;
  return {x, y, z};
}
