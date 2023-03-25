#include <bits/stdc++.h>
using namespace std;
#define int long long
int t;
const int MAX = 100001;

void solve()
{
}

// Quick sort faster than Merge sort as quick sort is tail recursive but merge is not tail recursive
// preorder,inorder traversal --> tail recursive
// postorder traversal --> non tail recursive

void printNto1(int n){ // "TAIL RECURSION" comparitively faster than non tail recursion
    if(n==0) return;
    cout<<n<<" ";
    printNto1(n-1);
}

void printNto1(int n){ // tail call elimination
    start:
    if(n==0) return;
    cout<<n<<' ';
    n--;
    goto start;
}

void print1toN(int n){
    if(n==0) return;
    print1toN(n-1);
    cout<<n<<" ";  // just interchanging lines reverses the pattern
}
int k=1;
void print1toN(int n,int k){ // coverting to tail recursive with some auxilary space 
    if(n==0) return;
    cout<<k<<' ';
    print1toN(n-1,k+1); 
}

// int k=1;
int fact(int n,int k){ // tail recursion
    if(n==1 || n==0) return k;
    return fact(n-1,k*n);
}


// int start=0,end=n-1;
bool isPalindrome(string s,int start,int end){
    if(start>=end) return true;
    return (s[start]==s[end] && isPalindrome(s,start+1,end-1));
}

// Q) Rod cutting for given n in peices of a,b,c;
// return maximumm no of cuts
int rodCutting(int n,int a,int b,int c){
    if(n==0) return 0;
    if(n<0) return -1;
    int res=max(rodCutting(n-a,a,b,c),max(rodCutting(n-b,a,b,c),rodCutting(n-c,a,b,c)));
    if(res==-1) return -1;
    return res+1;
}

// subSet("abc","",0);
void subSet(string s,string s1,int p,int n){
    if(p==n){
        cout<<s1<<" ";
        return;
    }
    subSet(s,s1,p+1,n);
    subSet(s,s1+=s[p],p+1,n);
}


int josephusProblem(int n,int k){
    if(n==1){
        return 0;
    }
    return (josephusProblem(n-1,k)+k)%n;
}

// print all permutations of given string 
void permutation(string s,int i=0){
    if(i==s.length()-1){
        cout<<s<<" ";
        return;
    }
    for(int j=i;j<s.length();j++){
        swap(s[i],s[j]);
        permutation(s,i+1);
        swap(s[i],s[j]);
    }
}

// sum of first n numbers
void sumOfNNatural(int n,int sum){
    if(n<1){
        cout<<sum<<"\n";
        return; 
    }
    sumOfNNatural(n-1,sum+n);
}

int sumOfNNumbers(int n){
    if(n==0) return 0;
    return n+sumOfNNumbers(n-1);
}

// reversing the array
//  call reverseArray(arr,0,n-1) in main function
void reverseArray(int arr[],int l,int r){
    if(l>=r) return;
    swap(arr[l],arr[r]);
    reverseArray(arr,l+1,r-1);
}

// printing all subsequences 
// call printSubSequences(arr,empty vector,0,n);
void printSubSequences(int arr[],vector<int> v,int ind,int n){
    if(ind==n){
        for(auto &i:v) cout<<i<<" ";
        cout<<'\n';
        return;
    }
    v.push_back(arr[ind]);
    printSubSequences(arr,v,ind+1,n);
    v.pop_back();
    printSubSequences(arr,v,ind+1,n);
}

// print all Sub Sequences with sum k
// call printWithSumK(arr,empty vector,0,0,k);
void printWithSumK(int arr[],vector<int> v,int sum,int ind,int k,int n){
    if(sum==k || ind==n){
        for(auto &i:v) cout<<i<<" ";
        cout<<'\n';
        return;
    }
    v.push_back(arr[ind]);
    printWithSumK(arr,v,sum+arr[ind],ind+1,k,n);
    v.pop_back();
    printWithSumK(arr,v,sum,ind+1,k,n);
}

// count noOfSubSequences with given sum k
int countSubSequencewithSumK(int arr[],vector<int> v,int k,int sum,int ind,int n){
    if(ind==n){
        if(sum==k){
            return 1;
        }
        return 0;
    }
    v.push_back(arr[ind]);
    int l=countSubSequencewithSumK(arr,v,k,sum+arr[ind],ind+1,n);
    v.pop_back();
    int r=countSubSequencewithSumK(arr,v,k,sum,ind+1,n);
    return l+r;
}

int32_t main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    // t = 1;
    while (t--)
    {
        solve();
        int arr[5]={1,2,2,1,1};
        vector<int> v;
        cout<<countSubSequencewithSumK(arr,v,2,0,0,5);
    }
}