/* Author: Ubiratan Correia Barbosa Neto
 * Block Cut Tree Example
 */

vector<int> adj[N];
int vis[N];
int ini[N];
int bef[N];
bool art[N] int num_bridges = 0;
int T = 0;

void dfs_tarjan(int v, int p) {
  vis[v] = 1;
  bef[v] = ini[v] = ++T;
  art[v] = false;
  int num_sub = 0;
  for (int i = 0; i < adj[v].size(); i++) {
    int ad = adj[v][i];
    if (ad == p) continue;
    if (!vis[ad]) {
      dfs_tarjan(ad, v);
      if (bef[ad] > ini[v]) {
        // Bridge
        num_bridges++;
      }
      if (bef[ad] >= ini[v] && p != -1) {
        // v is an articulation
        art[v] = true;
      }
      num_sub++;
    }
    bef[v] = min(bef[v], ini[ad]);
  }
  if (p == -1 && num_sub > 1) {
    // Root is an articulation
    art[v] = true;
  }
}

int curId;
vector<int> adjbct[2 * 112345];

void dfs_block_cut(int v, int id) {
  vis[v] = 1;
  if (id != -1) {
    adjbct[v].pb(id);
    adjbct[id].pb(v);
  }
  for (int i = 0; i < adj[v].size(); i++) {
    int ad = adj[v][i];
    if (!vis[ad]) {
      if (bef[ad] >= ini[v]) {
        curId++;
        adjbct[v].pb(curId);
        adjbct[curId].pb(v);
        dfs_block_cut(ad, curId);
      } else {
        dfs_block_cut(ad, id);
      }
    }
  }
}

int32_t main() {
  num_bridges = 0;
  T = 0;
  memset(vis, 0, sizeof vis);
  for (int i = 1; i <= n; i++) dfs_tarjan(i, -1);

  curId = n;
  memset(vis, 0, sizeof vis);
  for (int i = 1; i <= n; i++) dfs_block_cut(i, -1);
}
