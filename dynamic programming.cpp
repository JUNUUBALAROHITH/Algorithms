#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAX = 100001;

// DP --> recursion + memorisation(OVERLAPPING SUBPROBLEMS)
// 1) Combinations and Probabilty 
// 2) Optimisation(Minimum/ Maximum)
// 3) YES/NO problems

        // 1
// Fibonacci Optimiation using dynamic programming
int dp[MAX]; // O(n)

int fib(int n)
{
    if (n == 0 || n == 1)
        return 1;
    if (dp[n] != -1)
        return dp[n];
    return dp[n] = fib(n - 1) + fib(n - 2); // memorization and recursion
}
int fib(int n)
{
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= n; i++)
        dp[i] = dp[i - 1] + dp[i - 2];
}                                           // iterative approach

        // 2
// Catalan number Cn=sigma(i =0 to n-1)(Ci * Cn-i-1)
long long catalan(int n){
    if(n<=1){
        return 1;
    }
    long long ans=0;
    for(int i=0;i<n;i++) ans+=catalan(i)*catalan(n-i-1);
    return ans;
}

        // 3
// Bell numbers no of ways of partitioning a set of n numbers
// S(n,k)--> no of partitions of n elements into k sets
// bell(n)--> sigma(k=1 to n)S(n,k)
//  S(n+1,k)=k*S(n,k)+S(n,k-1)
// 1) It is added as a single element set to existing partitions, i.e, S(n, k-1) 
// 2) It is added to all sets of every partition, i.e., k*S(n, k)

        // 4
// Binomial Coefficient recursion C(n, k) = C(n-1, k-1) + C(n-1, k) 
int binomialCoeffUtil(int n, int k, int** dp)
{
    // If value in lookup table then return
    if (dp[n][k] != -1) //    
        return dp[n][k];
 
    // store value in a table before return
    if (k == 0) {
        dp[n][k] = 1;
        return dp[n][k];
    }
     
    // store value in table before return
    if (k == n) {
        dp[n][k] = 1;
        return dp[n][k];
    }
     
    // save value in lookup table before return
    dp[n][k] = binomialCoeffUtil(n - 1, k - 1, dp) +
               binomialCoeffUtil(n - 1, k, dp);
    return dp[n][k];
}
 
int binomialCoeff(int n, int k)
{
    int** dp; // make a temporary lookup table
    dp = new int*[n + 1];
 
    // loop to create table dynamically
    for (int i = 0; i < (n + 1); i++) {
        dp[i] = new int[k + 1];
    }
 
    // nested loop to initialise the table with -1
    for (int i = 0; i < (n + 1); i++) {
        for (int j = 0; j < (k + 1); j++) {
            dp[i][j] = -1;
        }
    }
 
    return binomialCoeffUtil(n, k, dp);
}

        // 5
// COIN CHANGE min no of coins required for given amount
int dp[10010];
int fun(vector<int> &coins,int amount){
    if(amount==0) return 0;
    if(dp[amount]!=-1) return dp[amount];
    int ans=INT_MAX;
    for(int i=0;i<coins.size();i++){
        if(amount-coins[i]>=0) ans=min(ans+0LL,fun(coins,amount-coins[i])+1LL);
    }
    return dp[amount]=ans;
}
int coinChange(vector<int>& coins, int amount) {
    memset(dp,-1,sizeof(dp));
    if(fun(coins,amount)==INT_MAX) return -1;
    return fun(coins,amount);
}

        // 6
// subset sum 
// n=6 {3,34,4,12,5,2}
// sum=30
// op: false
bool f(int i,int sum,vector<int> &v,vector<vector<int>> &dp){
    if(i==0) {
        if(sum==0 || sum==v[0]) return 1;
        return 0;
    }
    if(sum==0) return 1;
    if(dp[i][sum]!=-1) return dp[i][sum];
    if(v[i]<=sum) return dp[i][sum]=f(i-1,sum-v[i],v,dp)||f(i-1,sum,v,dp);
    return dp[i][sum]=f(i-1,sum,v,dp);
}

