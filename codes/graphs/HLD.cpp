struct HLD {

  vector<int> L, vis, vis2, P, ch, subsz, st, ed, heavy;
  int t = 0;
  
  HLD () {}
  
  HLD(int n){
    L.resize(n+1);
    vis.resize(n+1);
    vis2.resize(n+1);
    P.resize(n+1);
    ch.resize(n+1);
    subsz.resize(n+1);
    st.resize(n+1);
    ed.resize(n+1);
    heavy.resize(n+1);
    t = 0;
	  for(int i=0; i<=n; i++){
		  ch[i] = i;
		  P[i] = -1;
		  heavy[i] = -1;
	  }
  }

  void precalculate(int u){
	  vis[u] = true;
	  subsz[u] = 1;
	  for(int i=0; i<adj[u].size(); i++){
		  int v = adj[u][i];
		  if(vis[v]) continue;
		  P[v] = u;
		  L[v]=L[u]+1;
		  precalculate(v);
		  if(heavy[u] == -1 || subsz[heavy[u]] < subsz[v]) heavy[u] = v;
		  subsz[u]+=subsz[v];
	  }
  }

  void build(int u){
	  vis2[u] = true;
	  st[u]=t;
	  v[t++] = //segtree value
	  if(heavy[u] != -1){
		  ch[heavy[u]] = ch[u];
		  build(heavy[u]);
	  }
	  for(int i=0; i<adj[u].size(); i++){
		  int v = adj[u][i];
		  if(vis2[v] || v == heavy[u]) continue;
		  build(v);
	  }
	  ed[u] = t;
	  v[t++] = 0; //trick
  }

  void update(){
	  //update path / subtree / edge  
  }		

  int query(){
    long long ans;
    if(a == b) return 0;
    while(ch[a] != ch[b]){
      if(L[ch[b]] > L[ch[a]]) swap(a,b);
      //query from st[ch[a]] to st[a]
      a = P[ch[a]];
    }
    if(L[b] < L[a]) swap(b,a);
    if(st[a]+1 <= st[b]) //query from st[a]+1 to st[b]
    return ans;
  }
  
};
