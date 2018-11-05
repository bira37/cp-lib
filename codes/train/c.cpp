struct HLD {

  vector<int> L, P, ch, subsz, in, out;
  int instant;
  
  HLD () {}
  
  HLD(int n){
    L.resize(n+1);
    P.resize(n+1);
    ch.resize(n+1);
    subsz.resize(n+1);
    in.resize(n+1);
    out.resize(n+1);
    instant = 0;
    for(int i=0; i<=n; i++){
      ch[i] = i;
      P[i] = -1;
      L[i] = 0;
    }
  }

  void precalculate(int u, int p = -1){
    subsz[u] = 1;
    for(int &v : adj[u]){
      if(v == p) continue;
      P[v] = u;
      L[v] = L[u]+1;
      precalculate(v, u);
      if(subsz[adj[u][0]] < subsz[v]) swap(adj[u][0], v);
      subsz[u] += subsz[v];
    }
  }

  void build(int u, int p = -1){
    in[u] = ++instant;
    
    //segtree point value update for u here
    
    for(int v : adj[u]){
      int v = adj[u][i];
      if(v == p) continue;
      if(adj[u][0] == v){
        ch[v] = ch[u];
      }
      build(v, u);
    }
    out[u] = instant;
  }
  
  void calculate(int root = 1){
    precalculate(root)
    build(root);
  }
};
