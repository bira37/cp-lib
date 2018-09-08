// C++ program to efficiently count number of
// subarrays with XOR less than k
#include <bits/stdc++.h>
using namespace std;
 
// trie node
struct node
{
    struct node* left;
    struct node* right;
    struct node* parent;
    int leaf = 1;
};
 
// head node of trie
struct node* head = new node;
 
// initializing a new node
void init(node* temp)
{
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;
    temp->leaf = 1;
}
 
// updating the leaf count of trie
// nodes after insertion
void update(node* root)
{
    // updating from bottom to
    // top (leaf to root)
    if (root->right && root->left) // sum of left and right
        root->leaf = root->right->leaf + root->left->leaf;
    else if (root->left) // only the left
        root->leaf = root->left->leaf;
    else if (root->right) // only the right
        root->leaf = root->right->leaf;
 
    if (root->parent) // updating the parent
        update(root->parent);
}
 
// function to insert a new
// binary number in trie
void insert(string num, int level, node* root)
{
    // if added the last node updates the
    // leaf count using update function
    if (level == -1)
    {
        update(root);
        return;
    }
 
    // conversion to integer
    int x = num[level] - '0';
    if (x == 1)
    {
        // adding a right child
        if (!root->right)
        {
            struct node* temp = new node;
            init(temp);
            root->right = temp;
            temp->parent = root;
        }
 
        // calling for the right child
        insert(num, level - 1, root->right);
    }
    else
    {
 
        // adding a left child
        if (!root->left)
        {
            struct node* temp = new node;
            init(temp);
            root->left = temp;
            temp->parent = root;
        }
 
        // calling for the left child
        insert(num, level - 1, root->left);
    }
}
 
// Utility function to find the number of
// subarrays with xor less than k
void solveUtil(string num, string k, int level,
               node* root, int& ans)
{
    if (level == -1)
        return;
 
    if (num[level] == '1')
    {
 
        // numbers in the right subtree
        // added to answer
        if (k[level] == '1')
        {
            if (root->right)
                ans += root->right->leaf;
            if (root->left)
                solveUtil(num, k, level - 1, root->left, ans);
        }
        else
        {
            if (root->right)
                solveUtil(num, k, level - 1, root->right, ans);
        }
 
    }
    else
    {
        if (k[level] == '0')
        {
            if (root->left)
                solveUtil(num, k, level - 1, root->left, ans);
        }
        else   // then the numbers in the left
        {
            // subtree added to answer
            if (root->left)
                ans += root->left->leaf;
            if (root->right)
                solveUtil(num, k, level - 1, root->right, ans);
        }
    }
}
 
// function to find the number of
// subarrays with xor less than k
int solve(int a[], int n, int K)
{
    int maxEle = K;
 
    // Calculate maximum element in array
    for (int i = 0; i < n; i++)
        maxEle = max(maxEle, a[i]);
 
    // maximum height of the Trie when
    // the numbers are added as binary strings
    int height = (int)ceil(1.0 * log2(maxEle)) + 1;
 
    // string to store binary
    // value of K
    string k = "";
 
    int temp = K;
 
    // converting go to binary string and
    // storing in k
    for (int j = 0; j < height; j++)
    {
        k = k + char(temp % 2 + '0');
        temp /= 2;
    }
 
    string init = "";
    for (int i = 0; i < height; i++)
        init += '0';
 
    // adding 0 to the trie(initial value)
    insert(init, height - 1, head);
 
    int ans = 0;
    temp = 0;
    for (int i = 0; i < n; i++)
    {
        string s = "";
        temp = (temp ^ a[i]);
 
        // converting the array element to binary string s
        for (int j = 0; j < height; j++)
        {
            s = s + char(temp % 2 + '0');
            temp = temp >> 1;
        }
 
        solveUtil(s, k, height - 1, head, ans);
 
        insert(s, height - 1, head);
    }
 
    return ans;
}
 
// Driver program to test above function
int main()
{
    init(head); // initializing the head of trie
 
    int n, k;
    
    cin >> n >> k;
    
    int arr[n];
    for(int i=0; i<n; i++) cin >> arr[i];
 
 
    cout << solve(arr, n, k+1) << endl;
 
    return 0;
}
