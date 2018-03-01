pair<int, int> v[N];
int tmp_x[N];
int tmp_y[N];
int coord_x[N], coord_y[N];

for(int i=0; i<n; i++){
	tmp_x[i] = v[i].first;
	tmp_y[i] = v[i].second;
}

sort(tmp_x, tmp_x+n);
sort(tmp_y, tmp_y+n);

for(int i=0; i<n; i++){
	int idx_x = lower_bound(tmp_x, tmp_x+n, v[i].first);
	int idx_y = lower_bound(tmp_y, tmp_y+n, v[i].second);
	
	comp_x[idx_x] = v[i].first;
	comp_y[idx_y] = v[i].second;
	v[i].first = idx_x;
	v[i].second = idx_y;
}
