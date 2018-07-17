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

inline int mod(int n){ return (n%1000000007); }

int gcd(int a, int b){
  if(a == 0 || b == 0) return 0;
  if(b == 1) return b;
  else return gcd(b, a%b);
}

int32_t main(){
	DESYNC;
	string s;
	cin >> s;
	string t;
	string k;
	for(char c : s){
	  if(c == '1') k+=c;
	  else t+=c;
	}
	s = k + t;
	int last = -1;
	for(int i=0; i<s.size(); i++){
	  if(s[i] == '2'){
	    sort(s.begin() + last+1, s.begin()+ i);
	    last = i;
	  }
	}
	sort(s.begin() + last+1, s.end());
	cout << s << endl;
}