bool isSubsetSum(vector<int>v, int sum){
    // code here 
    int n=v.size();
    vector<vector<int>> dp(n,vector<int> (sum+1,-1));
    return f(n-1,sum,v,dp);
}

        // 7
// Rod cutting 
// n=8 {1,5,8,9,10,17,17,20}
// op: 22(5+17)
int cutRod(int price[], int n) {
    //code here
    int dp[n+1][n+1];
    for(int i=0;i<n+1;i++) dp[0][i]=0;
    for(int i=0;i<n+1;i++) dp[i][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i<=j){
                dp[i][j]=max(price[i-1]+dp[i][j-i],dp[i-1][j]);
            }
            else dp[i][j]=dp[i-1][j];
        }
    }
    return dp[n][n];
}

        // 8
// painting ways
// n walls k colors no three consecutive are same
int mod=1e9+7;
long long f(int n,int k,vector<long long> &dp){
    if(n==0) return k;
    else if(n==1) return k*k;
    if(dp[n]!=-1) return dp[n];
    return dp[n]=((k-1)*(f(n-1,k,dp)%mod+f(n-2,k,dp)%mod))%mod;
}

long long countWays(int n, int k){
    vector<long long> dp(n+1,-1);
    return f(n-1,k,dp);
}

        // 9
// longest increasing subsequence
int f(int i,int j,int a[],vector<vector<int>> &dp,int n){
    if(i==n) return 0;
    if(dp[i][j+1]!=-1) return dp[i][j+1];
    if(j==-1 || a[i]>a[j]){
        return dp[i][j+1]=max(1+f(i+1,i,a,dp,n),f(i+1,j,a,dp,n));
    }
    return dp[i][j+1]=f(i+1,j,a,dp,n);
}

int longestSubsequence(int n, int a[])
{
    vector<vector<int>> dp(n+1,vector<int> (n+1,-1));
    return f(0,-1,a,dp,n);
}

        // 10
// max square submatrix having all elements 1s 
int f(int n,int m,vector<vector<int>> &v,vector<vector<int>> &dp){
    if(n<0 || m<0) return 0;
    if(dp[n][m]!=-1) return dp[n][m];
    if(v[n][m]==1) return dp[n][m]=1+min(f(n-1,m-1,v,dp),min(f(n-1,m,v,dp),f(n,m-1,v,dp)));
    int x=f(n-1,m-1,v,dp),y=f(n-1,m,v,dp),z=f(n,m-1,v,dp);
    return dp[n][m]=0;
}

int maxSquare(int n, int m, vector<vector<int>> v){
    vector<vector<int>> dp(n,vector<int> (m,-1));
    for(int i=0;i<n;i++) dp[i][0]=v[i][0];
    for(int i=0;i<m;i++) dp[0][i]=v[0][i];
    int k= f(n-1,m-1,v,dp);
    int c=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            // cout<<dp[i][j]<<" ";
            if(c<dp[i][j]) c=dp[i][j];
        }
        // cout<<'\n';
    }
    return c;
}

        // 11
// max path sum in matrix
// (i,j)->(i+1,j),(i+1,j+1),(i+1,j-1) possible
int f(int i,int j,int n,vector<vector<int>> &v,vector<vector<int>> &dp){
    if(i==n-1) return v[i][j];
    if(dp[i][j]!=-1) return dp[i][j];
    if(j==0 && j<n-1) return dp[i][j]=v[i][j]+max(f(i+1,j,n,v,dp),f(i+1,j+1,n,v,dp));
    else if(j==0 && j==n-1) return dp[i][j]=v[i][j]+f(i+1,j,n,v,dp);
    else if(j>0 && j==n-1) return dp[i][j]=v[i][j]+max(f(i+1,j-1,n,v,dp),f(i+1,j,n,v,dp));
    return dp[i][j]=v[i][j]+max(f(i+1,j,n,v,dp),max(f(i+1,j+1,n,v,dp),f(i+1,j-1,n,v,dp)));
}

