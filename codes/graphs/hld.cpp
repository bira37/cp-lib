/* Author: Ubiratan Correia Barbosa Neto
 * heavy-Light Decomposition
 */

struct HLD {
  struct node {
    // node values
    int val = 0;  // sets neutral value for the needed operation
    int lazy = 0;
    node() {}
    node(int val) : val(val) { lazy = 0; }

    node merge(node b) {
      node ret;
      // merge nodes
      return ret;
    }
  };

  struct SegmentTree {
    vector<node> st;

    SegmentTree() {}

    void construct(int n) { st.resize(4 * n); }

    void propagate(int cur, int l, int r) {
      // check if exists operation

      // apply lazy

      if (l != r) {
        // propagate lazy
      }

      // reset lazy
    }

    void build(int cur, int l, int r) {
      if (l == r) {
        // apply on leaf
        return;
      }

      int m = (l + r) >> 1;

      build(2 * cur, l, m);
      build(2 * cur + 1, m + 1, r);
      st[cur] = st[2 * cur].merge(st[2 * cur + 1]);
    }

    void update(int cur, int l, int r, int a, int b, int val) {
      propagate(cur, l, r);
      if (b < l || r < a) return;
      if (a <= l && r <= b) {
        // apply on lazy
        propagate(cur, l, r);
        return;
      }
      int m = (l + r) >> 1;
      update(2 * cur, l, m, a, b, val);
      update(2 * cur + 1, m + 1, r, a, b, val);
      st[cur] = st[2 * cur].merge(st[2 * cur + 1]);
    }

    node query(int cur, int l, int r, int a, int b) {
      propagate(cur, l, r);
      if (b < l || r < a) return node();
      if (a <= l && r <= b) return st[cur];
      int m = (l + r) >> 1;
      node lef = query(2 * cur, l, m, a, b);
      node rig = query(2 * cur + 1, m + 1, r, a, b);
      return lef.merge(rig);
    }

  } st;

  vector<int> L, P, ch, subsz, in, out;
  int t;

  HLD() {}

  HLD(int n) {
    L.resize(n + 1);
    P.resize(n + 1);
    ch.resize(n + 1);
    subsz.resize(n + 1);
    in.resize(n + 1);
    out.resize(n + 1);
    st.construct(n + 1);
    t = 0;
    for (int i = 0; i <= n; i++) {
      ch[i] = i;
      P[i] = -1;
      L[i] = 0;
    }
  }

  void precalculate(int u, int p = -1) {
    subsz[u] = 1;
    for (int &v : adj[u]) {
      if (v == p) continue;
      P[v] = u;
      L[v] = L[u] + 1;
      precalculate(v, u);
      if (subsz[adj[u][0]] < subsz[v]) swap(adj[u][0], v);
      subsz[u] += subsz[v];
    }
  }

  void build(int u, int p = -1) {
    in[u] = ++t;
    for (int v : adj[u]) {
      if (v == p) continue;
      if (adj[u][0] == v) {
        ch[v] = ch[u];
      }
      build(v, u);
    }
    out[u] = t;
  }

  void calculate(int root = 1) {
    precalculate(root);
    build(root);
  }

  void build_ds() { st.build(1, 1, t); }

  void path_update(int a, int b, int val, bool edge_update = false) {
    while (ch[a] != ch[b]) {
      if (L[ch[b]] > L[ch[a]]) swap(a, b);
      st.update(1, 1, t, in[ch[a]], in[a], val);
      a = P[ch[a]];
    }
    if (L[b] < L[a]) swap(a, b);
    if (in[a] + edge_update <= in[b])
      st.update(1, 1, t, in[a] + edge_update, in[b], val);
  }

  void node_update(int u, int val) { st.update(1, 1, t, in[u], in[u], val); }

  void edge_update(int u, int v, int val) {
    if (L[u] > L[v]) swap(u, v);
    st.update(1, 1, t, in[v], in[v], val);
  }

  void subtree_update(int u, int val, bool edge_update = false) {
    if (in[u] + edge_update <= out[u])
      st.update(1, 1, t, in[u] + edge_update, out[u], val);
  }

  node path_query(int a, int b, bool edge_query = false) {
    node ans;
    while (ch[a] != ch[b]) {
      if (L[ch[b]] > L[ch[a]]) swap(a, b);
      ans = ans.merge(st.query(1, 1, t, in[ch[a]], in[a]));
      a = P[ch[a]];
    }
    if (L[b] < L[a]) swap(a, b);
    if (in[a] + edge_query <= in[b])
      ans = ans.merge(st.query(1, 1, t, in[a] + edge_query, in[b]));
    return ans;
  }

  node node_query(int u) { return st.query(1, 1, t, in[u], in[u]); }

  node edge_query(int u, int v) {
    if (L[u] > L[v]) swap(u, v);
    return st.query(1, 1, t, in[v], in[v]);
  }

  node subtree_query(int u, bool edge_query = false) {
    if (in[u] + edge_query <= out[u])
      return st.query(1, 1, t, in[u] + edge_query, out[u]);
    else
      return node();
  }
};
