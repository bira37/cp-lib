int mergesort_count(vector<int> & v){
  vector<int> a,b;
  if(v.size() == 1) return 0;
  for(int i=0; i<v.size()/2; i++) a.push_back(v[i]);
  for(int i=v.size()/2; i<v.size(); i++) b.push_back(v[i]);
  int ans = 0;
  ans += mergesort_count(a);
  ans += mergesort_count(b);
  a.push_back(LLONG_MAX);
  b.push_back(LLONG_MAX);
  int x = 0, y = 0;
  for(int i=0; i<v.size(); i++){
    if(a[x] <= b[y]){
      v[i] = a[x++];
    }
    else {
      v[i] = b[y++];
      ans += a.size() - x -1;
    }
  }
  return ans;
}
