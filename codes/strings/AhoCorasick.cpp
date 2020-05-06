class AhoCorasick {
public:
  const static int ALPHABET_SIZE = 26;

  struct Vertex {
    std::array<int, ALPHABET_SIZE> next;
    int p = -1;
    char pch;
    int depth = 0;
    int link = 0;
    int next_terminal = 0;
    std::array<int, ALPHABET_SIZE> go;
    bool terminal = false;

    // extra values
    int value = 0;
    int value_acc = 0;
    // vector< pair<int, int> > occ;

    Vertex(int p, char ch, int depth) : p(p), pch(ch), depth(depth) {
      std::fill(next.begin(), next.end(), 0);
      std::fill(go.begin(), go.end(), 0);
    }
  };

  std::vector<Vertex> t;

  AhoCorasick() : t(1, {-1, '$', 0}) {}

  void add(std::string const& s, int value, int x = -1) {
    int v = 0;
    for (char ch : s) {
      int c = ch - 'a';
      if (!t[v].next[c]) {
        t[v].next[c] = t.size();
        t.emplace_back(v, ch, t[v].depth + 1);
      }
      v = t[v].next[c];
    }
    t[v].terminal = true;
    t[v].value += value;
    // t[v].occ.pb(ii(value, x));
  }

  void push_links() {
    std::queue<int> q;
    q.push(0);
    while (!q.empty()) {
      int v = q.front();
      auto& cur = t[v];
      auto& link = t[cur.link];
      q.pop();
      cur.next_terminal = link.terminal ? cur.link : link.next_terminal;
      cur.value_acc = link.value_acc + (cur.terminal ? cur.value : 0);
      // for(ii x : t[cur.next_terminal].occ) cur.occ.pb(x);
      for (int c = 0; c < ALPHABET_SIZE; c++) {
        if (cur.next[c]) {
          t[cur.next[c]].link = v ? link.next[c] : 0;
          q.push(cur.next[c]);
        } else {
          cur.next[c] = link.next[c];
        }
      }
    }
  }

  int go(int idx, char c) {
    return t[idx].next[c - 'a'];
  }

  pair<bool, int> get_val(int idx){
    return mp(t[idx].terminal, t[idx].value);
  }

  int get_acc(int idx){
    return t[idx].value_acc;
  }

  int get_next_terminal(int idx){
    return t[idx].next_terminal;
  }
};
