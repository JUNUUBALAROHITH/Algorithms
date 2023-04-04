#include <bits/stdc++.h>
using namespace std;
#define int long long

//vvi
1)check whether xth bit is set or not -->(n&(1<<x)
2)set xth bit of n --> n=n|(1<<x)
3)Toggle xth bit of n --> n=n^(1<<x)
4)find lowest set bit of n --> n&(-n) 
5)unset lsb of n --> n=n^(n&(-n))
6)power of 2 --> !(n&(n-1)) for n>0

// n-1 is n except 1s complement from least significant set bit to least significant bit
// n=10100 --> n-1=10011
// any integer should have atmost 32 bits think for optimal code

// No of set bits
int setBits(int n) // Brian Kernighan Algo
{
    int count = 0;
    while (n)
    {
        n &= (n - 1);
        count++;
    }
    return count;
} // long long  _builtin_popcountll(int);
// if(n==1) POWEROF2
// else NOTPOWEROF2

// Two odd no of times repeating numbers in array
// Since two numbers different atleast one it is different
void oddAppearing(int arr[], int n)
{
    int XOR = 0, res1 = 0, res2 = 0;
    for (int i = 0; i < n; i++)
        XOR ^= arr[i];
    int firstSetBitNum = XOR ^ (~XOR); // --> Right Most Set Bit
    for (int i = 0; i < n; i++)
    {
        if (firstSetBitNum & arr[i])
            res1 ^= arr[i];
        else
            res2 ^= arr[i];
    }
    cout << res1 << " " << res2 << '\n';
}

// log2() --> inbuilt for logarithm base 2
// if(!(b&(b-1))) --> b is power of 2
// set ith bit to 0 --> n&=(1LL<<i);
// O(1) : __builtin_popcount(x): This function is used to count the number of one’s(set bits) in an integer.
// O(1) : __builtin_clz(x): This function is used to count the leading zeros of the integer. Note : clz = count leading zero’s
// O(1) : __builtin_ctz(x): This function is used to count the trailing zeros of the given integer. Note : ctz = count trailing zeros.

void printPowerSet(string s)
{
    int n = s.length();
    int powSize = pow(2, n);
    for (int counter = 0; counter < powSize; counter++)
    {
        for (int j = 0; j < n; j++)
        {
            if (counter & (1 << j))
                cout << s[j];
        }
        cout << '\n';
    }
}

// To iterate throught all sub bitmasks 11-->10,9,8,3,2,1,0
// for(int j=x;j>0;j=(j-1)&x){
//      cout<<j<<”\n”;
// }
// cout<<0<<”\n”;

// Binary Representation of given number
void bin(unsigned int n)
{
    if (n > 1)
        bin(n / 2);
    cout << n % 2;
}

void solve()
{
    cout << ceil(5 / 2);
}


// To print all subsets of given array
// vector<int> v = {1,2,10}
// Int n = v.size();
// for(int i=0;i<(1<<n);i++){
//    for(int j=0;j<n;j++){
//      if(i&(1<<j)){cout<<v[j]<<” “;}
//         }
//     cout<<”\n”;
// }


int32_t main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}

//bitmask
//x=1100 
//y=1101
//x is submask of y
//x&y==x --> x is submask of y <-- x|y==y
//iterate through all submasks of n
//for(int x=n;x>0;x=(x-1)&n)
//{
//    cout<<x<<'\n';
//}
//cout<<0<<'\n'; //-->seperate case

//iternate thrugh all submasks of n
//for(int i=0;i<(1<<n);i++)   O(3^n)
//{
//  for(int x=i;x>0;x=(x-1)&i)
//  {
//      cout<<x<<" ";
//  }
//  cout<<0<<'\n';
//}

