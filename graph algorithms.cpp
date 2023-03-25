#include <bits/stdc++.h>
using namespace std;
#define int long long
int t;
const int MAX = 100001;
int points[MAX][3];
int dp[MAX][3];

int ans(int n, int j)
{
    if (n == 1)
        return max(points[n - 1][0], max(points[n - 1][1], points[n - 1][2]));
    if (dp[n][j] != -1)
        return dp[n][j];
    int m = 0;
    for (int i = 0; i < 3; i++)
    {
        if (i != j)
        {
            m = max(m, ans(n - 1, i));
        }
    }
    return dp[n][j] = m + points[n - 1][j];
}

void solve()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> points[i][0] >> points[i][1] >> points[i][2];
    }
    cout << max(ans(n, 0), max(ans(n, 1), ans(n, 2))) << '\n';
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
    // cin >> t;
    t = 1;
    for (int i = 0; i < MAX; i++)
    {
        dp[i][0] = -1;
        dp[i][1] = -1;
        dp[i][2] = -1;
    }
    while (t--)
    {
        solve();
    }
}