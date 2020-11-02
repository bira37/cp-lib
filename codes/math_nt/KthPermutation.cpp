/* Find the k-th permutation of numbers from [1..n] */
/* Be careful: n <= 19 */
vi find_permutation(int n, int k) {
  int fat[n];
  fat[0] = 1;
  for (int i = 1; i < n; i++) fat[i] = fat[i - 1] * i;
  vi arr(n);
  iota(all(arr), 1);
  vi fatoriadic;
  for (int cur = k, i = 1; i <= n; i++) {
    fatoriadic.pb(cur % i);
    cur /= i;
  }
  reverse(all(fatoriadic));
  vi ans;
  for (int x : fatoriadic) {
    ans.pb(arr[x]);
    vi new_arr;
    for (int y : arr)
      if (y != arr[x]) new_arr.pb(y);
    swap(arr, new_arr);
  }
  return ans;
}
