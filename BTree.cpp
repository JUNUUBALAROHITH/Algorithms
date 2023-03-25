#include <bits/stdc++.h>
#define int long long
using namespace std;
#define MAX 4
#define MIN 2

struct btreeNode
{
    int val[MAX + 1], count;
    btreeNode *link[MAX + 1];
};

btreeNode *root;

/* creating new node */
btreeNode *createNode(int val, btreeNode *child)
{
    btreeNode *newNode = new btreeNode;
    newNode->val[1] = val;
    newNode->count = 1;
    newNode->link[0] = root;
    newNode->link[1] = child;
    return newNode;
}

/* Places the value in appropriate position */
void addValToNode(int val, int pos, btreeNode *node, btreeNode *child)
{
    int j = node->count;
    while (j > pos)
    {
        node->val[j + 1] = node->val[j];
        node->link[j + 1] = node->link[j];
        j--;
    }
    node->val[j + 1] = val;
    node->link[j + 1] = child;
    node->count++;
}

/* split the node */
void splitNode(int val, int *pval, int pos, btreeNode *node, btreeNode *child, btreeNode **newNode)
{
    int median, j;

    if (pos > MIN)
        median = MIN + 1;
    else
        median = MIN;

    *newNode = new btreeNode;
    j = median + 1;
    while (j <= MAX)
    {
        (*newNode)->val[j - median] = node->val[j];
        (*newNode)->link[j - median] = node->link[j];
        j++;
    }
    node->count = median;
    (*newNode)->count = MAX - median;

    if (pos <= MIN)
    {
        addValToNode(val, pos, node, child);
    }
    else
    {
        addValToNode(val, pos - median, *newNode, child);
    }
    *pval = node->val[node->count];
    (*newNode)->link[0] = node->link[node->count];
    node->count--;
}

/* sets the value val in the node */
int setValueInNode(int val, int *pval, btreeNode *node, btreeNode **child)
{

    int pos;
    if (!node)
    {
        *pval = val;
        *child = NULL;
        return 1;
    }

    if (val < node->val[1])
    {
        pos = 0;
    }
    else
    {
        for (pos = node->count;
             (val < node->val[pos] && pos > 1); pos--)
            ;
        if (val == node->val[pos])
        {
            cout << "Duplicates not allowed\n";
            return 0;
        }
    }
    if (setValueInNode(val, pval, node->link[pos], child))
    {
        if (node->count < MAX)
        {
            addValToNode(*pval, pos, node, *child);
        }
        else
        {
            splitNode(*pval, pval, pos, node, *child, child);
            return 1;
        }
    }
    return 0;
}

/* insert val in B-Tree */
void insert_into_Btree(int val)
{
    int flag, i;
    btreeNode *child;

    flag = setValueInNode(val, &i, root, &child);
    if (flag)
        root = createNode(i, child);
}

/* copy successor for the value to be deleted */
void copySuccessor(btreeNode *temp, int pos)
{
    btreeNode *temp1;
    temp1 = temp->link[pos];

    for (; temp1->link[0] != NULL;)
        temp1 = temp1->link[0];
    temp->val[pos] = temp1->val[1];
}

/* removes the value from the given node and rearrange values */
void removeVal(btreeNode *temp, int pos)
{
    int i = pos + 1;
    while (i <= temp->count)
    {
        temp->val[i - 1] = temp->val[i];
        temp->link[i - 1] = temp->link[i];
        i++;
    }
    temp->count--;
}

/* shifts value from parent to right child */
void doRightShift(btreeNode *temp, int pos)
{
    btreeNode *x = temp->link[pos];
    int j = x->count;

    while (j > 0)
    {
        x->val[j + 1] = x->val[j];
        x->link[j + 1] = x->link[j];
    }
    x->val[1] = temp->val[pos];
    x->link[1] = x->link[0];
    x->count++;

    x = temp->link[pos - 1];
    temp->val[pos] = x->val[x->count];
    temp->link[pos] = x->link[x->count];
    x->count--;
    return;
}

/* shifts value from parent to left child */
void doLeftShift(btreeNode *temp, int pos)
{
    int j = 1;
    btreeNode *x = temp->link[pos - 1];

    x->count++;
    x->val[x->count] = temp->val[pos];
    x->link[x->count] = temp->link[pos]->link[0];

    x = temp->link[pos];
    temp->val[pos] = x->val[1];
    x->link[0] = x->link[1];
    x->count--;

    while (j <= x->count)
    {
        x->val[j] = x->val[j + 1];
        x->link[j] = x->link[j + 1];
        j++;
    }
    return;
}

