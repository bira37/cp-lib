namespace Sorting {
 
/* Merge Sort + Inversion Count */
int merge(vector<int> &a, vector<int> &b, int l, int mid, int r) {
  int ans = 0;
  int k = mid + 1;
  for (int i = l; i <= r; i++) {
    if (l <= mid && (k > r || a[l] <= a[k])) {
      b[i] = a[l++];
    } else {
      ans += mid - l + 1;
      b[i] = a[k++];
    }
  }
  return ans;
}
int merge_sort(vector<int> &a, vector<int> &b, int l, int r) {
  if (l == r) return 0;
  int mid = l + r >> 1;
  return merge_sort(b, a, l, mid) + merge_sort(b, a, mid + 1, r) +
         merge(a, b, l, mid, r);
}
int MergeSort(vector<int> &a) {
  vector<int> b = a;
  return merge_sort(b, a, 0, a.size() - 1);
}
/* Merge Sort + Inversion Count */
 
}  // namespace Sorting
