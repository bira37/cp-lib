#include <bits/stdc++.h>

#define int long long
#define ff first
#define ss second
#define endl '\n'
#define ii pair<int, int>
#define DESYNC ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define pb push_back
#define vi vector<int>
#define vii vector< ii >
#define EPS 1e-9
#define INF 1e18
#define ROOT 1

using namespace std;

map<int, string> name;
int v[33];
int mat[33][33];
int n;

void print_ans(int id, set<int> s){
  if(s.size() == 0){
    cout << name[id] << " can win" << endl;
    return;
  }
  cout << name[id] << " cannot win because of the following teams:" << endl;
  cout << "   ";
  for(int x : s) cout << " " << name[x];
  cout << endl;
}

void solve(int id){
  set<int> s;
  int sum = 0;
  for(int i=0; i<n; i++){
    if(i == id) continue;
    for(int x : s){
      sum += mat[i][x];
    }
    s.insert(i);
    sum += v[i];
  }
  int cur = 0;
  for(int x : s){
    cur += mat[id][x];
  }
  cur += v[id];
  if(cur*s.size() < sum){
    print_ans(id, s);
    return;
  }
  while(!s.empty()){
    int best = -1;
    int best_val = INT_MIN;
    for(int x : s){
      int tira = 0;
      for(int y : s){
        if(x == y)  continue;
        tira += mat[x][y];
      }
      tira += v[x];
      if((sum - tira) - (cur - mat[x][id])*((int)s.size()-1) > best_val){
        best_val = (sum - tira) - (cur - mat[x][id])*((int)s.size()-1);
        best = x;
      }
    }
    int tira = 0;
    for(int y : s){
      if(best == y)  continue;
      tira += mat[best][y];
    }
    tira += v[best];
    sum -= tira;
    cur -= mat[best][id];
    s.erase(s.find(best));
    if(cur*s.size() < sum){
      print_ans(id, s);
      return;
    }
  }
  print_ans(id, s);   
}

int32_t main(){
  cin >> n;
  for(int i=0; i<n; i++){
    string s;
    cin >> s;
    cin >> v[i];
    name[i] = s;
  }
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      cin >> mat[i][j];
    }
  }
  
  for(int i=0; i<n; i++) solve(i);
}
     
