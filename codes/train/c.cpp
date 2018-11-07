#include <bits/stdc++.h>

#define int long long
#define double long double
#define ff first
#define ss second
#define endl '\n'
#define ii pair<int, int>
#define mp make_tuple
#define mt make_tuple
#define DESYNC ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define pb push_back
#define vi vector<int>
#define vii vector< ii >
#define EPS 1e-9
#define INF 1e18
#define ROOT 1
#define M 1000000007
const double PI = acos(-1);

using namespace std;

inline int mod(int n, int m){ int ret = n%m; if(ret < 0) ret += m; return ret; }

int gcd(int a, int b){
  if(a == 0 || b == 0) return 0;
  else return abs(__gcd(a,b));
}

int32_t main(){
  DESYNC;
  int t;
  cin >> t;
  while(t--){
    int n;
    cin >> n;
    string v[n];
    map<char, set<char> > dec;
    for(int i=0; i<n; i++)cin >> v[i];
    string s;
    string want;
    cin  >> s;
    cin >> want;
    for(int i=0; i<n; i++){
      char f[26];
      for(int i=0; i<26; i++) f[i] = '0';
      bool ok = true;
      for(int j = 0; j < v[i].size(); j++){
        if(f[s[j] - 'a'] != '0' && f[s[j] - 'a'] != v[i][j]){
          ok = false;
        }
        f[s[j] - 'a'] = v[i][j];
      }
      if(!ok) continue;
      cout << "ok for " << i << endl;
      for(int j=0; j<26; j++){
        if(f[j] == '0') continue;
        dec['a' + j].insert(f[j]);
        cout << "dec for " << char('a'+j) << " is " << f[j] << endl;
      }
    }
    map<char, char > decoda;
    for(auto it : dec){
      if(it.ss.size() == 1) decoda[*it.ss.begin()] = it.ff;
    } 
    string ans;
    for(int i=0; i<want.size(); i++){
      if(decoda.count(want[i]) == 1) ans += decoda[want[i]];
      else ans += '?';
    }
    cout << ans << endl;
    
  }     
}


