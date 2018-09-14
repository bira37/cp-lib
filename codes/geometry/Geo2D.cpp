////////////////////////////////// Geometry  Algorithms ////////////////////////////////////

namespace Geo2D {

  double distancePointLine(Point p, Line l){
    if(l.normal.squareSize() == 0) return INF;
    return (double)(1.*abs(l.a*p.x + l.b*p.y + l.c))/l.normal.size();
  }
  
  double distancePointSegment(Point p, Line l){
    int dot1 = Point(l.p, p)*Point(l.p, l.q);
    int dot2 = Point(l.q, p)*Point(l.q, l.p);
    
    if(dot1 >= 0 && dot2 >= 0) return distancePointLine(p, l);
    else return min(p.distanceTo(l.p), p.distanceTo(l.q));
  }
  
  double distancePointRay(Point p, Line l){
    int dot = Point(l.p, p)*l.v;
    if(dot >= 0) return distancePointLine(p, l);
    else return p.distanceTo(l.p);
  }
  
  Point closestPointInSegment(Point p, Line s){
    //returns closest point from p in segment s
    Point u = s.v.normalize();
    Point w(s.p, p);
    Point res = u.scale(u*w);
    if(u*w < 0 || u*w > s.p.distanceTo(s.q)){
      if(p.distanceTo(s.p) < p.distanceTo(s.q)) return s.p;
      else return s.q;
    }
    else return Point(s.p.x + res.x, s.p.y + res.y);
  }
  
