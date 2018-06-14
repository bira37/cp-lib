#include <bits/stdc++.h>
#define pii pair<int, int>
#define ff first
#define ss second
#define int long long

using namespace std;

vector<int> adj[610];
bool vis[610];
int pi[610];
int capacity[610][610];
int source,sink,flow;

void ford_fulkerson(){
	bool improving = true;
	while(improving){
		
		for(int i=0; i<610; i++){
			vis[i] = false;
			pi[i] = -1;
		}
		
		queue< pii > q;
		q.push(pii(source,INT_MAX));
		int bottleneck = 0;
		while(!q.empty()){
			pii u = q.front();
			//cout << "used " << pi[u.ff] << "->" << u.ff << "capacity " << capacity[pi[u.ff]][u.ff] << endl;
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
				//cout << u.ff << " " << v << " " << capacity[u.ff][v] << endl;
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

int dist(pii a, pii b){
	return abs(a.ff - b.ff) + abs(a.ss - b.ss);
}

int32_t main(){
	ios_base::sync_with_stdio(false);
	int m,n,s,c,t;
	cin >> t;
	while(t--){
		flow = 0;
		source = 0;
		cin >> m >> n >> s >> c;
		sink = m+n+1;
		for(int i=0; i<610; i++){
			adj[i].clear();
			for(int j=0; j<610; j++) capacity[i][j] = 0;
		}
		pii pass[m+1];
		pii taxi[n+1];
		
		for(int i=1; i<=m; i++) cin >> pass[i].ff >> pass[i].ss;
		for(int i=1; i<=n; i++) cin >> taxi[i].ff >> taxi[i].ss;

		for(int i=1; i<=n; i++){
			adj[source].push_back(i);
			capacity[source][i]++;
		}
		for(int i=1; i<=m; i++){
			adj[i+n].push_back(sink);
			capacity[i+n][sink]++;
		}

		for(int i=1; i<=n; i++){
			for(int j=1; j<=m; j++){
				if(dist(taxi[i], pass[j])*200 > c*s) continue;
				adj[i].push_back(j+n);
				adj[j+n].push_back(i);
				capacity[i][j+n]++;
			}
		}
		ford_fulkerson();
		cout << flow << endl;
	}
}
