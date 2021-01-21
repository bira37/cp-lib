/* Author: Ubiratan Neto
 * Trie structure example
 */
namespace Trie {
const int SIZE_NODE = 26;
struct node {
  node *adj[SIZE_NODE];
  node() {
    for (int i = 0; i < SIZE_NODE; i++) adj[i] = nullptr;
  }
};

struct Tree {
  node *t;

  Tree() { t = new node(); }

  void add() {
    node *cur = t;
    // add logic here
  }

  int query() {
    node *cur = t;
    // add logic here
  }

  void remove() {
    node *cur = t;
    // add logic here
  }
};

}  // namespace Trie
