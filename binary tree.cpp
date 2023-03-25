#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Iterative Pre-Order
vector<int> preorderTraversal(TreeNode *root)
{
    vector<int> v;
    if (!root)
        return v;
    stack<TreeNode *> s;
    s.push(root);
    while (!s.empty())
    {
        TreeNode *temp = s.top();
        s.pop();
        v.push_back(temp->val);
        if (temp->right)
            s.push(temp->right);
        if (temp->left)
            s.push(temp->left);
    }
    return v;
}

// Zig-Zag level order traversal
vector<vector<int>> zigzagLevelOrder(TreeNode *root)
{
    vector<vector<int>> v;
    if (!root)
        return v;
    stack<TreeNode *> s1, s2;
    s1.push(root);
    int c = 1;
    while (!s1.empty() || !s2.empty())
    {
        vector<int> v1;
        int n;
        if (c)
        {
            n = s1.size();
            for (int i = 0; i < n; i++)
            {
                TreeNode *temp = s1.top();
                v1.push_back(temp->val);
                s1.pop();
                if (temp->left)
                    s2.push(temp->left);
                if (temp->right)
                    s2.push(temp->right);
            }
            c = 0;
        }
        else
        {
            n = s2.size();
            for (int i = 0; i < n; i++)
            {
                TreeNode *temp = s2.top();
                v1.push_back(temp->val);
                s2.pop();
                if (temp->right)
                    s1.push(temp->right);
                if (temp->left)
                    s1.push(temp->left);
            }
            c = 1;
        }
        v.push_back(v1);
    }
    return v;
}

// Maximum depth in tree
int m = 0, ans = 0;
void preorder(TreeNode *root)
{
    if (!root)
    {
        ans = max(ans, m);
        return;
    }
    m++;
    preorder(root->left);
    if (root->left)
        m--;
    preorder(root->right);
    if (root->right)
        m--;
}
int maxDepth(TreeNode *root)
{
    preorder(root);
    return ans;
}
// or
int maxDepth(TreNode *root)
{
    if (!root)
        return 0;
    int l = maxDepth(root->left);
    int r = maxDepth(root->right);
    return 1 + max(l, r);
}

int maxPathSum(TreeNode *root)
{
    int maxi = INT_MIN;
    maxPathDown(root, maxi);
    return maxi;
}
int maxPathDown(TreeNode *node, int &maxi)
{
    if (!node)
        return 0;
    int l = max(0, maxPathDown(node->left, maxi));
    int r = max(0, maxPathDown(node->right, maxi));
    maxi = max(maxi, l + r + node->val);
    return max(l, r) + node->val;
}

// preimum-->Boundary Tree Traversal


// Vertical Order Traversal
vector<vector<int>> verticalTraversal(TreeNode *root)
{
    map<int, map<int, multiset<int>>> nodes;
    queue<pair<TreeNode *, pair<int, int>>> todo;
    todo.push({root, {0, 0}});
    while (!todo.empty())
    {
        auto p = todo.front();
        todo.pop();
        TreeNode *node = p.first;
        int x = p.second.first, y = p.second.second;
        nodes[x][y].insert(node->val);
        if (node->left)
            todo.push({node->left, {x - 1, y + 1}});
        if (node->right)
            todo.push({node->right, {x + 1, y + 1}});
    }
    vector<vector<int>> ans;
    for (auto p : nodes)
    {
        vector<int> col;
        for (auto &q : p.second)
        {
            col.insert(col.end(), q.second.begin(), q.second.end());
        }
        ans.push_back(col);
    }
    return ans;
}

// top view
vector<int> topView(Node *root)
{
    vector<int> ans;
    if (!root)
        return ans;
    map<int, int> mpp;
    queue<pair<Node *, int>> q;
    q.push({root, 0});
    while (!q.empty())
    {
        auto it = q.front();
        q.pop();
        Node *node = it.first;
        int line = it.second;
        if (mpp.find(line) == mpp.end())
            mpp[line] = node->data;
        if (node->left)
            q.push({node->left, line - 1});
        if (node->right)
            q.push({node->right, line + 1});
    }
    for (auto it : mpp)
    {
        ans.push_back(it.second);
    }
    return ans;
}

// bottom view
vector<int> bottomView(Node *root)
{
    vector<int> ans;
    if (!root)
        return ans;
    queue<pair<Node *, int>> q;
    map<int, int> mpp;
    q.push({root, 0});
    while (!q.empty())
    {
        auto it = q.front();
        q.pop();
        Node *node = it.first;
        int line = it.second;
        mpp[line] = node->data;
        if (node->left)
            q.push({node->left, line - 1});
        if (node->right)
            q.push({node->right, line + 1});
    }
    for (auto it : mpp)
    {
        ans.push_back(it.second);
    }
    return ans;
}

