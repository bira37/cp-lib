/*
 * Suffix Automaton
 */

#include <bits/stdc++.h>

using namespace std;

struct SuffixAutomaton {
  vector<map<char, int>> nxt;
  vector<int> slink;
  vector<int> len;
  int lstr;
  int root;
  vector<bool> is_terminal;
  int slen;
  vector<vector<int>> slink_tree;
  // vector<int> terminals;

  SuffixAutomaton(const string& s) {
    slen = s.size();
    // add root
    nxt.push_back(map<char, int>());
    len.push_back(0);
    slink.push_back(-1);
    is_terminal.push_back(false);
    lstr = root = 0;

    for (int i = 0; i < s.size(); i++) {
      // add r
      nxt.push_back(map<char, int>());
      len.push_back(i + 1);
      slink.push_back(0);
      is_terminal.push_back(false);
      int r = nxt.size() - 1;

      // Find p (longest suffix of last r with edge with new character)
      int p = lstr;
      while (p >= 0 && nxt[p].count(s[i]) == 0) {
        // Add edge with new character
        nxt[p][s[i]] = r;
        p = slink[p];
      }
      if (p != -1) {
        // There is an suffix of last r that has edge to new character
        int q = nxt[p][s[i]];
        if (len[p] + 1 == len[q]) {
          // the longest suffix of new r is the logest of class q
          // There is no need to split
          slink[r] = q;
        } else {
          // Need to split
          // Add q'. New class that longest sufix of r and q.
          nxt.push_back(nxt[q]);  // Copy from q
          len.push_back(len[p] + 1);
          slink.push_back(slink[q]);  // Copy from q
          is_terminal.push_back(false);
          int ql = nxt.size() - 1;

          slink[q] = ql;
          slink[r] = ql;

          // q' will have every suffix of p that was previously conected to q
          while (p >= 0 && nxt[p][s[i]] == q) {
            nxt[p][s[i]] = ql;
            p = slink[p];
          }
        }
      }
      lstr = r;
      if (i == s.size() - 1) {
        p = r;
        while (p >= 0) {
          // terminals.push_back(p);
          is_terminal[p] = true;
          p = slink[p];
        }
      }
    }
  }

  bool is_substr(const string& s) {
    int cur = root;
    for (int i = 0; i < s.size(); i++) {
      if (nxt[cur].count(s[i]) == 0) return false;
      cur = nxt[cur][s[i]];
    }
    return true;
  }
  bool is_suffix(const string& s) {
    int cur = root;
    for (int i = 0; i < s.size(); i++) {
      if (nxt[cur].count(s[i]) == 0) return false;
      cur = nxt[cur][s[i]];
    }
    if (is_terminal[cur]) return true;
    return false;
  }

  void dfs_num_substr(int v, int* dp) {
    dp[v] = 1;
    for (pair<char, int> ad : nxt[v]) {
      if (dp[ad.second] == -1) dfs_num_substr(ad.second, dp);
      dp[v] += dp[ad.second];
    }
  }
  int num_substr() {
    int dp[nxt.size()];
    memset(dp, -1, sizeof dp);
    dfs_num_substr(root, dp);
    return dp[root] - 1;  // Remove empty substring
  }

  void dfs_num_matches(int v, int* dp) {
    dp[v] = 0;
    if (is_terminal[v]) dp[v] = 1;
    for (pair<char, int> ad : nxt[v]) {
      if (dp[ad.second] == -1) dfs_num_matches(ad.second, dp);
      dp[v] += dp[ad.second];
    }
  }
  int num_matches(const string& s) {
    int cur = root;
    for (int i = 0; i < s.size(); i++) {
      if (nxt[cur].count(s[i]) == 0) return 0;
      cur = nxt[cur][s[i]];
    }
    int dp[nxt.size()];
    memset(dp, -1, sizeof dp);
    dfs_num_matches(cur, dp);
    return dp[cur];
  }

  void dfs_first_match(int v, int* dp) {
    dp[v] = 0;
    if (is_terminal[v]) dp[v] = 1;
    for (pair<char, int> ad : nxt[v]) {
      if (dp[ad.second] == -1) {
        dfs_first_match(ad.second, dp);
        dp[v] = max(dp[v], dp[ad.second] + 1);
      }
    }
  }
  int first_match(const string& s) {
    int cur = root;
    for (int i = 0; i < s.size(); i++) {
      if (nxt[cur].count(s[i]) == 0) return -1;
      cur = nxt[cur][s[i]];
    }
    int dp[nxt.size()];
    memset(dp, -1, sizeof dp);
    dfs_first_match(cur, dp);
    return slen - (dp[cur] - 1) - s.size();
  }

  void dfs_all_matches(int v, vector<int>& ans) {
    // cout << v << endl;
    if (slink_tree[v].size() == 0) ans.push_back(len[v]);
    for (int ad : slink_tree[v]) {
      dfs_all_matches(ad, ans);
    }
  }
  vector<int> all_matches(const string& s) {
    slink_tree = vector<vector<int>>(slink.size());
    for (int i = 0; i < slink.size(); i++) {
      if (slink[i] >= 0) slink_tree[slink[i]].push_back(i);
    }
    int cur = root;
    for (int i = 0; i < s.size(); i++) {
      if (nxt[cur].count(s[i]) == 0) return vector<int>();
      cur = nxt[cur][s[i]];
    }
    vector<int> ans;
    dfs_all_matches(cur, ans);
    for (int i = 0; i < ans.size(); i++) {
      ans[i] -= s.size();
    }
    // Last one is not valid
    return ans;
  }
};

int main() {
  string s;
  cin >> s;
  SuffixAutomaton sa(s);
  cout << sa.num_substr() << endl;
  //  cout << sa.terminals.size() << endl;
  //  for(int ter : sa.terminals) cout << ter << " ";
  //  cout << endl;
  int T;
  cin >> T;
  string w;
  while (T--) {
    cin >> w;
    cout << sa.is_substr(w) << endl;
    cout << sa.is_suffix(w) << endl;
    cout << sa.num_matches(w) << endl;
    cout << sa.first_match(w) << endl;
    SuffixAutomaton sb(s + "$" + w);
    vector<int> matches = sb.all_matches(w);
    for (int i : matches) cout << i << " ";
    cout << endl;
  }
}
