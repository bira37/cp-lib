#include <bits/stdc++.h>

#define int long long

using namespace std;

#define ROOT 1

int sum[812345], rmq[812345];
int v[212345];

void build_rmq(int root, int l, int r){
  if(l == r){
    rmq[root] = v[l];
    return;
  }
  int m = (l+r)>>1;
  build_rmq(2*root, l, m);
  build_rmq(2*root+1, m+1, r);
  rmq[root] = max(rmq[2*root], rmq[2*root+1]);
}

void build_sum(int root, int l, int r){
  if(l == r){
    sum[root] = v[l];
    return;
  }
  int m = (l+r)>>1;
  build_sum(2*root, l, m);
  build_sum(2*root+1, m+1, r);
  sum[root] = sum[2*root] + sum[2*root+1];
}

int query_sum(int root, int l, int r, int a, int b){
  if(l == a && r == b) return sum[root];
  int m = (l+r)>>1;
  if(b <= m) return query_sum(2*root, l, m, a, b);
  else if(m < a) return query_sum(2*root+1, m+1, r, a, b);
  
  int left = query_sum(2*root, l, m, a, m);
  int right = query_sum(2*root+1, m+1, r, m+1, b);
  return left + right;
}

int find_val(int root, int l, int r, int val){
  if(l == r) return (rmq[root] >= val ? l : -1);
  int m = (l+r)>>1;
  if(rmq[2*root] >= val) return find_val(2*root, l, m, val);
  else if(rmq[2*root+1] >= val) return find_val(2*root+1, m+1, r, val);
  else return -1;
}

int query_rmq(int root, int l, int r, int a, int b, int val){
  if(l == a && r == b){
    return find_val(root, l , r, val);
  }
  int m = (l+r)>>1;
  if(b <= m) return query_rmq(2*root, l , m, a , b, val);
  else if(m < a) return query_rmq(2*root+1, m+1, r, a, b, val);
  
  int left = query_rmq(2*root, l, m, a, m, val);
  int right = query_rmq(2*root+1, m+1, r, m+1, b, val);
  if(left != -1 && right != -1) return min(left, right);
  else if(left == -1) return right;
  else return left;
}

void rmq_update(int root, int l, int r, int id, int val){
  if(l == r){
    rmq[root] = val;
    return;
  }
  int m = (l+r)>>1;
  if(id <= m) rmq_update(2*root, l, m, id, val);
  else rmq_update(2*root+1, m+1, r, id, val);
  rmq[root] = max(rmq[2*root], rmq[2*root+1]);
}

void sum_update(int root, int l, int r, int id, int val){
  if(l == r){
    sum[root] = val;
    return;
  }
  int m = (l+r)>>1;
  if(id <= m) sum_update(2*root, l, m, id, val);
  else sum_update(2*root+1, m+1, r, id, val);
  sum[root] = sum[2*root] + sum[2*root+1];
}

int32_t main(){
  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  int n, q;
  cin >> n >> q;
  for(int i=0; i<n; i++) cin >> v[i];
  build_rmq(1, 0, n-1);
  build_sum(1, 0, n-1);
  
  while(q--){
    int id, val;
    cin >> id >> val;
    id--;
    rmq_update(1, 0, n-1, id, val);
    sum_update(1, 0, n-1, id, val);
    v[id] = val;
    if(v[0] == 0){
      cout << 1 << endl;
      continue;
    }
    int good = 0;
    int ans = -1;
    //cout << "array is " << endl;
    //for(int i=0; i<n; i++){
    //  cout << v[i] << " ";
    //}
    //cout << endl;
    while(good < n-1){
      //cout << "good is " << good << endl;
      int check = query_sum(1, 0, n-1, 0, good);
      int get = query_rmq(1, 0, n-1, good+1, n-1, check);
      //cout << "val to check is " << check << endl;
      //cout << "index choosen was " << get << endl;
      //cout << "val of index is " << v[get] << endl;
      if(get == -1){
        break;
      }
      if(v[get] == query_sum(1, 0, n-1, 0, get-1)){
        ans = get+1;
        break;
      }
      good = get;
    }
    cout << ans << endl;
  }
}  
  
