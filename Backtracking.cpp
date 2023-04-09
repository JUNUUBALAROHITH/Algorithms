#include <bits/stdc++.h>
#define int long long
#define ll long long
#define lld long double
#define MAX INT64_MAX
#define print(x) cout << x << '\n'
#define print1(x, y) cout << x << " " << y << '\n';
#define sortf(a) sort(a.begin(), a.end())
#define sortr(a) sort(a.rbegin(), a.rend())
#define reverse(x) reverse(x.begin(), x.end())
#define gsum(a) accumulate(a.begin(), a.end(), 0LL)
#define gmax(a) *max_element(a.begin(), a.end())
#define gmin(a) *min_element(a.begin(), a.end())
#define show(x)           \
    for (auto &i : x)     \
        cout << i << " "; \
    cout << endl;
#define show1(x)      \
    for (auto &i : x) \
        cout << i.first << " " << i.second << '\n';
#define set_bits(a) __builtin_popcountll(a)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
const int mod = 1000000007;
const lld pi = 3.1415926535897932;
using namespace std;
int t;
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

bool isSafe1(int row, int col, vector < string > board, int n) {
  // check upper element
  int duprow = row;
  int dupcol = col;

  while (row >= 0 && col >= 0) {
    if (board[row][col] == 'Q')
      return false;
    row--;
    col--;
  }

  col = dupcol;
  row = duprow;
  while (col >= 0) {
    if (board[row][col] == 'Q')
      return false;
    col--;
  }

  row = duprow;
  col = dupcol;
  while (row < n && col >= 0) {
    if (board[row][col] == 'Q')
      return false;
    row++;
    col--;
  }
  return true;
 }
  void solve(int col, vector < string > & board, vector <vector<string>> & ans, int n) {
  if (col == n) {
    ans.push_back(board);
    return;
  }
  for (int row = 0; row < n; row++) {
    if (isSafe1(row, col, board, n)) {
      board[row][col] = 'Q';
      solve(col + 1, board, ans, n);
      board[row][col] = '.';
    }
  }
  }
  vector<vector<string>> solveNQueens(int n) {
  vector < vector < string >> ans;
  vector < string > board(n);
  string s(n, '.');
  for (int i = 0; i < n; i++) {
    board[i] = s;
  }
  solve(0, board, ans, n);
  return ans;
  }

int32_t main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    fastio;
    t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
