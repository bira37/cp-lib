/* Closest Pair of Points Problem Implementation */
/* Divide and Conquer Approach */
/* Using the observation of only checking points inside min_dist x min_dist from mid */
/* Binary search boosts search for the right border start point */

struct vec2 {
	long long x, y;
};

bool cmp(vec2 a, vec2 b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

pair<vec2, vec2> ans;

long long solve(vector<vec2> &a) {

	long long mid = a[a.size()/2].x;
	int n = a.size();
	
	vector<vec2> l;
	vector<vec2> r;
	int i = 0;
	for(; i < a.size()/2; i++) l.push_back(a[i]);
	for(; i < a.size(); i++) r.push_back(a[i]);

	long long d = LLONG_MAX;
	
	if(l.size() > 1) {
 		d = min(d, solve(l));
	} if(r.size() > 1) {
		d = min(d, solve(r));
	}
	
	a.clear();
	
	vector<vec2> ll;
	vector<vec2> rr;
	
	
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
			long long cur =  (ll[i].x - rr[j].x)*(ll[i].x - rr[j].x)
							+(ll[i].y - rr[j].y)*(ll[i].y - rr[j].y);
			if(cur < d) {
				d = cur;
				long long cur2 =  (ans.first.x - ans.second.x)*(ans.first.x - ans.second.x)
							+(ans.first.y - ans.second.y)*(ans.first.y - ans.second.y);
				if(cur < cur2)
					ans = { ll[i], rr[j] };
			}
		}
	}
	return d;
}
