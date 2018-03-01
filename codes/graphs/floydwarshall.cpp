int dist[N][N][N];

void relax(int i, int j, int k){
	dist[k][i][j] = min(dist[k-1][i][j], dist[k-1][i][k] + dist[k-1][k][j]);
}

void floyd_warshall(){
	for(int k=0; k<=n; k++){
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				if(i==j) dist[k][i][j] = 0;
				else dist[k][i][j] = INF;
			}
		}
	}
	for(int k=1; k<=n; k++){
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				relax(i,j,k);
			}
		}
	}
}
