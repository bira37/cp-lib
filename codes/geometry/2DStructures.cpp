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
  
  bool operator<(const Point2D b) const{
    return x < b.x || (x == b.x && y < b.y);
  }
  
  void operator=(const Point2D b) const{
    x = b.x;
    y = b.y;
  }
  
  double distanceTo(Point2D b){
    return sqrt((x - b.x)*(x - b.x) + (y - b.y)*(y - b.y));
  }
  
  int distanceTo2(Point2D b){
    return (x - b.x)*(x - b.x) + (y - b.y)*(y - b.y);
  }
  
};

struct Vector2D {
  int x,y;
  
  Vector2D(){
    x = 0;
    y = 0;
  }
  
  Vector2D(int x, int y) : x(x), y(y) {}
  
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
  
  void operator=(const Vector2D b) const{
    x = b.x;
    y = b.y;
  }
  
  int operator*(const Vector2D b) const{
    return (x*b.x + y*b.y);
  }
  
  int operator^(const Vector2D b) const{
		return x*b.y - y*b.x;
	}
	
	bool operator<(const Vector2D b) const{
		return x < b.x || (x == b.x && y < b.y);
	}
	
	Vector2D scale(int n){
	  return Vector2D(x*n, y*n);
	}
	
	double size(){
	  return sqrt(x*x + y*y);
	}
	
	int size2(){
	  return x*x + y*y;
	}
	
	Vector2D normalize(){
	  return Vector2D((double)x/size(), (double)y/size());
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
  
  void operator=(const Line2D l) const{
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
  
};