  Point intersectionSegmentSegment(Line s1, Line s2){
    //Assumes that intersection exists
    //Assuming that endpoints are ordered by x
    if(s1.p.x > s1.q.x) swap(s1.p, s1.q);
    if(s2.p.x > s2.q.x) swap(s2.p, s2.q);
    
    if(abs(s1.v^s2.v) <= EPS){
    
      //parallel segments
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
        else {
          if(ansl.x == ansr.x && ansl.y > ansr.y) swap(ansl, ansr);
          //cout << ansl.x << " " << ansl.y << endl << ansr.x << " " << ansr.y << endl;
          return Point(INF, INF);
        }
      }
      else if(abs(s1.v^v1) <= EPS){
        Point ansl, ansr;
        if(s1.p.x <= s2.p.x) ansl = s2.p;
        else ansl = s1.p;
        if(s2.q.x <= s1.q.x) ansr = s2.q;
        else ansr = s1.q;
        if(ansl.x == ansr.x && ansl.y == ansr.y){
          //cout << ansr.x << " " << ansr.y << endl;
          return Point(ansr.x, ansr.y);
        }
        else {
          if(ansl.x == ansr.x && ansl.y > ansr.y) swap(ansl, ansr);
          //cout << ansl.x << " " << ansl.y << endl << ansr.x << " " << ansr.y << endl;
          return Point(INF, INF);
        }
      }
    
    }
    else {
      //general case
      int a1 = s1.q.y - s1.p.y;
      int b1 = s1.p.x - s1.q.x;
      int c1 = a1*s1.p.x + b1*s1.p.y;
      int a2 = s2.q.y - s2.p.y;
      int b2 = s2.p.x - s2.q.x;
      int c2 = a2*s2.p.x + b2*s2.p.y;
      int det = a1*b2 - a2*b1;
      
      double x = (double)(b2*c1 - b1*c2)/(double)det*1.;
      double y = (double)(a1*c2 - a2*c1)/(double)det*1.;
      //cout << x << " " << y << endl;
      return Point(x,y);
    }
  }
    
  
  double distanceSegmentSegment(Line l1, Line l2){
    if(l1.p == l2.p && l1.q == l2.q) return 0;
    if(l1.q == l2.p && l1.p == l2.q) return 0;
    if((l1.v^l2.v) != 0){
    
      Line r1(l1.p, l1.q);
      Line r2(l1.q, l1.p);
      Line r3(l2.p, l2.q);
      Line r4(l2.q, l2.p);
      
      int cross1 = (Point(r3.p, r1.p)^r3.v);
      int cross2 = (Point(r3.p, r1.q)^r3.v);
      if(cross2 < cross1) swap(cross1, cross2);
      
      bool ok1 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r1.p, r3) > distancePointLine(r1.q, r3));
      
      cross1 = (Point(r1.p, r3.p)^r1.v);
      cross2 = (Point(r1.p, r3.q)^r1.v);
      if(cross2 < cross1) swap(cross1, cross2);
      
      bool ok2 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r3.p, r1) > distancePointLine(r3.q, r1));
      
      cross1 = (Point(r3.p, r2.p)^r3.v);
      cross2 = (Point(r3.p, r2.q)^r3.v);
      if(cross2 < cross1) swap(cross1, cross2);
      
      bool ok3 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r2.p, r3) > distancePointLine(r2.q, r3));
      
      cross1 = (Point(r2.p, r3.p)^r2.v);
      cross2 = (Point(r2.p, r3.q)^r2.v);
      if(cross2 < cross1) swap(cross1, cross2);
     
      bool ok4 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r3.p, r2) > distancePointLine(r3.q, r2));
      
      cross1 = (Point(r4.p, r1.p)^r4.v);
      cross2 = (Point(r4.p, r1.q)^r4.v);
      if(cross2 < cross1) swap(cross1, cross2);
      
      bool ok5 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r1.p, r4) > distancePointLine(r1.q, r4));
      
      cross1 = (Point(r1.p, r4.p)^r1.v);
      cross2 = (Point(r1.p, r4.q)^r1.v);
      if(cross2 < cross1) swap(cross1, cross2);
      
      bool ok6 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r4.p, r1) > distancePointLine(r4.q, r1));
      
      cross1 = (Point(r4.p, r2.p)^r4.v);
      cross2 = (Point(r4.p, r2.q)^r4.v);
      if(cross2 < cross1) swap(cross1, cross2);
      
      bool ok7 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r2.p, r4) > distancePointLine(r2.q, r4));
      
      cross1 = (Point(r2.p, r4.p)^r2.v);
      cross2 = (Point(r2.p, r4.q)^r2.v);
      if(cross2 < cross1) swap(cross1, cross2);
     
      bool ok8 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r4.p, r2) > distancePointLine(r4.q, r2));
      
      if(ok1 && ok2 && ok3 && ok4 && ok5 && ok6 && ok7 && ok8) return 0;
      
    }
    
    double ans = distancePointSegment(l1.p, l2);
    ans = min(ans, distancePointSegment(l1.q, l2));
    ans = min(ans, distancePointSegment(l2.p, l1));
    ans = min(ans, distancePointSegment(l2.q, l1));
    return ans;
  }
  
  double distanceSegmentRay(Line s, Line r){
    if((s.v^r.v) != 0){
      Line r1(s.p, s.q);
      Line r2(s.q, s.p);
      
      int cross1 = (Point(r.p, r1.p)^r.v);
      int cross2 = (Point(r.p, r1.q)^r.v);
      if(cross2 < cross1) swap(cross1, cross2);
      
      bool ok1 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r1.p, r) > distancePointLine(r1.q, r));
      
      cross1 = (Point(r1.p, r.p)^r1.v);
      cross2 = (Point(r1.p, r.q)^r1.v);
      if(cross2 < cross1) swap(cross1, cross2);
      
      bool ok2 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r.p, r1) > distancePointLine(r.q, r1));
      
      cross1 = (Point(r.p, r2.p)^r.v);
      cross2 = (Point(r.p, r2.q)^r.v);
      if(cross2 < cross1) swap(cross1, cross2);
      
      bool ok3 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r2.p, r) > distancePointLine(r2.q, r));
      
      cross1 = (Point(r2.p, r.p)^r2.v);
      cross2 = (Point(r2.p, r.q)^r2.v);
      if(cross2 < cross1) swap(cross1, cross2);
     
      bool ok4 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r.p, r2) > distancePointLine(r.q, r2));
      
      if(ok1 && ok2 && ok3 && ok4) return 0;
    }
      
    
    double ans = INF;
    int dot = Point(s.p, r.p)*Point(r.p, s.q);
    if(dot >= 0) ans = min(ans, distancePointLine(r.p, s));
    else ans = min(ans, min(r.p.distanceTo(s.p), r.p.distanceTo(s.q)));
    
    dot = Point(r.p, s.p)*r.v;
    if(dot >= 0) ans = min(ans, distancePointLine(s.p, r));
    else ans = min(ans, r.p.distanceTo(s.p));
    
    dot = Point(r.p, s.q)*r.v;
    if(dot >= 0) ans = min(ans, distancePointLine(s.q, r));
    else ans = min(ans, r.p.distanceTo(s.q));
    
    return ans;
      
  }
  
  double distanceSegmentLine(Line s, Line l){
    if((s.v^l.v) == 0){
      return distancePointLine(s.p, l);
    }
    
    int cross1 = (Point(l.p, s.p)^l.v);
    int cross2 = (Point(l.p, s.q)^l.v);
    if(cross2 < cross1) swap(cross1, cross2);
    if(cross1 <= 0 && cross2 >= 0) return 0;
    else return min(distancePointLine(s.p, l), distancePointLine(s.q,l)); 
    
  }
  
  double distanceLineRay(Line l, Line r){
    if((l.v^r.v) == 0){
      return distancePointLine(r.p, l);
    }
    
    int cross1 = (Point(l.p, r.p)^l.v);
    int cross2 = (Point(l.p, r.q)^l.v);
    if(cross2 < cross1) swap(cross1, cross2);
    if((cross1 <= 0 && cross2 >= 0) || (distancePointLine(r.p, l) > distancePointLine(r.q, l))) return 0;
    return distancePointLine(r.p, l);
  }
  
  double distanceLineLine(Line l1, Line l2){
    if((l1.v^l2.v) == 0){
      return distancePointLine(l1.p, l2);
    }
    else return 0;
  }
  
  double distanceRayRay(Line r1, Line r2){
    if((r1.v^r2.v) != 0){
      
      int cross1 = (Point(r1.p, r2.p)^r1.v);
      int cross2 = (Point(r1.p, r2.q)^r1.v);
      if(cross2 < cross1) swap(cross1, cross2);
      bool ok1 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r2.p, r1) > distancePointLine(r2.q, r1));
      
      cross1 = (Point(r2.p, r1.p)^r2.v);
      cross2 = (Point(r2.p, r1.q)^r2.v);
      if(cross2 < cross1) swap(cross1, cross2);
      
      bool ok2 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r1.p, r2) > distancePointLine(r1.q, r2));
      
      if(ok1 && ok2) return 0;
      
    }
    
    double ans = INF;
    int dot = Point(r2.p, r1.p)*r2.v;
    if(dot >= 0) ans = min(ans, distancePointLine(r1.p, r2));
    else ans = min(ans, r2.p.distanceTo(r1.p));
    
    dot = Point(r1.p, r2.p)*r1.v;
    if(dot >= 0) ans = min(ans, distancePointLine(r2.p, r1));
    else ans = min(ans, r1.p.distanceTo(r2.p));
    
    return ans;
    
  }
  
  double circleCircleIntersection(Circle c1, Circle c2){
  
    if((c1.r+c2.r)*(c1.r+c2.r) <= (c2.c.x-c1.c.x)*(c2.c.x-c1.c.x) + (c2.c.y-c1.c.y)*(c2.c.y-c1.c.y)){
      return 0;
    }
    if((c1.r-c2.r)*(c1.r-c2.r) >= (c2.c.x-c1.c.x)*(c2.c.x-c1.c.x) + (c2.c.y-c1.c.y)*(c2.c.y-c1.c.y)){
      return PI*min(c1.r, c2.r)*min(c1.r, c2.r);
    }
    double x1 = c1.c.x, x2 = c2.c.x, y1 = c1.c.y, y2 = c2.c.y, r1 = c1.r, r2 = c2.r;
    double d = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
    double r1sqr = c1.r*c1.r;
    double r2sqr = c2.r*c2.r;
    double dsqr = d*d;
    
    double alpha1 = acos(((c1.r + c2.r)*(c1.r - c2.r) + dsqr)/(2.*d*r1));
    double alpha2 = acos(((c2.r + c1.r)*(c2.r - c1.r) + dsqr)/(2.*d*r2));
    double area1 = r1sqr*(alpha1 - sin(alpha1)*cos(alpha1));
    double area2 = r2sqr*(alpha2 - sin(alpha2)*cos(alpha2));
    
    return area1 + area2;
    
  }
  
  vector<Point> intersectionLineCircle(Line l, Circle circ){
    //NOT TESTED!!!!!!!!
    //no intersection
    if((l.c*l.c)/(circ.r*circ.r) > l.a*l.a + l.b*l.b) return vector<Point>();
    
    double x0 = -l.a*l.c/(l.a*l.a+l.b*l.b), y0 = -l.b*l.c/(l.a*l.a+l.b*l.b);
    //one intersection
    if(abs((l.c*l.c)/(circ.r*circ.r) - (l.a*l.a + l.b*l.b)) <= EPS){
      vector<Point> ret;
      ret.pb(Point(x0,y0));
      return ret;
    }
    
    //general case
    double d = circ.r*circ.r - (l.c*l.c)/(l.a*l.a+l.b*l.b);
    double mult = sqrt(d/(l.a*l.a+l.b*l.b));
    
    Point p1(x0 + l.b*mult, y0 - l.a*mult);
    Point p2(x0 - l.b*mult, y0 + l.a*mult);
    
    vector<Point> ret;
    ret.pb(p1); ret.pb(p2);
    return ret;
  }
    
  vector<Point> intersectionCircleCircle(Circle c1, Circle c2){
    //NOT TESTED!!!!!!!!
    //translate first circle to origin
    Point translation = c1.c;
    c1.c = Point(0,0);
    c2.c = c2.c - translation;
    
    //check if centers are equal
    if(c1.c == c2.c){
      //if radius are equal = infinite intersections(return 3 points to indicate), else = no intersection(empty)
      if(c1.r == c2.r){
        vector<Point> ret;
        ret.pb(Point());
        ret.pb(Point());
        ret.pb(Point());
        return ret;
      }
      else return vector<Point>();
    }
    
    //general case
    Line l(-2*c2.c.x,-2*c2.c.y, c2.c.x*c2.c.x + c2.c.y*c2.c.y + c1.r*c1.r - c2.r*c2.r);
    
    vector<Point> ret = intersectionLineCircle(l, c1);
    
    for(Point & p : ret){
      p = p + translation;
    }
    
    return ret;
  }
  
  Point barycenter(Point & a, Point & b, Point & c, double pA, double pB,  double pC){
    Point ret = (a.scale(pA) + b.scale(pB) + c.scale(pC));
    ret.x /= (pA + pB + pC);
    ret.y /= (pA + pB + pC);
    return ret;
  }
  
  Point circumcenter(Point & a, Point & b, Point & c){
    double pA = Point(b,c).squareSize(), pB = Point(a,c).squareSize(), pC = Point(a,b).squareSize();
    return barycenter(a,b,c, pA*(pB+pC-pA), pB*(pC+pA-pB), pC*(pA+pB-pC));
  }
  
  Point centroid(Point & a, Point & b, Point & c){
    return barycenter(a,b,c,1,1,1);
  }
  
  Point incenter(Point & a, Point & b, Point & c){
    return barycenter(a,b,c, Point(b,c).size(), Point(a,c).size(), Point(a,b).size());
  }
  
  Point excenter(Point & a, Point & b, Point & c){
    return barycenter(a,b,c, -Point(b,c).size(), Point(a,c).size(), Point(a,b).size());
  }
  
  Point orthocenter(Point & a, Point & b, Point & c){
    double pA = Point(b,c).squareSize(), pB = Point(a,c).squareSize(), pC = Point(a,b).squareSize();
    return barycenter(a, b, c, (pA+pB-pC)*(pC+pA-pB), (pB+pC-pA)*(pA+pB-pC), (pC+pA-pB)*(pB+pC-pA));
  }
  
  Circle minimumCircle(vector<Point> & v){
    Circle circ(Point(0,0), 1e-14);
    random_shuffle(v.begin(), v.end());
    for(int i=0; i<v.size(); i++){
      if(!circ.inside(v[i])){
        circ = Circle(v[i], 0);
        for(int j=0; j<i; j++){
          if(!circ.inside(v[j])){
            circ = Circle((v[i] + v[j]).scale(0.5), Point(v[i], v[j]).size()*0.5);
            for(int k = 0; k<j; k++){
              if(!circ.inside(v[k])){
                Point center = circumcenter(v[i], v[j], v[k]);
                circ = Circle(center, Point(center, v[k]).size());
              }
            }
          }
        }
      }
    }
    return circ;
  }
  
  long long ClosestPairOfPoints(vector<Point> &a) {
    //returns square of distance
    long long mid = a[a.size()/2].x;
    int n = a.size();
  
    vector<Point> l;
    vector<Point> r;
    int i = 0;
    for(; i < a.size()/2; i++) l.push_back(a[i]);
    for(; i < a.size(); i++) r.push_back(a[i]);

    long long d = LLONG_MAX;
  
    if(l.size() > 1) {
       d = min(d, ClosestPairOfPoints(l));
    } if(r.size() > 1) {
      d = min(d, ClosestPairOfPoints(r));
    }
  
    a.clear();
  
    vector<Point> ll;
    vector<Point> rr;
  
  
    int j = 0;
    i = 0;
    for(int k=0; k<n; k++){
      if(i < l.size() && j < r.size()){
        if(r[j].y <= l[i].y){
          if((r[j].x - mid)*(r[j].x - mid) < d) {
            rr.push_back(r[j]);
          }
          a.push_back(r[j++]);
        }
        else {
          if((l[i].x - mid)*(l[i].x - mid) < d) {
            ll.push_back(l[i]);
          }
          a.push_back(l[i++]);
        }
      }
      else if(i < l.size()){
        if((l[i].x - mid)*(l[i].x - mid) < d) {
          ll.push_back(l[i]);
        }
        a.push_back(l[i++]);
      }
      else {
        if((r[j].x - mid)*(r[j].x - mid) < d) {
            rr.push_back(r[j]);
        }
          a.push_back(r[j++]);
      }
    }
  
    for(int i = 0; i < ll.size(); i++) {
  
      int ini = 0, end = rr.size()-1;
      int j;
    
      while(ini < end) {
        j = (ini + end) / 2;
        if((rr[j].y - ll[i].y)*(rr[j].y - ll[i].y) > d && rr[j].y < ll[i].y)
          ini = j+1;
        else end = j;
      }
    
      j = ini;
  
      for(; j < rr.size(); j++) {
        if((rr[j].y - ll[i].y)*(rr[j].y - ll[i].y) > d) break;
        long long cur =  (ll[i].x - rr[j].x)*(ll[i].x - rr[j].x) + (ll[i].y - rr[j].y)*(ll[i].y - rr[j].y);
        if(cur < d) {
          d = cur;
        }
      }
    }
    return d;
  }
  
}

////////////////////////////////// End of Geometry  Algorithms /////////////////////////////
