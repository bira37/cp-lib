//////////////////////////////////  Geometry Structures ////////////////////////////////////

namespace Geo2D {
 
  struct Point {
    int x,y;
    
    Point(){
      x = 0;
      y = 0;
    }
    
    Point(int x, int y) : x(x), y(y) {}
    
    Point(Point a, Point b){
      x = b.x - a.x;
      y = b.y - a.y;
    }
    
    Point operator+(const Point b) const{
      return Point(x + b.x, y + b.y);
    }
    
    Point operator-(const Point b) const{
      return Point(x - b.x, y - b.y);
    }
    
    int operator*(const Point b) const{
      return (x*b.x + y*b.y);
    }
    
    int operator^(const Point b) const{
      return x*b.y - y*b.x;
    }
  
    Point scale(int n){
      return Point(x*n, y*n);
    }
    
    void operator=(const Point b) {
      x = b.x;
      y = b.y;
    }
    
    bool operator==(const Point b){
      return x == b.x && y == b.y;
    }
    
    double distanceTo(Point b){
      return sqrt((x - b.x)*(x - b.x) + (y - b.y)*(y - b.y));
    }
    
    int squareDistanceTo(Point b){
      return (x - b.x)*(x - b.x) + (y - b.y)*(y - b.y);
    }
    
    bool operator<(const Point & p) const{
      return tie(x,y) < tie(p.x, p.y);
    }
    
    double size(){
      return sqrt(x*x + y*y);
    }
  
    int squareSize(){
      return x*x + y*y;
    }
  
    //Only with double type
    Point normalize(){
      return Point((double)x/size(), (double)y/size());
    }
  
    void rotate(double ang){
      double xx = x, yy = y;
      x = xx*cos(ang) + yy*-sin(ang);
      y = xx*sin(ang) + yy*cos(ang);
    }
    
  };

  struct Line {
    Point p, q;
    Point v;
    Point normal;
    
    int a,b,c;
    
    Line() {
      p = Point();
      q = Point();
      v = Point();
      normal = Point();
      a = 0;
      b = 0;
      c = 0;
    }
    
    Line(int aa, int bb, int cc){
      a = aa;
      b = bb;
      c = cc;
      normal = Point(a,b);
      v = Point(-normal.y, normal.x);
      p = Point();
      q = Point();
    }
    
    void operator=(const Line l){
      a = l.a;
      b = l.b;
      c = l.c;
      p = l.p;
      q = l.q;
      v = l.v;
      normal = l.normal;
    }
    
    Line(Point r, Point s){
      p = r;
      q = s;
      v = Point(r, s);
      normal = Point(-v.y, v.x);
      a = -v.y;
      b = v.x;
      c = -(a*p.x + b*p.y);
    }
    
    void flip_sign(){
      a = -a, b = -b, c = -c;
    }
    
    void normalize(){
      if(a < 0) flip_sign();
      else if(a == 0 && b < 0) flip_sign();
      else if(a == 0 && b == 0 && c < 0) flip_sign();
      int g = max(a, max(b,c));
      if(a != 0) g = gcd(g, a); if(b != 0) g = gcd(g,b); if(c != 0) g = gcd(g,c);
      if(g > 0) a/=g, b/=g, c/=g;
    }
    
    bool operator<(const Line & l) const{
      return tie(a,b,c) < tie(l.a, l.b, l.c);
    }
    
  };

  struct Circle{
    Point c;
    double r;
    Circle() {}
    Circle(Point center, double radius) : c(center), r(radius) {}
    
    bool operator=(Circle circ){
      c = circ.c;
      r = circ.r;
    }
    
    pair<Point, Point> getTangentPoints(Point p){
      //p needs to be outside the circle
      double d = p.distanceTo(c);
      double ang = asin(1.*r/d);
      Point v1(p, c);
      v1.rotate(ang);
      Point v2(p, c);
      v2.rotate(-ang);
      v1 = v1.scale(sqrt(d*d - r*r)/d);
      v2 = v2.scale(sqrt(d*d - r*r)/d);
      Point p1(v1.x + p.x, v1.y + p.y);
      Point p2(v2.x + p.x, v2.y + p.y);
      return make_pair(p1,p2);
    }
    
    double sectorArea(double ang){
      return (ang*r*r)/2.;
    }
    
    double arcLength(double ang){
      return ang*r;
    }
    
    double sectorArea(Point p1, Point p2){
      double h = p1.distanceTo(p2);
      double ang = acos(1. - h*h/r*r);
      return sectorArea(ang);
    }
    
    double arcLength(Point p1, Point p2){
      double h = p1.distanceTo(p2);
      double ang = acos(1. - (h*h)/(2*r*r));
      return arcLength(ang);
    }
    
    bool inside(const Point & p){
      if(Point(c,p).size() + EPS < r) return true;
      else if(r + EPS < Point(c,p).size()) return false; 
      else return true;
    }
    
  };
  
}

////////////////////////////////// End of  Geometry Structures /////////////////////////////
