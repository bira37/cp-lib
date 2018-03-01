#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ff first
#define ss second
#define LL_MAX LLONG_MAX
#define LL_MIN LLONG_MIN
#define endl '\n'
#define pii pair<int, int>
#define pll pair<ll,ll> 
#define IOS_SYNC ios_base::sync_with_stdio
#define vi vector<int>
#define vll vector<ll>
#define vpll vector< pll >
#define vpii vector< pii >

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;

inline int mod(int n){ return (n%1000000007); } 

//////////////////////////////////////////////STL - Ordered Set////////////////////////////////////////////
typedef tree<
int, //change for pair<int,int> to use like multiset
null_type,
less<int>, //change for pair<int,int> to use like multiset
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

int differ = 0;

//////////////////////////////////////////////EXTRAS//////////////////////////////////////////////////////


int main(){
	IOS_SYNC(false);
	ordered_set myset; //declares a stl ordered set 
	myset.insert(1); //inserts
	myset.insert(make_pair(1, differ++)); //insertion for multiset 
	cout << *myset.find_by_order(k) << endl; //returns an iterator to the k-th element (or returns the end)
	cout << myset.order_of_key(x) << endl; //returns the number of elements strictly less than x
	cout << myset.order_of_key(myset.lower_bound(make_pair(x, 0))) << endl; //for multisets
	return 0;
}


