struct edges {
	int u, v, weight;
	edges(int u , int v, int weight) :
	u(u),
	v(v),
	weight(weight) {}
};

int dist[N];

vector<edges> e;

bool bellmanford(int n, int source){
	for(int i=0; i<n; i++){
		dist[i] = INT_MAX;
	}
	dist[source] = 0;
	for(int k=0; k<n-1; k++){
		for(int i=0; i<e.size(); i++){
			if(dist[e[i].v] > dist[e[i].u] + e[i].weight){
				dist[e[i].v] = dist[e[i].u] + e[i].weight;
			}
		}
	}
	for(int i=0; i<e.size(); i++){
		if(dist[e[i].v] > dist[e[i].u] + e[i].weight){
			return false;
		}
	}
	return true;
}
