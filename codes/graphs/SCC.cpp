vector<int> adj[N];
vector<int> adj_t[N];
vector<int> scc_adj[N];
int ed[N];
int tempo,comp;
bool vis[N];
int scc[N];

int init(int n){
	tempo = 0;
	for(int i=0; i<n; i++){
		adj[i].clear();
		adj_t[i].clear();
		scc_adj[i].clear();
		ed[i] = -1;
	        vis[i] = false;
	        uf[i]  = i;
	        sz[i] = 1;
	}
}

void dfs(int u){
	vis[u] = true;
	for(int i=0; i<adj[u].size(); i++){
		int v = adj[u][i];
		if(!vis[v]) dfs(v);
	}
	ed[u] = ++tempo;
}

void dfst(int u, int comp){
	scc[u] = comp;
	vis[u] = true;
	for(int i=0; i<adj_t[u].size(); i++){
		int v = adj_t[u][i];
		if(!vis[v]) dfst(v,comp);
	}
}

bool cmp_end(const int & a, const int & b){
	return ed[a] > ed[b];
}

void calculate_scc(int n){
	for(int i=0; i<n; i++){
		vis[i] = false;
	}
	for(int i=0; i<n; i++){
		if(!vis[i]){
			dfs(i);
		}
	}
	vector<int> vertex(n+1);
	for(int i=0; i<n; i++){
		vis[i] = false;
		vertex[i] = i;
	}
	sort(vertex.begin(), vertex.end(), cmp_end);
	comp=-1;
	for(int i=0; i<vertex.size(); i++){
		if(!vis[vertex[i]]){
			comp++;
			dfst(vertex[i],comp);
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<adj[i].size(); j++){
			int v = adj[i][j];
			scc_adj[scc[i]].push_back(scc[v]);
		}
	}
}
