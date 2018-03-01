int v[MAX_N];
int comp[MAX_N];

void coordinate_compression(int n){
	int tmp[n];
	for(int i=0; i<n; i++) tmp[i] = v[i];
	sort(tmp, tmp+n);
	for(int i=0; i<n; i++){
		int idx = lower_bound(tmp, tmp+n, v[i]) - tmp;
		comp[idx] = v[i];
		v[i] = idx;
	}
}
