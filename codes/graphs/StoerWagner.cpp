/* Author: Ubiratan Correia Barbosa Neto
 * Stoer Wagner
 */

/* Initialization */
int cost[n + 1][n + 1];
memset(cost, 0, sizeof cost);
while (m--) {
  int u, v, c;
  u = input.next();
  v = input.next();
  c = input.next();
  cost[u][v] = c;
  cost[v][u] = c;
}
/* Stoer-Wagner: global minimum cut in undirected graphs */
int min_cut = 1000000000;
bool added[n + 1];
int vertex_cost[n + 1];
for (int vertices_count = n; vertices_count > 1; --vertices_count) {
  memset(added, 0, sizeof(added[0]) * (vertices_count + 1));
  memset(vertex_cost, 0, sizeof(vertex_cost[0]) * (vertices_count + 1));
  int s = -1, t = -1;
  for (int i = 1; i <= vertices_count; ++i) {
    int vert = 1;
    while (added[vert]) ++vert;
    for (int j = 1; j <= vertices_count; ++j)
      if (!added[j] && vertex_cost[j] > vertex_cost[vert]) vert = j;
    if (i == vertices_count - 1)
      s = vert;
    else if (i == vertices_count) {
      t = vert;
      min_cut = min(min_cut, vertex_cost[vert]);
    }
    added[vert] = 1;
    for (int j = 1; j <= vertices_count; ++j) vertex_cost[j] += cost[vert][j];
  }
  for (int i = 1; i <= vertices_count; ++i) {
    cost[s][i] += cost[t][i];
    cost[i][s] += cost[i][t];
  }
  for (int i = 1; i <= vertices_count; ++i) {
    cost[t][i] = cost[vertices_count][i];
    cost[i][t] = cost[i][vertices_count];
  }
}
printf("%d\n", min_cut);