int maximumPath(int n, vector<vector<int>> v)
{
    vector<vector<int>> dp(n+1,vector<int>(n+1,-1));
    int c=0;
    for(int i=0;i<n;i++) c=max(c,f(0,i,n,v,dp));
    return c;
}

        // 12
// min no of jumps to reach end of array
// already done by bottom up memorization

        // 13
// longest common substring
int longestCommonSubstr (string s1, string s2, int n, int m)
{
    int dp[n+1][m+1];
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            if(i==0 || j==0) dp[i][j]=0;
            else if(s1[i-1]==s2[j-1]) dp[i][j]=1+dp[i-1][j-1];
            else dp[i][j]=0;
        }
    }
    int c=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            c=max(c,dp[i][j]);
        }
    }
    return c;
}

// Bottom Up approach : iterative approach
// Top Bottom approach : recursion + memorisation approach
// 1) Vacation
// const int MAX = 100001;
// int points[MAX][3];
// int dp[MAX][3];

// int ans(int n, int j)
// {
//     if (n == 1)
//         return max(points[n - 1][0], max(points[n - 1][1], points[n - 1][2]));
//     if (dp[n][j] != -1)
//         return dp[n][j];
//     int m = 0;
//     for (int i = 0; i < 3; i++)
//     {
//         if (i != j)
//         {
//             m = max(m, ans(n - 1, i));
//         }
//     }
//     return dp[n][j] = m + points[n - 1][j];
// }

// void solve()
// {
//     int n;
//     cin >> n;
//     for (int i = 0; i < n; i++)
//     {
//         cin >> points[i][0] >> points[i][1] >> points[i][2];
//     }
//     cout << max(ans(n, 0), max(ans(n, 1), ans(n, 2))) << '\n';
// }

// 2) dp[i]=>maximuim score you can get by considering numbers till i;


	//14
// whether subset exists with target sum
// memorization
bool f(int ind,int k,vector<int> &v,vector<vector<int>> &dp,int n){
    if(k==0) return true;
    if(ind<0) return false;
    if(dp[ind][k]!=-1) return dp[ind][k];
    if(v[ind]<=k){
        return dp[ind][k]=(f(ind-1,k,v,dp,n)|(f(ind-1,k-v[ind],v,dp,n)));
    }
    return dp[ind][k]=f(ind-1,k,v,dp,n);
}

bool subsetSumToK(int n, int k, vector<int> &v) {
    // Write your code here.
    vector<vector<int>> dp(n+1,vector<int> (k+1,-1));
    return f(n-1,k,v,dp,n);
}
// tabulation
bool subsetSumToK(int n, int k, vector<int> &v) {
    bool dp[n+1][k+1];
    for(int i=0;i<=k;i++) dp[0][i]=0;
    for(int i=0;i<=n;i++) dp[i][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=k;j++){
            int take=0;
            if(v[i-1]<=j) dp[i-1][j-v[i]];
            int n=dp[i-1][j];
            dp[i][j]=take|n;
        }
    }
    return dp[n][k];
}

	//15
// no of subsets with sum k
int f(int ind,int sum,vector<int> &v,vector<vector<int>> &dp){
    if(ind==0){
        if(sum==0 && v[0]==0) return 2;
        if(sum==0 || v[0]==sum) return 1;
        return 0;
    }
    if(dp[ind][sum]!=-1) return dp[ind][sum];
    if(v[ind]<=sum) return dp[ind][sum]=f(ind-1,sum-v[ind],v,dp)+f(ind-1,sum,v,dp);
    return dp[ind][sum]=f(ind-1,sum,v,dp);
}

	//16
int findWays(vector<int> &v, int k)
{
    // Write your code here.
    int n=v.size();
    vector<vector<int>> dp(n,vector<int> (k+1,-1));
    return f(n-1,k,v,dp);
}

