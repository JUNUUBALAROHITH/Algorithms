#include <bits/stdc++.h>
using namespace std;
#define int long long
int t;

TreeNode *searchBST(TreeNode *root, int val)
{
    if (!root)
        return NULL;
    if (root->val == val)
        return root;
    if (root->val > val)
        return searchBST(root->left, val);
    if (root->val < val)
        return searchBST(root->right, val);
    return NULL;
}

void solve()
{
}

int32_t main()
{
    t = 1;
    // cin>>t;
    while (t--)
    {
        solve();
    }
}