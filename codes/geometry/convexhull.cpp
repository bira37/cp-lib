//Convex Hull - Monotone Chain
//Generates Upper and Lower Hull 

vector < pair<int, int> > upper, lower;
vector< pair<int, int> > hull;


int direction(pair<int, int> & a, pair<int, int> & b, pair<int, int> & c){
    pair<int, int> vec1(b.ff - a.ff, b.ss - a.ss);
    pair<int, int> vec2(c.ff - b.ff, c.ss - b.ss);
    return vec1.ff*vec2.ss - vec1.ss*vec2.ff;
}

void calculate_upper(vector< pair<int, int> > & p){
   	for(int i=0; i<p.size(); i++){
        	while(upper.size() >= 2 && direction(upper[upper.size()-2], upper.back(), p[i]) >= 0){
       		     upper.pop_back();
      		}
        	upper.push_back(p[i]);
    	}
}

void calculate_lower(vector< pair<int, int> > & p){
	for(int i=0; i<p.size(); i++){
        	while(lower.size() >= 2 && direction(lower[lower.size()-2], lower.back(), p[i]) <= 0){
       		     lower.pop_back();
      		}
        	lower.push_back(p[i]);
    	}
}

void merge_hull(){
	for(int i=0; i<upper.size(); i++) hull.push_back(upper[i]);
	for(int i=lower.size()-2; i>0; i--) hull.push_back(lower[i]);
}
