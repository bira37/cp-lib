
//Uses Segment tree

int L[N], vis[N], vis2[N], P[N], ch[N], subsz[N], st[N], ed[N], heavy[N];
int t = 0;
vector<int> adj[N];
int n,q;

void init(int n){
	t = 0;
	for(int i=0; i<=n; i++){
		vis[i] = false;
		vis2[i] = false;
		adj[i].clear();
		ch[i] = i;
		L[i] = 0;
		P[i] = -1;
		subsz[i] = 1;
		heavy[i] = -1;
	}
}

void pre_dfs(int u){
	vis[u] = true;
	for(int i=0; i<adj[u].size(); i++){
		int v = adj[u][i];
		if(vis[v]) continue;
		P[v] = u;
		L[v]=L[u]+1;
		pre_dfs(v);
		if(heavy[u] == -1 || subsz[heavy[u]] < subsz[v]) heavy[u] = v;
		subsz[u]+=subsz[v];
	}
}

void st_dfs(int u){
	vis2[u] = true;
	st[u]=t;
	v[t++] = //segtree value
	if(heavy[u] != -1){
		ch[heavy[u]] = ch[u];
		st_dfs(heavy[u]);
	}
	for(int i=0; i<adj[u].size(); i++){
		int v = adj[u][i];
		if(vis2[v] || v == heavy[u]) continue;
		st_dfs(v);
	}
	ed[u] = t;
	v[t++] = 0; //trick
}

void update(){
	
}		

void query(){

}

