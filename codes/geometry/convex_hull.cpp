struct ConvexHull {
  vector< Point2D > points, lower, upper;
  
  ConvexHull(){}
  
  void calculate(vector<Point2D> v){
    sort(v.begin(), v.end());
    for(int i=0; i<v.size(); i++){
			while(upper.size() >= 2 && (Vector2D(upper[upper.size()-2], upper.back())^Vector2D(upper.back(), v[i])) >= 0LL) upper.pop_back();
			upper.push_back(v[i]);
		}
		reverse(v.begin(), v.end());
		for(int i=0; i<v.size(); i++){
			while(lower.size() >= 2 && (Vector2D(lower[lower.size()-2], lower.back())^Vector2D(lower.back(), v[i])) >= 0LL) lower.pop_back();
			lower.push_back(v[i]);
		}
		for(int i=upper.size()-2; i>=0; i--) points.push_back(upper[i]);
		for(int i=lower.size()-2; i>=0; i--) points.push_back(lower[i]);
	}
	
	double area(){
		double area = points.back().x*points[0].y - points.back().y*points[0].x;
		for(int i=0; i<points.size()-1; i++){
			area += points[i].x*points[i+1].y - points[i].y*points[i+1].x;
		}
		return area/2.;
	}
	
	int area2(){
		int area2 = points.back().x*points[0].y - points.back().y*points[0].x;
		for(int i=0; i<points.size()-1; i++){
			area2 += points[i].x*points[i+1].y - points[i].y*points[i+1].x;
		}
		return area2;
	}
	
	long double perimeter(){
		long double val = Vector2D(points[0], points.back()).size();
		for(int i=0; i<points.size()-1; i++){
			val += Vector2D(points[i], points[i+1]).size();
		}
		return val;
	}

} chull;