// rightside view
vector<int> rightSideView(TreeNode *root)
{
    vector<int> ans;
    if (!root)
        return ans;
    queue<pair<TreeNode *, int>> q;
    map<int, int> mpp;
    q.push({root, 0});
    while (!q.empty())
    {
        int n = q.size();
        int l = (q.front()).second;
        for (int i = 0; i < n; i++)
        {
            auto it = q.front();
            TreeNode *temp = it.first;
            if (temp->left)
                q.push({temp->left, l + 1});
            if (temp->right)
                q.push({temp->right, l + 1});
            if (i == n - 1)
            {
                mpp[l] = temp->val;
            }
            q.pop();
        }
    }
    for (auto it : mpp)
    {
        ans.push_back(it.second);
    }
    return ans;
}

// Symmetric or Not
bool isSymmetric(TreeNode *root)
{
    return !root || isSym(root->left, root->right);
}
bool isSym(TreeNode *l, TreeNode *r)
{
    if (!l || !r)
        return l == r;
    if (l->val != r->val)
        return 0;
    return isSym(l->left, r->right) && isSym(l->right, r->left);
}

// print root to node path

void getPath(TreeNode *root, vector<int> &ans, int k)
{
    if (!root)
        return;
}

vector<int> path(TreeNode *root, int k)
{
    vector<int> ans;
    if (!root)
        return ans;
    getPath(root, ans, k);
    return ans;
}

// lowest common ancestor
TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    if (!root || root == p || root == q)
        return root;
    TreeNode *left = lowestCommonAncestor(root->left, p, q);
    TreeNode *right = lowestCommonAncestor(root->right, p, q);
    if (!left)
        return right;
    else if (!right)
        return left;
    else
        return root;
}

// width of tree
int widthOfBinaryTree(TreeNode *root)
{
    if (!root)
        return 0;
    long long ans = 0;
    queue<pair<TreeNode *, long long>> q;
    q.push({root, 0});
    while (!q.empty())
    {
        int size = q.size();
        long long mmin = q.front().second; // to make the id starting from 0
        long long first, last;
        for (int i = 0; i < size; i++)
        {
            long long cur_id = q.front().second - mmin;
            TreeNode *node = q.front().first;
            q.pop();
            if (i == 0)
                first = cur_id;
            if (i == size - 1)
                last = cur_id;
            if (node->left)
                q.push({node->left, cur_id * 2 + 1});
            if (node->right)
                q.push({node->right, cur_id * 2 + 2});
        }
        ans = max(ans, last - first + 1);
    }
    return int(ans);
}

// construct unique binary tree using
// (preorder && inorder) || (postorder && inorder)

// preorder && inorder
TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
{
    map<int, int> inMap;
    for (int i = 0; i < inorder.size() - 1; i++)
    {
        inMap[inorder[i]] = i;
    }
    TreeNode *root = buildTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1, inMap);
    return root;
}

TreeNode *buildTree(vector<int> &preorder, int preStart, int preEnd, vector<int> &inorder, int inStart, int inEnd, map<int, int> inMap)
{
    if (preStart > preEnd || inStart > inEnd)
        return NULL;
    TreeNode *root = new TreeNode(preorder[preStart]);
    int inRoot = inMap[root->val];
    int numsLeft = inRoot - inStart;
    root->left = buildTree(preorder, preStart + 1, preStart + numsLeft, inorder, inStart, inRoot - 1, inMap);
    root->right = buildTree(preorder, preStart + numsLeft + 1, preEnd, inorder, inRoot + 1, inEnd, inMap);
    return root;
}

// postorder && inorder
Node *buildUtil(int in[], int post[], int inStrt, int inEnd,
                int *pIndex)
{
    // Base case
    if (inStrt > inEnd)
        return NULL;

    /* Pick current node from Postorder traversal using
       postIndex and decrement postIndex */
    Node *node = newNode(post[*pIndex]);
    (*pIndex)--;

    /* If this node has no children then return */
    if (inStrt == inEnd)
        return node;

    /* Else find the index of this node in Inorder
       traversal */
    int iIndex = search(in, inStrt, inEnd, node->data);

    /* Using index in Inorder traversal, construct left and
       right subtrees */
    node->right = buildUtil(in, post, iIndex + 1, inEnd, pIndex);
    node->left = buildUtil(in, post, inStrt, iIndex - 1, pIndex);

    return node;
}

// This function mainly initializes index of root
// and calls buildUtil()
Node *buildTree(int in[], int post[], int n)
{
    int pIndex = n - 1;
    return buildUtil(in, post, 0, n - 1, &pIndex);
}

int main()
{
}