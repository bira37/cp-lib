struct query{
	int id, l, r, ans;
};

bool cmp_mos(const query & a, const query & b){
	return a.l/(int)sqrt(n) < b.l/(int)sqrt(n) || a.l/(int)sqrt(n) == b.l/(int)sqrt(n) && a.r < b.r;
}

bool cmp_ans(const query & a, const query & b){
	return a.id < b.id;
}

void sqrtdecomp(vector<query> & q){
	sort(q.begin(), q.end(), cmp_mos);
	int l =0, r = -1;
	for(int i=0; i<n; i++){
		while(q[i].l < l) add(--l);
		while(r < q[i].r) add(++r);
		while(q[i].l > l) remove(l++);
		while(r > q[i].r) remove(r--);
		q[i].ans = answer_query();
	}
} 
