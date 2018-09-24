#include <bits/stdc++.h>

using namespace std;

int c00,c01,c10,c11;

bool solve(string & a){
  int cnt00 = 0, cnt01 = 0, cnt10 = 0, cnt11 = 0;
  char last = a[0];
  for(int i=1; i<a.size(); i++){
    if(last == '0'){
      if(a[i] == '1') cnt01++;
      else cnt00++;
    }
    else {
      if(a[i] == '1') cnt11++;
      else cnt10++;
    }
    last = a[i];
  }
  if(cnt00 == c00 && cnt01 == c01 && cnt10 == c10 && cnt11 == c11) return true;
  return false;
}

int main(){
int arr[] = {100000,
100001,
100010,
100011,
100100,
100101,
100110,
100111,
101000,
101001,
101010,
101011,
101100,
101101,
101110,
101111,
110000,
110001,
110010,
110011,
110100,
110101,
110110,
110111,
111000,
111001,
111010,
111011,
111100,
111101,
111110,
111111,
1000000,
1000001,
1000010,
1000011,
1000100,
1000101,
1000110,
1000111,
1001000,
1001001,
1001010,
1001011,
1001100,
1001101,
1001110,
1001111,
1010000};
  
  cin >> c00 >> c01 >> c10 >> c11;
  int ans = 0;
  for(int i = 0; i<80-32+1; i++){
    string a = to_string(arr[i]);
    cout << a << endl;
    ans += solve(a);
  }
  cout << ans <<endl;
}
