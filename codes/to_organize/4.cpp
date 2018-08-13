#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main(){
  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  int n;
  cin >> n;
  vector<int> A(n),B(n),C(n),D(n);
  for(int i=0; i<n; i++){
    cin >> A[i] >> B[i] >> C[i] >> D[i];
  }
  map<int,int> Cordeiro, Lucas;
  for(int x : A){
    for(int y : B){
      Cordeiro[x+y]++;
    }
  }
  for(int x : C){
    for(int y : D){
      Lucas[x+y]++;
    }
  }
  int ans = 0;
  for(pair<int,int> x : Cordeiro){
    int qtd = x.second;
    int num = -x.first;
    ans += qtd*Lucas[num];
  }
  cout << ans << endl;
}
