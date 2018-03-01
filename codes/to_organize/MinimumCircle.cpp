#include <bits/stdc++.h>
using namespace std;
 
typedef complex<double> point;
#define x real()
#define y imag()
#define EX(p) p.first,p.second
#define PT(a) const point & a
#define LINE(a,b) PT(a),PT(b)
#define SEG(a,b) LINE(a,b)
#define HPLANE(a,b) LINE(a,b)
#define CIRCLE(a,b) PT(a), double b
 
const double PI = acos(-1);
const double EPS = 1e-9;
 
int dcmp(double a, double b = 0){
  if(a+EPS < b) return -1;
  else if(b+EPS < a) return 1;
  return 0;
}
 
// basics
// returned angles are in [0, 2pi] for absolute or [-pi, pi] for relative
// arg(v) returns angle of the vector
// norm(v) returns squared norm of the vector
// abs(v) returns norm of the vector
// polar to cartesian polar(norm, arg)
// cartesian to polar point(abs(v), arg(v))
// all signed areas and angles are ccw-positive
double dot(PT(a), PT(b)){ return (conj(a)*b).x; }
double cross(PT(a), PT(b)) { return (conj(a)*b).y; }
int ccw(PT(o), PT(a), PT(b)) { return dcmp(cross(a-o, b-o)); }
point rotate(PT(a), double theta) {
  return a*polar(1.0, theta);
}
point ortho(PT(v)){ return point(-v.y, v.x); }
point normalize(PT(p), double k=1.0){
  return !dcmp(abs(p)) ? point(0,0) : p/abs(p)*k;
}
 
bool collinear(PT(a), PT(b), PT(c)){
  return !ccw(a,b,c);
}
 
point proj(PT(p), PT(v)){
  return dot(p,v) * v / norm(v);
}
 
point reflect(PT(p), LINE(a, b)){
  return a + conj((p - a) / (b - a)) * (b - a);
}
 
double sig_angle(PT(a), PT(o), PT(b)){ // signed smallest angle
  return remainder(arg(b-o) - arg(a-o), 2.0 * PI);
}
 
double angle(PT(a), PT(o), PT(b)){ // abs smallest angle
  return abs(sig_angle(a,o,b));
}
 
bool between(PT(a), PT(b), PT(c)){
  return collinear(a,b,c) && dcmp(dot(a-b, c-b)) <= 0;
}
 
int sig(double x) {
  return (dcmp(x) > 0) - (dcmp(x) < 0);
}
 
// lines
point proj(PT(p), LINE(a, b)){
  return a+proj(p-a, b-a);
}
 
bool collinear(LINE(a,b), LINE(p,q)){
  return collinear(a,b,p) && collinear(a,b,q);
}
 
bool parallel(LINE(a,b), LINE(p,q)){
  return !dcmp(cross(b-a, q-p));
}
 
double progress(PT(p), LINE(a, b)) {
  return abs(proj(p-a, b-a));
}
 
// barycentric stuff
point bary(PT(A), PT(B), PT(C), double a, double b, double c){
  return (A*a + B*b + C*c) / (a+b+c);
}
point centroid(PT(A), PT(B), PT(C)){
  return bary(A, B, C, 1, 1, 1);
}
point circumcenter(PT(A), PT(B), PT(C)){
  double a = norm(B-C), b = norm(C-A), c = norm(A-B);
  return bary(A, B, C, a*(b+c-a), b*(c+a-b), c*(a+b-c));
}
point incenter(PT(A), PT(B), PT(C)){
  return bary(A, B, C, abs(B-C), abs(A-C), abs(A-B));
}
point orthocenter(PT(A), PT(B), PT(C)){
  double a = norm(B-C), b = norm(C-A), c = norm(A-B);
  return bary(A, B, C, (a+b-c)*(c+a-b), (b+c-a)*(a+b-c), (c+a-b)*(b+c-a));
}
point excenter(PT(A), PT(B), PT(C)){
  return bary(A, B, C, -abs(B-C), abs(A-C), abs(A-B));
}
 
typedef pair<point, double> circle;
 
bool in_circle(const circle& C, const point& p) {
    return dcmp(abs(p - C.first), C.second) <= 0;
}
 
point read() {
    double xx, yy;
    cin >> xx >> yy;
    return point(xx, yy);
}
 
const int N = 1e5+10;
point v[N];
 
int32_t main() {
    int n;
    cin >> n;
 
    for(int i = 0; i < n; i++) v[i] = read();
    circle C(point(0, 0), -1e14);
    random_shuffle(v, v+n);
 
    for(int i = 0; i < n; i++) {
        if(!in_circle(C, v[i])) {
            C = circle(v[i], 0);
            for(int j = 0; j < i; j++) {
                if(!in_circle(C, v[j])) {
                    C = circle((v[i] + v[j]) * 0.5, abs(v[i] - v[j]) * 0.5);
                    for(int k = 0; k < j; k++) {
                        if(!in_circle(C, v[k])) {
                            point center = circumcenter(v[i], v[j], v[k]);
                            C = circle(center, abs(v[k] - center));
                        }
                    }
                }
            }
        }
    }
 
    cout << fixed << setprecision(11);
    cout << C.first.x << " " << C.first.y << endl;
    cout << C.second << endl;
}
