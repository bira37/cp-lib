struct Circle{
  Point2D c;
  int r;
  Circle() {}
  Circle(Point2D center, int radius) : c(center), r(radius) {}
  bool operator=(Circle circ){
    c = circ.c;
    r = circ.r;
  }
};

struct Geo2D {

  double distancePointLine(Point2D p, Line2D l){
    return (double)(1.*abs(l.a*p.x + l.b*p.y + l.c))/l.normal.size();
  }
  
  double distancePointSegment(Point2D p, Line2D l){
    int dot1 = Vector2D(l.p, p)*Vector2D(l.p, l.q);
    int dot2 = Vector2D(l.q, p)*Vector2D(l.q, l.p);
    
    if(dot1 >= 0 && dot2 >= 0) return distancePointLine(p, l);
    else return min(p.distanceTo(l.p), p.distanceTo(l.q));
  }
  
  double distancePointRay(Point2D p, Line2D l){
    int dot = Vector2D(l.p, p)*l.v;
    if(dot >= 0) return distancePointLine(p, l);
    else return p.distanceTo(l.p);
  }
  
  Point2D closestPointInSegment(Point2D p, Line2D s){
    //returns closest point from p in segment s
    Vector2D u = s.v.normalize();
    Vector2D w(s.p, p);
    Vector2D res = u.scale(u*w);
    if(u*w < 0 || u*w > s.p.distanceTo(s.q)){
      if(p.distanceTo(s.p) < p.distanceTo(s.q)) return s.p;
      else return s.q;
    }
    else return Point2D(s.p.x + res.x, s.p.y + res.y);
  }
  
