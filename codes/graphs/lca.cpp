int tempo = 0;
int st[N];
int ed[N];
int vis[N];
int dad[N];
vector<int> adj[N];
int anc[20][N];

void dfs_makedad(int u){
	vis[u] = true;
	st[u] = tempo++;
	for(int i=0; i<adj[u].size(); i++){
		int v = adj[u][i];
		if(!vis[v]){
			dad[v] = u;
			dfs_makedad(v);
		}
	} 
	ed[u] = tempo++;
}

bool is_ancestor(int u, int v){
	return st[u] <= st[v] && st[v] <= ed[u];
}

int lca(int u, int v){
	if(is_ancestor(u,v)) return u;
	for(int i=19; i>=0; i--){
		if(anc[i][u] == -1) continue;
		if(!is_ancestor(anc[i][u],v)) u = anc[i][u];
	}
	return dad[u];
}

void pre_process(int n){
	dad[1] = -1;
	dfs_makedad(1);
	for(int i=1; i<=n; i++){
		anc[0][i] = dad[i];
	}
	for(int i=1; i<20; i++){
		for(int j=1; j<=n; j++){
				if(anc[i-1][j] != -1){
					anc[i][j] = anc[i-1][anc[i-1][j]];
				}
				else {
					anc[i][j] = -1;
				}
		}
	}
}
