#include <bits/stdc++.h>

using namespace std;

#define int long long

int32_t main(){
  int n;
  cin >> n;
  int sz = (31 - __builtin_clz(n)%32) + 1;
  cout << (1 << (sz-1) == n ? n : (1<<sz)) << endl;
}