/* merge nodes */
void mergeNodes(btreeNode *temp, int pos)
{
    int j = 1;
    btreeNode *x1 = temp->link[pos], *x2 = temp->link[pos - 1];

    x2->count++;
    x2->val[x2->count] = temp->val[pos];
    x2->link[x2->count] = temp->link[0];

    while (j <= x1->count)
    {
        x2->count++;
        x2->val[x2->count] = x1->val[j];
        x2->link[x2->count] = x1->link[j];
        j++;
    }
    j = pos;
    while (j < temp->count)
    {
        temp->val[j] = temp->val[j + 1];
        temp->link[j] = temp->link[j + 1];
        j++;
    }
    temp->count--;
    free(x1);
}

/* adjusts the given node */
void adjustNode(btreeNode *temp, int pos)
{
    if (!pos)
    {
        if (temp->link[1]->count > MIN)
        {
            doLeftShift(temp, 1);
        }
        else
        {
            mergeNodes(temp, 1);
        }
    }
    else
    {
        if (temp->count != pos)
        {
            if (temp->link[pos - 1]->count > MIN)
            {
                doRightShift(temp, pos);
            }
            else
            {
                if (temp->link[pos + 1]->count > MIN)
                {
                    doLeftShift(temp, pos + 1);
                }
                else
                {
                    mergeNodes(temp, pos);
                }
            }
        }
        else
        {
            if (temp->link[pos - 1]->count > MIN)
                doRightShift(temp, pos);
            else
                mergeNodes(temp, pos);
        }
    }
}

/* delete val from the node */
int delValFromNode(int val, btreeNode *temp)
{
    int pos, flag = 0;
    if (temp)
    {
        if (val < temp->val[1])
        {
            pos = 0;
            flag = 0;
        }
        else
        {
            for (pos = temp->count; (val < temp->val[pos] && pos > 1); pos--)
                ;
            if (val == temp->val[pos])
            {
                flag = 1;
            }
            else
            {
                flag = 0;
            }
        }
        if (flag)
        {
            if (temp->link[pos - 1])
            {
                copySuccessor(temp, pos);
                flag = delValFromNode(temp->val[pos], temp->link[pos]);
                if (flag == 0)
                {
                    cout << "Given data is not present in B-Tree\n";
                }
            }
            else
            {
                removeVal(temp, pos);
            }
        }
        else
        {
            flag = delValFromNode(val, temp->link[pos]);
        }
        if (temp->link[pos])
        {
            if (temp->link[pos]->count < MIN)
                adjustNode(temp, pos);
        }
    }
    return flag;
}

/* delete val from B-tree */
void DELETION(int val, btreeNode *temp)
{
    btreeNode *tmp;
    if (!delValFromNode(val, temp))
    {
        cout << "Given value is not present in B-Tree\n";
        return;
    }
    else
    {
        if (temp->count == 0)
        {
            tmp = temp;
            temp = temp->link[0];
            free(tmp);
        }
    }
    root = temp;
    return;
}

/* search val in B-Tree */
void SEARCHING(int val, int *pos, btreeNode *temp)
{
    if (!temp)
    {
        return;
    }

    if (val < temp->val[1])
    {
        *pos = 0;
    }
    else
    {
        for (*pos = temp->count; (val < temp->val[*pos] && *pos > 1); (*pos)--)
            ;
        if (val == temp->val[*pos])
        {
            cout << "Given data is Found\n";
            return;
        }
    }
    SEARCHING(val, pos, temp->link[*pos]);
    return;
}

/* B-Tree Traversal */
void TRAVERSAL(btreeNode *temp)
{
    int i;
    if (temp != NULL)
    {
        for (i = 0; i < temp->count; i++)
        {
            TRAVERSAL(temp->link[i]);
            cout << temp->val[i + 1] << ' ';
        }
        TRAVERSAL(temp->link[i]);
    }
}

int32_t main()
{
    int x, c;
    cout << "ENTER ORDER: ";
    cin >> x;
    int n;
    cout << "Enter the number of keys: ";
    cin >> n;
    cout << "ENTER THE KEY-VALUES: ";
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        insert_into_Btree(x);
    }
    cout << "Traversal: ";
    TRAVERSAL(root);

    return 0;
}
