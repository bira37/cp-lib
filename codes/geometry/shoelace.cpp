/* Shoelace formula */
/* Calculate area of convex polygon */
/* Points given in clockwise/counterclockwise order */

int cross(pair<int, int> & a, pair<int, int> & b){
	return a.ff*b.ss - a.ss*b.ff;
}

int shoelace(vector< pair<int, int> > & p){
	int area = 0;
	for(int i=0; i<hull.size(); i++){
		area += cross(hull[i], hull[(i+1)%hull.size()]);
	}
	return abs(area/2);
}
