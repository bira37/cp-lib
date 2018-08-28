/* Centroid Decomposition Implementation */
/* c_p[] contains the centroid predecessor on centroid tree */
/* removed[] says if the node was already selected as a centroid (limit the subtree search) */
/* L[] contains the height of the vertex (from root) on centroid tree (Max is logN) */
/* N is equal to the maximum size of tree (given by statement) */

struct CentroidDecomposition {
  vector<int> adj[N];
  bool removed[N];
  int L[N], subsz[N];
  int c_p[N];

  void init(int n){
	  for(int i=0; i<=n;i++){
		  removed[i] = false;
		  adj[i].clear();
		  L[i] = 0;
		  subsz[i] = 1;
		  c_p[i] = -1;
	  }
  }

  void centroid_subsz(int u, int p){
	  subsz[u]= 1;
	  for(int i=0; i<adj[u].size(); i++){
		  int v = adj[u][i];
		  if(v == p || removed[v]) continue;
		  centroid_subsz(v,u);
		  subsz[u] += subsz[v];
	  }
  }

  int find_centroid(int u, int p, int sub){
	  for(int i=0; i<adj[u].size(); i++){
		  int v = adj[u][i];
		  if(v == p || removed[v]) continue;
		  if(subsz[v] > subsz[sub]/2){
			  return find_centroid(v, u, sub);
		  }
	  }
	  return u;
  }	

  void centroid_decomp(int u, int p, int r){
	  centroid_subsz(u,-1);
	  int centroid = find_centroid(u, -1, u);
	  L[centroid] = r;
	  c_p[centroid] = p;
	  removed[centroid] = true;
	
	  //problem pre-processing
	
	  for(int i=0; i<adj[centroid].size(); i++){
		  int v = adj[centroid][i];
		  if(removed[v]) continue;
		  centroid_decomp(v, centroid, r+1);
	  }
  }
};

