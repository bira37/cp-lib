#include <bits/stdc++.h>

using namespace std;

set< vector<int> > s;
vector<int> v(5);
int acc = 0;
void solve(int i, int k, int n){
  if(i == n){
    if(acc != 10) return;
    vector<int> vv = v;
    sort(vv.begin(), vv.end());
    s.insert(vv);
    return;
  }
  for(int j = k; j >=0; j--){
    v[i] = j;
    acc += j;
    solve(i+1, k-j, n);
    acc -= j;
  }
}

int main(){
  solve(0, 10, 5);
  int cnt = 0;
  for(auto t : s){
    int mx = 0;
    for(int x : t) cout << x << " ";
    cout << endl;
    for(int x : t) mx = max(mx, x);
    if(mx > 5) cnt++;
  }
  cout << cnt << " " << s.size() << endl;
  int g = __gcd(cnt, (int)s.size());
  cout << cnt/g << " " << (int)s.size()/g << endl;
}
