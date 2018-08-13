#include <bits/stdc++.h>
#define int long long
using namespace std;

map<tuple<int,int,int>, set< pair<int,int > > > m;

int gcd(int a, int b){
  if(a == 0 || b == 0) return 0;
  else return __gcd(a,b);
}

int32_t main(){
  int n;
  cin >> n;
  pair<int,int> v[n];
  for(int i=0; i<n; i++){
    cin >> v[i].first >> v[i].second;
  }
  for(int i=0; i<n; i++){
    for(int j=i+1; j<n; j++){
      int x1,x2,y1,y2;
      x1 = v[i].first;
      x2 = v[j].first;
      y1 = v[i].second;
      y2 = v[j].second;
      int a = y1-y2;
      int b = x2-x1;
      int c = x1*y2 - x2*y1;
      if(a == 0 && b == 0 && c == 0){
        m[make_tuple(a, b, c)].insert(v[i]);
        m[make_tuple(a, b, c)].insert(v[j]);
      }
      else if(a == 0 && b == 0){
        if(c < 0) c *= -1;
        m[make_tuple(a, b, c/c)].insert(v[i]);
        m[make_tuple(a, b, c/c)].insert(v[j]);
      }
      else if(a == 0 && c == 0){
        if(b < 0) b *= -1;
        m[make_tuple(a, b/b, c)].insert(v[i]);
        m[make_tuple(a, b/b, c)].insert(v[j]);
      }
      else if(b == 0 && c == 0){
        if(a < 0) a *= -1;
        m[make_tuple(a/a, b, c)].insert(v[i]);
        m[make_tuple(a/a, b, c)].insert(v[j]);
      }
      else if(a == 0){
        if(b < 0) b *= -1, c *= -1;
        m[make_tuple(a, b/gcd(b,c), c/gcd(b,c))].insert(v[i]);
        m[make_tuple(a, b/gcd(b,c), c/gcd(b,c))].insert(v[j]);
      }
      else if(b == 0){
        if(a < 0) a *= -1, c *= -1;
        m[make_tuple(a/gcd(a,c), b, c/gcd(a,c))].insert(v[i]);
        m[make_tuple(a/gcd(a,c), b, c/gcd(a,c))].insert(v[j]);
      }
      else if(c == 0){
        if(a < 0) a *= -1, b *= -1;
        m[make_tuple(a/gcd(b,a), b/gcd(b,a), c)].insert(v[i]);
        m[make_tuple(a/gcd(b,a), b/gcd(b,a), c)].insert(v[j]);
      }
    }
  }
  int ans = (n*(n-1)*(n-2))/6;
  for(auto k : m){
    int val = k.second.size();
    ans -= (val*(val-1)*(val-2))/6;
  }
  cout << ans << endl;  
} 
