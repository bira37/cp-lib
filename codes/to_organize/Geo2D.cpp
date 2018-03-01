template <class T> class Vector{
public:

	T x,y;
	
	Vector<T>() = default;
	Vector<T>(T x, T y) : x(x), y(y) {}
	
	Vector<T> operator+(const Vector<T> & b) const {
		return Vector<T>(x + b.x, y+b.y);
	}
	
	Vector<T> operator-(const Vector<T> & b) const {
		return Vector<T>(x - b.x, y - b.y);
	}
	
	T operator*(const Vector<T> & b) const {
		return x*b.x + y*b.y;
	}
	
	Vector<T> operator*(const int & b) const {
		return Vector<T>(x*b, y*b);
	}
	
	T operator^(const Vector<T> & b) const {
		return x*b.y - y*b.x;
	}
	
	bool operator<(const Vector<T> & b){
		return x < b.x || (x == b.x && y < b.y);
	}
	
	T size2(){
		return x*x + y*y;
	}

};

template <class T> class ConvexHull{
public:
	vector< Vector<T> > points;
	vector< Vector<T> > lower, upper;
	ConvexHull<T>() = default;
	
	void make(vector< Vector<T> > v){
		sort(v.begin(), v.end());
		for(int i=0; i<v.size(); i++){
			while(upper.size() >= 2 && (Vector<T>(upper.back() - upper[upper.size()-2])^Vector<T>(v[i] - upper.back())) >= 0LL) upper.pop_back();
			upper.push_back(v[i]);
		}
		reverse(v.begin(), v.end());
		for(int i=0; i<v.size(); i++){
			while(lower.size() >= 2 && (Vector<T>(lower.back() - lower[lower.size()-2])^Vector<T>(v[i] - lower.back())) >= 0LL) lower.pop_back();
			lower.push_back(v[i]);
		}
		for(int i=upper.size()-2; i>=0; i--) points.push_back(upper[i]);
		for(int i=lower.size()-2; i>=0; i--) points.push_back(lower[i]);
	}
	
	T shoelace2(){
		T area2 = points.back()^points[0];
		for(int i=0; i<points.size()-1; i++){
			area2 += points[i]^points[i+1];
		}
		return area2;
	}
	
	long double perimeter(){
		long double val = sqrt(Vector<T>(points.back().x - points[0].x, points.back().y - points[0].y).size2());
		for(int i=0; i<points.size()-1; i++){
			val += sqrtl(Vector<T>(points[i+1].x - points[i].x, points[i+1].y - points[i].y).size2());
		}
		return val;
	}
		
};

