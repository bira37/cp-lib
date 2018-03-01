//Graph - Tarjan Bridges Algorithm

//calculate bridges, articulations and all connected components

int cont = 0;
int st[N];
int low[N];
int bridge = 0;
bool isArticulation[N];
vector<int> adj[N];

void tarjan(int u, int p){
	st[u] = low[u] = ++cont;
	int son = 0;
	for(int i=0; i<adj[u].size(); i++){
		if(adj[u][i]==p){
			p = 0;
			continue;
		}
		if(!st[adj[u][i]]){
			tarjan(adj[u][i], u);
			low[u] = min(low[u], low[adj[u][i]]);
			if(low[adj[u][i]] >= st[u]) isArticulation[u] = true; //check articulation

			if(low[adj[u][i]] > st[u]){ //check if its a bridge
				bridge++;
			}

			son++;
		}
		else low[u] = min(low[u], st[adj[u][i]]);
	}

	if(p == -1){
		if(son > 1) isArticulation[u] = true;
		else isArticulation[u] = false;
	}
}
