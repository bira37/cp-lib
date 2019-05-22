#include <bits/stdc++.h>

#define int long long
#define double long double
#define ff first
#define ss second
#define endl '\n'
#define ii pair<int, int>
#define mp make_pair
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
  if(a == 0) return b;
  else return gcd(b%a, a);
}

void read_day(){
  int x;
  cin >> x;
  if(x == -1) exit(0);
}

void solve(){
  srand(time(NULL));
  int vase[21];
  for(int i=0; i<=20; i++) vase[i] = 0;
  set<int> used;
  vector<int> v;
  for(int i=0; i<20; i++) v.pb(i+1);
  int q = 0;
  while(q < 20){
    random_shuffle(v.begin(), v.end());
    for(int i=0; i<v.size() && q < 20; i++, q++){
      read_day();
      cout << v[i] << " " << 0 << endl;
      cout.flush();
      int n;
      cin >> n;
      if(n == -1) exit(0);
      vase[v[i]] = n;
      int x;
      while(n--){
        cin >> x;
        used.insert(x);
      }
    }
    v.clear();
    for(int i=1; i<=20; i++){
      if(vase[i] < 5) v.pb(i);
    }
  }
  
  //check min
  random_shuffle(v.begin(), v.end());
  for(int i=0; i<v.size() && q < 40; i++, q++){
    read_day();
    int number = *used.begin();
    used.erase(used.begin());
    cout << v[i] << " " << number << endl;
    cout.flush();
    vase[v[i]]++;
  }
  v.clear();
  for(int i=1; i<=20; i++){
    if(vase[i] < 5) v.pb(i);
  }
  
  while(q < 60){
    random_shuffle(v.begin(), v.end());
    for(int i=0; i<v.size() && q < 60; i++, q++){
      read_day();
      cout << v[i] << " " << 0 << endl;
      cout.flush();
      int n;
      cin >> n;
      if(n == -1) exit(0);
      vase[v[i]] = n;
      int x;
      while(n--){
        cin >> x;
        used.insert(x);
      }
    }
    v.clear();
    for(int i=1; i<=20; i++){
      if(vase[i] < 5) v.pb(i);
    }
  }
  
  random_shuffle(v.begin(), v.end());
  for(int i=0; i<v.size() && q < 80; i++, q++){
    read_day();
    int number = *used.begin();
    used.erase(used.begin());
    cout << v[i] << " " << number << endl;
    cout.flush();
    vase[v[i]]++;
  }
  v.clear();
  for(int i=1; i<=20; i++){
    if(vase[i] <= 5) v.pb(i);
  }
  
  while(q < 99){
    random_shuffle(v.begin(), v.end());
    for(int i=0; i<v.size() && q < 99; i++, q++){
      read_day();
      cout << v[i] << " " << 0 << endl;
      cout.flush();
      int n;
      cin >> n;
      if(n == -1) exit(0);
      vase[v[i]] = n;
      int x;
      while(n--){
        cin >> x;
        used.insert(x);
      }
    }
    v.clear();
    for(int i=1; i<=20; i++){
      if(vase[i] <= 5) v.pb(i);
    }
  }
  
  int ans = 1;
  int bst = INF;
  for(int x : v){
    if(vase[x] < bst){
      bst = vase[x];
      ans = x;
    }
  }
  read_day();
  cout << ans << " " << 100 << endl;
  cout.flush();
}

int32_t main(){
  int t;
  cin >> t;
  int tt = 1;
  while(t--){
    solve();
  }
}


