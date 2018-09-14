struct SCC {

  vector< vector<int> > adj_t;
  vector< vector<int> > scc_adj;
  vector<int> ed;
  int tempo,comp;
  vector<bool> vis;
  vector<int> scc;
  
  SCC() {}
  
  SCC(int n){
    tempo = 0;
    adj_t.resize(n+1, vector<int>());
    scc_adj.resize(n+1, vector<int>());
    ed.resize(n+1);
    comp = 0;
    vis.resize(n+1);
    scc.resize(n+1);
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

  void calculate(int n){
    for(int i=0; i<=n; i++){
      vis[i] = false;
    }
    for(int i=1; i<=n; i++){
      if(!vis[i]){
        dfs(i);
      }
    }
    
    vector< ii > vertex(n);
    
    for(int i=0; i<n; i++){
      vis[i] = false;
      vertex[i] = ii(i+1, ed[i+1]);
    }
    
    sort(vertex.begin(), vertex.end(), [](const ii & a, const ii & b) { return a.ss > b.ss; });
    
    for(int i=0; i<vertex.size(); i++){
      if(!vis[vertex[i].ff]){
        comp++;
        dfst(vertex[i].ff,comp);
      }
    }
    for(int i=1; i<=n; i++){
      for(int j=0; j<adj[i].size(); j++){
        int v = adj[i][j];
        scc_adj[scc[i]].push_back(scc[v]);
      }
    }
  }
  
};