  bool intersectionSegmentSegment(Line2D s1, Line2D s2){
    //Assuming that endpoints are ordered by x
    if(s1.p.x > s1.q.x) swap(s1.p, s1.q);
    if(s2.p.x > s2.q.x) swap(s2.p, s2.q);
    if(abs(s1.v^s2.v) <= EPS){
		  Vector2D v1(s2.p, s1.p);
		  if(s1.p.x == s1.q.x && s2.p.x == s2.q.x && s1.p.x == s2.p.x){
			  Point2D ansl, ansr;
			  if(s1.p.y > s1.q.y) swap(s1.p, s1.q);
			  if(s2.p.y > s2.q.y) swap(s2.p, s2.q);
			  if(s1.p.y <= s2.p.y) ansl = s2.p;
			  else ansl = s1.p;
			  if(s2.q.y <= s1.q.y) ansr = s2.q;
			  else ansr = s1.q;
			  if(ansl.x == ansr.x && ansl.y == ansr.y){
			    //cout << ansr.x << " " << ansr.y << endl;
			    return true;
			  }
			  else if(ansr.y < ansl.y){
			    //cout << "Empty" << endl;
			    return false;
			  }
			  else {
				  if(ansl.x == ansr.x && ansl.y > ansr.y) swap(ansl, ansr);
				  //cout << ansl.x << " " << ansl.y << endl << ansr.x << " " << ansr.y << endl;
				  return true;
			  }
		  }
		  else if(abs(s1.v^v1) <= EPS){
			  Point2D ansl, ansr;
			  if(s1.p.x <= s2.p.x) ansl = s2.p;
			  else ansl = s1.p;
			  if(s2.q.x <= s1.q.x) ansr = s2.q;
			  else ansr = s1.q;
			  if(ansl.x == ansr.x && ansl.y == ansr.y){
			    //cout << ansr.x << " " << ansr.y << endl;
			    return true;
			  }
			  else if(ansr.x < ansl.x){
			    //cout << "Empty" << endl;
			    return false;
			  }
			  else {
				  if(ansl.x == ansr.x && ansl.y > ansr.y) swap(ansl, ansr);
				  //cout << ansl.x << " " << ansl.y << endl << ansr.x << " " << ansr.y << endl;
				  return true;
			  }
		  }
		  else {
		    //cout << "Empty" << endl;
		    return false;
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
		  double x = (double)(b2*c1 - b1*c2)/(double)det*1.;
		  double y = (double)(a1*c2 - a2*c1)/(double)det*1.;
		  if(s1.p.x-EPS <= x && x <= s1.q.x+EPS && s2.p.x-EPS <= x && x <= s2.q.x+EPS){
		    //cout << x << " " << y << endl;
		    return true;
		  }
		  else {
		    //cout << "Empty" << endl;
		    return false;
		  }
	  }
  }
  
  double distanceSegmentSegment(Line2D l1, Line2D l2){
    if((l1.v^l2.v) != 0){
    
      Line2D r1(l1.p, l1.q);
      Line2D r2(l1.q, l1.p);
      Line2D r3(l2.p, l2.q);
      Line2D r4(l2.q, l2.p);
      
      int cross1 = (Vector2D(r3.p, r1.p)^r3.v);
      int cross2 = (Vector2D(r3.p, r1.q)^r3.v);
      if(cross2 < cross1) swap(cross1, cross2);
      
      bool ok1 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r1.p, r3) > distancePointLine(r1.q, r3));
      
      cross1 = (Vector2D(r1.p, r3.p)^r1.v);
      cross2 = (Vector2D(r1.p, r3.q)^r1.v);
      if(cross2 < cross1) swap(cross1, cross2);
      
      bool ok2 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r3.p, r1) > distancePointLine(r3.q, r1));
      
      cross1 = (Vector2D(r3.p, r2.p)^r3.v);
      cross2 = (Vector2D(r3.p, r2.q)^r3.v);
      if(cross2 < cross1) swap(cross1, cross2);
      
      bool ok3 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r2.p, r3) > distancePointLine(r2.q, r3));
      
      cross1 = (Vector2D(r2.p, r3.p)^r2.v);
      cross2 = (Vector2D(r2.p, r3.q)^r2.v);
      if(cross2 < cross1) swap(cross1, cross2);
     
      bool ok4 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r3.p, r2) > distancePointLine(r3.q, r2));
      
      cross1 = (Vector2D(r4.p, r1.p)^r4.v);
      cross2 = (Vector2D(r4.p, r1.q)^r4.v);
      if(cross2 < cross1) swap(cross1, cross2);
      
      bool ok5 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r1.p, r4) > distancePointLine(r1.q, r4));
      
      cross1 = (Vector2D(r1.p, r4.p)^r1.v);
      cross2 = (Vector2D(r1.p, r4.q)^r1.v);
      if(cross2 < cross1) swap(cross1, cross2);
      
      bool ok6 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r4.p, r1) > distancePointLine(r4.q, r1));
      
      cross1 = (Vector2D(r4.p, r2.p)^r4.v);
      cross2 = (Vector2D(r4.p, r2.q)^r4.v);
      if(cross2 < cross1) swap(cross1, cross2);
      
      bool ok7 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r2.p, r4) > distancePointLine(r2.q, r4));
      
      cross1 = (Vector2D(r2.p, r4.p)^r2.v);
      cross2 = (Vector2D(r2.p, r4.q)^r2.v);
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
  
  double distanceSegmentRay(Line2D s, Line2D r){
    if((s.v^r.v) != 0){
      Line2D r1(s.p, s.q);
      Line2D r2(s.q, s.p);
      
      int cross1 = (Vector2D(r.p, r1.p)^r.v);
      int cross2 = (Vector2D(r.p, r1.q)^r.v);
      if(cross2 < cross1) swap(cross1, cross2);
      
      bool ok1 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r1.p, r) > distancePointLine(r1.q, r));
      
      cross1 = (Vector2D(r1.p, r.p)^r1.v);
      cross2 = (Vector2D(r1.p, r.q)^r1.v);
      if(cross2 < cross1) swap(cross1, cross2);
      
      bool ok2 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r.p, r1) > distancePointLine(r.q, r1));
      
      cross1 = (Vector2D(r.p, r2.p)^r.v);
      cross2 = (Vector2D(r.p, r2.q)^r.v);
      if(cross2 < cross1) swap(cross1, cross2);
      
      bool ok3 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r2.p, r) > distancePointLine(r2.q, r));
      
      cross1 = (Vector2D(r2.p, r.p)^r2.v);
      cross2 = (Vector2D(r2.p, r.q)^r2.v);
      if(cross2 < cross1) swap(cross1, cross2);
     
      bool ok4 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r.p, r2) > distancePointLine(r.q, r2));
      
      if(ok1 && ok2 && ok3 && ok4) return 0;
    }
      
    
    double ans = INF;
    int dot = Vector2D(s.p, r.p)*Vector2D(r.p, s.q);
    if(dot >= 0) ans = min(ans, distancePointLine(r.p, s));
    else ans = min(ans, min(r.p.distanceTo(s.p), r.p.distanceTo(s.q)));
    
    dot = Vector2D(r.p, s.p)*r.v;
    if(dot >= 0) ans = min(ans, distancePointLine(s.p, r));
    else ans = min(ans, r.p.distanceTo(s.p));
    
    dot = Vector2D(r.p, s.q)*r.v;
    if(dot >= 0) ans = min(ans, distancePointLine(s.q, r));
    else ans = min(ans, r.p.distanceTo(s.q));
    
    return ans;
      
  }
  
  double distanceSegmentLine(Line2D s, Line2D l){
    if((s.v^l.v) == 0){
      return distancePointLine(s.p, l);
    }
    
    int cross1 = (Vector2D(l.p, s.p)^l.v);
    int cross2 = (Vector2D(l.p, s.q)^l.v);
    if(cross2 < cross1) swap(cross1, cross2);
	  if(cross1 <= 0 && cross2 >= 0) return 0;
	  else return min(distancePointLine(s.p, l), distancePointLine(s.q,l)); 
    
  }
  
  double distanceLineRay(Line2D l, Line2D r){
    if((l.v^r.v) == 0){
      return distancePointLine(r.p, l);
    }
    
    int cross1 = (Vector2D(l.p, r.p)^l.v);
    int cross2 = (Vector2D(l.p, r.q)^l.v);
    if(cross2 < cross1) swap(cross1, cross2);
	  if((cross1 <= 0 && cross2 >= 0) || (distancePointLine(r.p, l) > distancePointLine(r.q, l))) return 0;
	  return distancePointLine(r.p, l);
  }
  
  double distanceLineLine(Line2D l1, Line2D l2){
    if((l1.v^l2.v) == 0){
      return distancePointLine(l1.p, l2);
    }
    else return 0;
  }
  
  double distanceRayRay(Line2D r1, Line2D r2){
    if((r1.v^r2.v) != 0){
      
      int cross1 = (Vector2D(r1.p, r2.p)^r1.v);
      int cross2 = (Vector2D(r1.p, r2.q)^r1.v);
      if(cross2 < cross1) swap(cross1, cross2);
      bool ok1 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r2.p, r1) > distancePointLine(r2.q, r1));
      
      cross1 = (Vector2D(r2.p, r1.p)^r2.v);
      cross2 = (Vector2D(r2.p, r1.q)^r2.v);
      if(cross2 < cross1) swap(cross1, cross2);
      
      bool ok2 = (cross1 <= 0 && cross2 >= 0) || (distancePointLine(r1.p, r2) > distancePointLine(r1.q, r2));
      
      if(ok1 && ok2) return 0;
      
    }
    
    double ans = INF;
    int dot = Vector2D(r2.p, r1.p)*r2.v;
    if(dot >= 0) ans = min(ans, distancePointLine(r1.p, r2));
    else ans = min(ans, r2.p.distanceTo(r1.p));
    
    dot = Vector2D(r1.p, r2.p)*r1.v;
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
  
} geo2d;
