#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

typedef tree<
int, //change for pair<int,int> to use like multiset
null_type,
less<int>, //change for pair<int,int> to use like multiset
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

//int differ = 0; for multiset

//ordered_set myset; //declares a stl ordered set 
//myset.insert(1); //inserts
//myset.insert(make_pair(1, differ++)); //insertion for multiset 
//myset.find_by_order(k)//returns an iterator to the k-th element (or returns the end)
//myset.order_of_key(x)//returns the number of elements strictly less than x
//myset.order_of_key(myset.lower_bound(make_pair(x, 0))) //for multisets
