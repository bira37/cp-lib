#include <bits/stdc++.h>
#define int long long
using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n;
  cin >> n;
  int v[n];
  int acc = 0;
  for(int i=0; i<n; i++){
    cin >> v[i];
  }
  
  for(int i=0; i<n-1; i++){
    int l = 0, r = 22;
    int ans = -1;
    while(l <= r){
      int m = (l+r)>>1;
      if(i + (1<<m) < n){
        ans = i + (1<<m);
        l = m+1;
      }
      else r = m-1;
    }
    v[ans] += v[i];
    acc += v[i];
    cout << acc << endl;
  }
}
 
