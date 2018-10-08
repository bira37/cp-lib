#include <bits/stdc++.h>

using namespace std;

bool prime(int n){
  for(int i=2; i<=sqrt(n); i++){
    if(n%i == 0) return false;
  }
  return true;
}

int main(){
  int cnt = 0;
  for(int i=10; i<81; i++){
    cout << i << " " << cbrt(i) << endl;
  }
}
   
