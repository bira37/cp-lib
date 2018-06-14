//Graph - Euler path

//for undirected graph
//circuit - 2 vertex with odd grades 
//simple path - all vertex with even grades
//this algorithm generates a circuit, if you need a path between u,v
//create a new edge u-v, compute circuit u..u, then delete the last u

//for directed graph
//circuit - all vertex needs enter grade = exit grade
//path - one vertex needs to have one more enter grade
//and the other needs to have one more exit grade
//this algorithm generates a circuit, if you need a path between u,v
//create a new edge u-v, considering that u have one more enter grade
//and v one more exit grade

struct EulerianCircuit {
  vector< set<int> > adj;
  vector<int> walk;
  vector<int> deg;
  int s, t;
  
  EulerianCiruit();
  EulerianCircuit(int n){
    deg.resize(n+1);
    adj.resize(n+1);
  }
  
  void undirected_euler(int u){
	  while(!adj[u].empty()){
		  int v = *(--adj[u].end());

		  adj[u].erase(v);
		  adj[v].erase(adj[v].find(u));
		
		  euler(v);
	  }

	  walk.push_back(u);
  }

  void directed_euler(int u){
	  while(!adj[u].empty()){
		  int v = *(--adj[u].end());

		  adj[u].erase(v);
		
		  euler(v);
	  }

	  walk.push_back(u);
  }
  
};


	
	

