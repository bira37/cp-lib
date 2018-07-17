#include <bits/stdc++.h>

using namespace std;

int main(){
  string s;
  cin >> s;
  
  string rest;
  int p = s.size()-1;
  while(p >= 0 && s[p] != '0') rest+=s[p--];
  reverse(rest.begin(), rest.end());
  string zeroes;
  while(p>=0 && s[p] == '0') zeroes+=s[p--];
  string pot;
  while(p >= 0) pot += s[p--];
  
  reverse(pot.begin(), pot.end());
  reverse(zeroes.begin(), zeroes.end());
  if(pot.size() == 1 && pot[0] == '1'){
    string news;
    news += "10^";
    news += to_string(zeroes.size() + rest.size());
    if(rest.size() > 0){
      news += '+';
      news += rest;
    }
    if(news.size() <= s.size()) cout << news << endl;
    else cout << s << endl;
  }
  else {
    string news;
    news += pot;
    news += "*10^";
    news += to_string(zeroes.size() + rest.size());
    if(rest.size() > 0){
      news += '+';
      news += rest;
    }
    if(news.size() <= s.size()) cout << news << endl;
    else cout << s << endl;
  }
}
