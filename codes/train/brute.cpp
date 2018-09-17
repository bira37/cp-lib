#include <bits/stdc++.h>

using namespace std;

int main(){
  int n;
  cin >> n;
  int ans = 0;
  int cur = 0;
  for(int i=1; i<=500000; i++){
    for(int j = 1; j<=i; j++){
      cur += j;
      ans ++;
      if(cur >= n){
        cout << ans << endl;
        return 0;
      }
    }
    for(int j = i-1; j>=1; j--){
      cur += j;
      ans ++;
      if(cur >= n){
        cout << ans << endl;
        return 0;
      }
    }
  }
}
