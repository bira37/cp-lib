#include <bits/stdc++.h>

#define int long long

int32_t main(){
  int t;
  std::cin >> t;
  while(t--){
    int n,k;
    std::cin >> n >> k;
    int v[n];
    for(int i=0; i<n; i++){
      std::cin >> v[i];
    }
    std::sort(v,  v+n, std::greater<int>());
    int ans = 0;
    for(int i=0; i<n; i++){
      ans += (v[i] >= v[k-1]);
    }
    std::cout <<ans << std::endl;
  }
        
}


