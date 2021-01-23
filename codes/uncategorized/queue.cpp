template <class T>
struct Queue {
  vector<int> queue;
  int top = 0;
  int size() { return (int)queue.size() - top; }
  bool empty() { return size() == 0; }
  void push(T item) { queue.push_back(item); }
  T get() {
    assert(!empty());
    return queue[top++];
  }
};
