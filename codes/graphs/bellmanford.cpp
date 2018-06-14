struct BellmanFord{

  struct edges {
	  int u, v, weight;
	  edges(int u , int v, int weight) :
	  u(u),
	  v(v),
	  weight(weight) {}
  };

  vector<int> dist;

  vector<edges> e;
  
  bool cycle = false;
  
  BellmanFord(){}
  
  BellmanFord(int n, int m){
    dist.resize(n+1);
    e.resize(m+1);
  }

  void calculate(int source){
	  for(int i=0; i<=dist.size(); i++){
		  dist[i] = INT_MAX;
	  }
	  dist[source] = 0;
	  for(int k=0; k<dist.size()-1; k++){
		  for(int i=0; i<e.size(); i++){
			  if(dist[e[i].v] > dist[e[i].u] + e[i].weight){
				  dist[e[i].v] = dist[e[i].u] + e[i].weight;
			  }
		  }
	  }
	  for(int i=0; i<e.size(); i++){
		  if(dist[e[i].v] > dist[e[i].u] + e[i].weight){
		    cycle = true;
		  }
	  }
  }
};
