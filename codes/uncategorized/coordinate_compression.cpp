/* Author: Ubiratan Correia Barbosa Neto
 * Coordinate Compression
 */

struct Compresser {
  vector<int> original;
  map<int, int> comp;
  Compresser() {}

  Compresser(int n) { original.resize(n, -1); }

  void compress(vector<int>& v) {
    vector<int> tmp;
    set<int> s;
    for (int i = 0; i < v.size(); i++) s.insert(v[i]);
    for (int x : s) tmp.pb(x);
    for (int i = 0; i < v.size(); i++) {
      int idx = lower_bound(tmp.begin(), tmp.end(), v[i]) - tmp.begin();
      original[idx] = v[i];
      v[i] = idx;
      comp[v[i]] = idx;
    }
  }

} compresser;
