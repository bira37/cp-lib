////////////////////////////////// 2D Geometry Structures ////////////////////////////////////

struct Point2D {
  int x,y;
  
  Point2D(){
    x = 0;
    y = 0;
  }
  
  Point2D(int x, int y) : x(x), y(y) {}
  
  Point2D operator+(const Point2D b) const{
    return Point2D(x + b.x, y + b.y);
  }
  
  Point2D operator-(const Point2D b) const{
    return Point2D(x - b.x, y - b.y);
  }
  
  void operator=(const Point2D b) {
    x = b.x;
    y = b.y;
  }
  
  double distanceTo(Point2D b){
    return sqrt((x - b.x)*(x - b.x) + (y - b.y)*(y - b.y));
  }
  
  int squareDistanceTo(Point2D b){
    return (x - b.x)*(x - b.x) + (y - b.y)*(y - b.y);
  }
  
  bool operator<(const Point2D & p) const{
    return tie(x,y) < tie(p.x, p.y);
  }
  
};

struct Vector2D {
  int x,y;
  
  Vector2D(){
    x = 0;
    y = 0;
  }
  
  Vector2D(int x, int y) : x(x), y(y) {}
  
  int operator*(const Vector2D b) const{
    return (x*b.x + y*b.y);
  }
  
  int operator^(const Vector2D b) const{
		return x*b.y - y*b.x;
	}
	
	Vector2D scale(int n){
	  return Vector2D(x*n, y*n);
	}
  
  Vector2D(Point2D a, Point2D b){
    x = b.x - a.x;
    y = b.y - a.y;
  }
  
  Vector2D operator+(const Vector2D b) const{
    return Vector2D(x + b.x, y + b.y);
  }
  
  Vector2D operator-(const Vector2D b) const{
    return Vector2D(x - b.x, y - b.y);
  }
  
  void operator=(const Vector2D b) {
    x = b.x;
    y = b.y;
  }
	
	bool operator<(const Vector2D & v) const{
    return tie(x,y) < tie(v.x, v.y);
  }
	
	double size(){
	  return sqrt(x*x + y*y);
	}
	
	int squareSize(){
	  return x*x + y*y;
	}
	
	//Only with double type
	Vector2D normalize(){
	  return Vector2D((double)x/size(), (double)y/size());
	}
	
	void rotate(double ang){
	  double xx = x, yy = y;
	  x = xx*cos(ang) + yy*-sin(ang);
	  y = xx*sin(ang) + yy*cos(ang);
	}
	
};

struct Line2D {
  Point2D p, q;
  Vector2D v;
  Vector2D normal;
  
  int a,b,c;
  
  Line2D() {
    p = Point2D();
    q = Point2D();
    v = Vector2D();
    normal = Vector2D();
    a = 0;
    b = 0;
    c = 0;
  }
  
  void operator=(const Line2D l){
    a = l.a;
    b = l.b;
    c = l.c;
    p = l.p;
    q = l.q;
    v = l.v;
    normal = l.normal;
  }
  
  Line2D(Point2D r, Point2D s){
    p = r;
    q = s;
    v = Vector2D(r, s);
    normal = Vector2D(-v.y, v.x);
    a = -v.y;
    b = v.x;
    c = -(a*p.x + b*p.y);
  }
  
  Line2D(Point2D r, Vector2D s){
    p = r;
    q = Point2D(p.x + s.x, p.y + s.y);
    v = s;
    normal = Vector2D(-v.y, v.x);
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
  
  bool operator<(const Line2D & l) const{
    return tie(a,b,c) < tie(l.a, l.b, l.c);
  }
  
};

struct Circle{
  Point2D c;
  double r;
  Circle() {}
  Circle(Point2D center, double radius) : c(center), r(radius) {}
  
  bool operator=(Circle circ){
    c = circ.c;
    r = circ.r;
  }
  
  pair<Point2D, Point2D> getTangentPoints(Point2D p){
    double d = p.distanceTo(c);
    double ang = asin(1.*r/d);
    Vector2D v1(p, c);
    v1.rotate(ang);
    Vector2D v2(p, c);
    v2.rotate(-ang);
    v1 = v1.scale(sqrt(d*d - r*r)/d);
    v2 = v2.scale(sqrt(d*d - r*r)/d);
    Point2D p1(v1.x + p.x, v1.y + p.y);
    Point2D p2(v2.x + p.x, v2.y + p.y);
    return make_pair(p1,p2);
  }
  
  double sectorArea(double ang){
    return (ang*r*r)/2.;
  }
  
  double arcLength(double ang){
    return ang*r;
  }
  
  double sectorArea(Point2D p1, Point2D p2){
    double h = p1.distanceTo(p2);
    double ang = acos(1. - h*h/r*r);
    return sectorArea(ang);
  }
  
  double arcLength(Point2D p1, Point2D p2){
    double h = p1.distanceTo(p2);
    double ang = acos(1. - (h*h)/(2*r*r));
    return arcLength(ang);
  }
};

////////////////////////////////// End of 2D Geometry Structures /////////////////////////////
