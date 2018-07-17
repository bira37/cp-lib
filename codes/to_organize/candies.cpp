#include <bits/stdc++.h>

using namespace std;

#define int unsigned long long

bool check(int n, int m){
  int need = (n+1)/2LL;
  int cur = 0;
  while(n > 0){
    int tira = min(n, m);
    n -= tira;
    cur += tira;
    tira = min(n, (10LL*n)/100LL);
    n -= tira;
  }
  return need <= cur;
}

int32_t main(){
  int n;
  cin >> n;
  
  int l = 1, r = (int)1e18;
  int ans = 0;
  while(l <= r){
    int m = (l+r)>>1;
    if(check(n, m)){
      ans = m;
      r = m-1;
    }
    else l = m+1;
  }
  cout << ans << endl;
}