// two subsets with min abs diff
int minSubsetSumDifference(vector<int>& v, int n)
{
	// Write your code here.
	int k=0;
	for(auto &i:v) k+=i;
	bool dp[n+1][k+1];
	for(int i=0;i<=k;i++) dp[0][i]=0;
	for(int i=0;i<=n;i++) dp[i][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=k;j++){
			int take=0;
			if(v[i-1]<=j) take=dp[i-1][j-v[i-1]];
			int n=dp[i-1][j];
			dp[i][j]=take|n; 
		}
	}
	int m=INT_MAX;
	for(int i=0;i<=k;i++){
		if(dp[n][i]==1) m=min(m,abs(i-(k-i)));
	}
	return m;
}

	//17
//s1="horse" s2="ros"
//1 insert
//2 remove
//3 replace
//find minimum no of operations
int editDistance(string s1, string s2)
{
    //write you code here
    int m=s1.size(),n=s2.size();
    int dp[m+1][n+1];
    for(int i=0;i<=m;i++) dp[i][0]=i;
    for(int i=0;i<=n;i++) dp[0][i]=i;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(s1[i-1]==s2[j-1]) dp[i][j]=dp[i-1][j-1];
            else dp[i][j]=1+min(dp[i-1][j-1],min(dp[i-1][j],dp[i][j-1]));
        }
    }
    return dp[m][n];

}

	//18
//wildcard pattern matching
//s1="?ay"  s2="ray" --> true
//s1="**" s2="fvdgb" -->true
//s1="fffsf" s2="dfzvbdfg" -->false
//memeorization
bool f(int i,int j,string p,string t,vector<vector<int>> &dp){
   if(i<0 && j<0) return 1;
   else if(i<0 && j>=0) return 0;
   else if(j<0 && i>=0){
      for(int k=0;k<=i;k++){
         if(p[k]!='*') return 0;
      }
      return 1;
   }
   if(dp[i][j]!=-1) return dp[i][j];
   if(p[i]=='?' || p[i]==t[j]) return dp[i][j]=f(i-1,j-1,p,t,dp);
   else if(p[i]=='*'){
      return dp[i][j]=f(i-1,j,p,t,dp)|f(i,j-1,p,t,dp);
   }
   return dp[i][j]=0;
}


bool wildcardMatching(string p, string t)
{
   int m=p.size(),n=t.size();
   vector<vector<int>> dp(m+1,vector<int> (n+1,-1));
   return f(m-1,n-1,p,t,dp);
}

//tabuation
bool wildcardMatching(string p, string t)
{
   int m=p.size(),n=t.size();
   bool dp[m+1][n+1];
   for(int i=1;i<=m;i++) dp[i][0]=0;
   dp[0][0]=1;
   for(int i=1;i<=n;i++){
      if(p[i-1]=='*') dp[0][i]=dp[0][i-1];
      else dp[0][i]=0;
   }
   for(int i=1;i<=m;i++){
      for(int j=1;j<=n;j++){
         if(p[i-1]=='?' || p[i-1]==t[j-1]) dp[i][j]=dp[i-1][j-1];
         else if(p[i-1]=='*') dp[i][j]=dp[i-1][j]|dp[i][j-1];
         else dp[i][j]=0;
      }
   }
   return dp[m][n];
}


	//19
//arr[]={7,1,4,5,6,2} o/p=5
// buy at 1 and sell at 6 maximize profit
int maximumProfit(vector<int> &v){
    int n=v.size(),ans=0;
    vector<int> v1(n);
    v1[n-1]=v[n-1];
    for(int i=n-2;i>=0;i--) v1[i]=max(v1[i+1],v[i]);
    for(int i=0;i<n;i++){
        ans=max(ans,v1[i]-v[i]);
    }
    return ans;
}


int t;
void solve()
{
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
    for (int i = 0; i < MAX; i++)
        dp[i] = -1;
    // cin >> t;
    t = 1;
    while (t--)
    {
        cout << fib(5);
        solve();
    }
}
