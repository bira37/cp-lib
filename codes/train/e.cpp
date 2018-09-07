#include <bits/stdc++.h>

#define int long long
#define double long double
#define ff first
#define ss second
#define endl '\n'
#define ii pair<int, int>
#define DESYNC ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define pb push_back
#define vi vector<int>
#define vii vector< ii >
#define EPS 1e-9
#define INF 1e18
#define ROOT 1
#define M 1000000007
const double PI = acos(-1);

using namespace std;

inline int mod(int n, int m){ int ret = n%m; if(ret < 0) ret += m; return ret; }

int gcd(int a, int b){
  if(a == 0 || b == 0) return 0;
  else return abs(__gcd(a,b));
}

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
  
}

////////////////////////////////// End of  Geometry Structures /////////////////////////////

////////////////////////////////// Geometry  Algorithms ////////////////////////////////////

namespace Geo2D {
  
  Point intersectionSegmentSegment(Line s1, Line s2){
    //Assuming that endpoints are ordered by x
    if(s1.p.x > s1.q.x) swap(s1.p, s1.q);
    if(s2.p.x > s2.q.x) swap(s2.p, s2.q);
    if(abs(s1.v^s2.v) == 0){
		  Point v1(s2.p, s1.p);
		  if(s1.p.x == s1.q.x && s2.p.x == s2.q.x && s1.p.x == s2.p.x){
			  Point ansl, ansr;
			  if(s1.p.y > s1.q.y) swap(s1.p, s1.q);
			  if(s2.p.y > s2.q.y) swap(s2.p, s2.q);
			  if(s1.p.y <= s2.p.y) ansl = s2.p;
			  else ansl = s1.p;
			  if(s2.q.y <= s1.q.y) ansr = s2.q;
			  else ansr = s1.q;
			  if(ansl.x == ansr.x && ansl.y == ansr.y){
			    //cout << ansr.x << " " << ansr.y << endl;
			    return Point(ansr.x, ansr.y);
			  }
			  else if(ansr.y < ansl.y){
			    //cout << "Empty" << endl;
			    return Point((int)1e9, (int)1e9);
			  }
			  else {
				  if(ansl.x == ansr.x && ansl.y > ansr.y) swap(ansl, ansr);
				  //cout << ansl.x << " " << ansl.y << endl << ansr.x << " " << ansr.y << endl;
				  return Point((int)1e9, (int)1e9);
			  }
		  }
		  else if(abs(s1.v^v1) == 0){
			  Point ansl, ansr;
			  if(s1.p.x <= s2.p.x) ansl = s2.p;
			  else ansl = s1.p;
			  if(s2.q.x <= s1.q.x) ansr = s2.q;
			  else ansr = s1.q;
			  if(ansl.x == ansr.x && ansl.y == ansr.y){
			    //cout << ansr.x << " " << ansr.y << endl;
			    return Point(ansr.x, ansr.y);
			  }
			  else if(ansr.x < ansl.x){
			    //cout << "Empty" << endl;
			    return Point((int)1e9, (int)1e9);
			  }
			  else {
				  if(ansl.x == ansr.x && ansl.y > ansr.y) swap(ansl, ansr);
				  //cout << ansl.x << " " << ansl.y << endl << ansr.x << " " << ansr.y << endl;
				  return Point((int)1e9, (int)1e9);
			  }
		  }
		  else {
		    //cout << "Empty" << endl;
		    return Point((int)1e9, (int)1e9);
		  }
		
	  }
	  else {
		  int a1 = s1.q.y - s1.p.y;
	    int b1 = s1.p.x - s1.q.x;
	    int c1 = a1*s1.p.x + b1*s1.p.y;
	    int a2 = s2.q.y - s2.p.y;
	    int b2 = s2.p.x - s2.q.x;
	    int c2 = a2*s2.p.x + b2*s2.p.y;
	    int det = a1*b2 - a2*b1;
	    if(abs(b2*c1 - b1*c2)%det != 0 || abs(a1*c2 - a2*c1)%det != 0) return Point((int)1e9, (int)1e9);
	    int x = (b2*c1 - b1*c2)/det;
	    int y = (a1*c2 - a2*c1)/det;
	    if(s1.p.x <= x && x <= s1.q.x && s2.p.x <= x && x <= s2.q.x && ((s1.p.y <= y && y <= s1.q.y && s2.p.y <= y && y <= s2.q.y) || (s1.q.y <= y && y <= s1.p.y && s2.q.y <= y && y <= s2.p.y) || (s1.p.y <= y && y <= s1.q.y && s2.q.y <= y && y <= s2.p.y) || (s1.q.y <= y && y <= s1.p.y && s2.p.y <= y && y <= s2.q.y))){
	      return Point(x,y);
	    }
	    else {
	      return Point((int)1e9, (int)1e9);
	    }
	  }
  }
  
}

////////////////////////////////// End of Geometry  Algorithms /////////////////////////////

int boundary(Geo2D::Point p, Geo2D::Point q){
  if(p.x == q.x) return abs(q.y - p.y) - 1;
  if(p.y == q.y) return abs(q.x - p.x) - 1;
  else return gcd(abs(q.x - p.x), abs(q.y - p.y)) - 1;
}

int32_t main(){
  DESYNC;
  int n;
  cin >> n;
  Geo2D::Line v[n];
  int ans = 0;
  set<Geo2D::Point> k;
  for(int i=0; i<n; i++){
    Geo2D::Point a,b;
    cin >> a.x >> a.y >> b.x >> b.y;
    ans += boundary(a,b);
    k.insert(a);
    k.insert(b);
    v[i] = Geo2D::Line(a,b);
  }
  map< Geo2D::Point, set<Geo2D::Line> > m;
  for(int i=0; i<n; i++){
    for(int j = i+1; j<n; j++){
      Geo2D::Point p = Geo2D::intersectionSegmentSegment(v[i], v[j]);
      if(p.x != (int)1e9 && p.y != (int)1e9 && !k.count(p)){
        m[p].insert(v[i]);
        m[p].insert(v[j]);
      }
    }
  }
  for(auto it : m){
    ans -= it.second.size() -1;
  }
  cout << (int)k.size() + ans << endl;
}


