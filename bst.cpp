#include <bits/stdc++.h>
using namespace std;
struct node
{
    int key;
    node *left;
    node *right;
};

node *createNode(int n)
{
    node *temp = new node;
    temp->key = n;
    temp->left = NULL;
    temp->right = NULL;
}

int height(node *head){
    if(!head) return 0;
    else return 1+max(height(head->left),height(head->right));
}

int BalanceFactor(node *head){
    if(!head) return 0;
    else{
        return height(head->left)-height(head->right);
    }
}

node *insertNode(node *head, node *temp)
{
    if (!head)
    {
        head = temp;
        return head;
    }
    if (temp->key < head->key)
        head->left = insertNode(head->left, temp);
    else
        head->right = insertNode(head->right, temp);
    return head;
}

void reverseLevelOrder(node *head){
    stack<node *> st;
    queue<node *> q;
    q.push(head);
    node *temp;
    while(q.empty()==false){
        st.push(q.front());
        q.pop();
        if(st.top()->left) q.push(st.top()->left);
        if(st.top()->right) q.push(st.top()->right);
    }
    while(st.empty()==false){
        cout<<st.top()<<" ";
        st.pop();
    }
}

node *minValNode(node *head){
    node *current=head->right;
    while(current->left) current=current->left;
    return current;
}

node *deleteNode(node *head, int k)
{
    if (!head)
        return NULL;
    if (head->key > k)
        head->left = deleteNode(head->left, k);
    else if (head->key < k)
        head->right = deleteNode(head->right,k);
    else
    {
        if (!head->left)
        {
            node *temp=head->right;
            delete head;
            return temp;
        }
        else if(!head->right){
            delete head;
            return NULL;
        }
        else{
            node *temp=minValNode(head);
            head->key=temp->key;
            head->right=deleteNode(head->right,temp->key);
        }
    }
    return head;
}

node *RightRotate(node *head){
    node *x=head->left;
    node *y=x->right;
    x->right=head;
    head->left=y;
    return x;
}

node *LeftRotate(node *head){
    node *y=head->right;
    node *x=y->left;
    y->left=head;
    head->left=x;
    return y;
}

node *deleteAVLNode(node *head, int k)
{
    if (!head)
        return NULL;
    if (head->key > k)
        head->left = deleteNode(head->left, k);
    else if (head->key < k)
        head->right = deleteNode(head->right,k);
    else
    {
        if (!head->left)
        {
            node *temp=head->right;
            delete head;
            return temp;
        }
        else if(!head->right){
            delete head;
            return NULL;
        }
        else{
            node *temp=minValNode(head);
            head->key=temp->key;
            head->right=deleteNode(head->right,temp->key);
        }
    }

    int bf=BalanceFactor(head);

    if(bf==2 && BalanceFactor(head->left)>=0){
        return RightRotate(head);
    }
    else if(bf==2 && BalanceFactor(head->left)==-1){
        head->left=LeftRotate(head->left);
        return RightRotate(head);
    }
    else if(bf==-2 && BalanceFactor(head->right)<=0){
        return LeftRotate(head);
    }
    else if(bf==-2 && BalanceFactor(head->right)==1){
        head->right=RightRotate(head->right);
        return LeftRotate(head);
    }
    
    return head;
}

node *deleteLevelNode(node *head,int level){
    if(!head) return NULL;
    if(level==0){
        head=deleteNode(head,head->key);
    }
    else{
        head->left=deleteLevelNode(head->left,level-1);
        head->right=deleteLevelNode(head->right,level-1);
    }
    return head;
}

void inorder(node *head)
{
    if (head)
    {
        inorder(head->left);
        cout << head->key << " ";
        inorder(head->right);
    }
}

int main()
{
    int i, j;
    node *head = NULL, *temp = NULL;
    i = 1;
    while (i != 0)
    {
        cout << "Enter value to be inserted :";
        cin >> j;
        if (j == -1)
            break;
        else
        {
            temp = createNode(j);
            head = insertNode(head, temp);
        }
    }
    reverseLevelOrder(head);
    inorder(head);
    cout << "Enter node to be deleted :";
    cin >> j;
    head = deleteNode(head, j);
    inorder(head);
}