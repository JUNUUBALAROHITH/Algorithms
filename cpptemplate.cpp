#include <bits/stdc++.h>
#define int long long
#define ll long long
#define mod 1000000007
#define ARR_SIZE 100005
#define set_bits(a) __builtin_popcountll(a)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
using namespace std;
int t;
int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

void solve()
{
    
}

int32_t main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    fastio;
    // t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}