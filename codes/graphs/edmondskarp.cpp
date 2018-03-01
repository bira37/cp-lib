vector<int> adj[N];
bool vis[NN];
int pi[NN];
int capacity[N][N];
int source,sink,flow;

void ford_fulkerson(){
	bool improving = true;
	while(improving){
		
		for(int i=0; i<MAX_N; i++){
			vis[i] = false;
			pi[i] = -1;
		}
		
		queue< pii > q;
		q.push(pii(source,INT_MAX));
		int bottleneck = 0;
		while(!q.empty()){
			pii u = q.front();
			q.pop();
			if(vis[u.ff]) continue;
			vis[u.ff] = true;
			if(u.ff == sink){
				bottleneck = u.ss;
				break;
			}
			
			for(int i=0; i<adj[u.ff].size(); i++){
				int v = adj[u.ff][i];
				if(vis[v]) continue;
				if(!capacity[u.ff][v]) continue;
				pi[v] = u.ff;
				q.push(pii(v, min(u.ss, capacity[u.ff][v])));
			}
		}
				
		if(pi[sink] == -1){
			improving = false;
			continue;
		}
	
		int curr = sink;
		while(pi[curr] != -1){
			capacity[pi[curr]][curr]-=bottleneck;
			capacity[curr][pi[curr]]+=bottleneck;
			curr = pi[curr];
		}
		flow+=bottleneck;
	}
}
