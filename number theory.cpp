#include <bits/stdc++.h>
using namespace std;
#define int long long
// cout<<fixed<<setprecision(4)<<3.14159;
#define mod 10000007

// __gcd(a,b) inbulit
// gcd(a,b)==gcd(a-b,b)==gcd(a,b-a)
string s1="geeksforgeeks",s2="for;
int found=s1.find(s2);
if(found!=string::npos) cout<<"Substring Exists";
else cout<<"Substring not exists";

// Sieve of eratostheses o(nloglogn)
bool isPrime[1000001]; //--> takes less space than integers 1e6+1
void sieve()
{
    int max = 1000000;
    for (int i = 1; i <= max; i++)
        isPrime[i] = 1;
    isPrime[0] = isPrime[1] = 0;
    for (int i = 2; i <= max; i++)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j <= max; j += i)
            {
                isPrime[j] = 0;
            }
        }
    }
}

void add(string x, string y)
{
    string s1 = "";
    reverse(x.begin(), x.end());
    reverse(y.begin(), y.end());
    int n1 = x.size(), n2 = y.size(), a = 0, b = 0, c = 0, s;
    while (n1 > a && n2 > b)
    {
        int p = x[a] - 48, q = y[b] - 48;
        s = (p + q + c) % 10;
        c = (p + q + c) / 10;
        // cout<<p<<" "<<q<<c<<'\n';
        s1 += (s + 48);
        a++;
        b++;
    }
    while (a < n1)
    {
        int p = x[a] - 48;
        s = (p + c) % 10;
        c = (p + c) / 10;
        s1 += (s + 48);
        a++;
    }
    while (b < n2)
    {
        int q = y[b] - 48;
        s = (q + c) % 10;
        c = (q + c) / 10;
        s1 += (s + 48);
        b++;
    }
    if (c != 0)
        s1 += c + 48;
    reverse(s1.begin(), s1.end());
    cout << s1;
}

string multiply(string num1, string num2)
{
    int len1 = num1.size();
    int len2 = num2.size();
    if (len1 == 0 || len2 == 0)
        return "0";

    // will keep the result number in vector
    // in reverse order
    vector<int> result(len1 + len2, 0);

    // Below two indexes are used to find positions
    // in result.
    int i_n1 = 0;
    int i_n2 = 0;

    // Go from right to left in num1
    for (int i = len1 - 1; i >= 0; i--)
    {
        int carry = 0;
        int n1 = num1[i] - '0';

        // To shift position to left after every
        // multiplication of a digit in num2
        i_n2 = 0;

        // Go from right to left in num2
        for (int j = len2 - 1; j >= 0; j--)
        {
            // Take current digit of second number
            int n2 = num2[j] - '0';

            // Multiply with current digit of first number
            // and add result to previously stored result
            // at current position.
            int sum = n1 * n2 + result[i_n1 + i_n2] + carry;

            // Carry for next iteration
            carry = sum / 10;

            // Store result
            result[i_n1 + i_n2] = sum % 10;

            i_n2++;
        }

        // store carry in next cell
        if (carry > 0)
            result[i_n1 + i_n2] += carry;

        // To shift position to left after every
        // multiplication of a digit in num1.
        i_n1++;
    }
}

// primes till given number using sieve
vector<int> primes(int n)
{
    vector<int> u;
    vector<int> v(n + 1, 1);
    v[0] = 1, v[1] = 0;
    for (int i = 2; i * i <= n; i++)
    {
        if (v[i])
        {
            for (int j = i * i; j <= n; j++)
            {
                v[j] = 0;
            }
        }
    }
    for (int i = 0; i <= n; i++)
    {
        if (v[i])
            u.push_back(i);
    }
    return u;
}
// if primes form l to r is asked precompute sieve(r) and traverse sieve O(nloglogn)

// finding prime factor without checking every factor as prime
vector<int> primeFactors(int n)
{
    int p = n;
    vector<int> v;
    if (n % 2 == 0)
    {
        v.push_back(2);
        while (n % 2 == 0)
            n /= 2;
    }

    for (int i = 3; i <= p; i += 2)
    {
        if (n % i == 0)
        {
            v.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1)
        v.push_back(n);
    return v;
}

// prime factorisation using map
map<int, int> primeFactorisation(int n)
{
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            int c = 0;
            while (n % i == 0)
            {
                c++;
                n /= i;
            }
            m[i] = c;
        }
    }
    if (n > 1)
        m[n]++;
}

// finding least prime factor for q queries
vector<int> v;
void leastprimefactorsusingsieve(int n)
{
    v.resize(n + 1);
    for (int i = 1; i < n + 1; i++)
    {
        v[i] = i;
    }
    for (int i = 2; i <= n; i++)
        v[i] = 2;
    for (int i = 3; i <= n; i += 2)
    {
        if (v[i] == i)
        {
            for (int j = i * i; j <= n; j += i)
            {
                if (v[j] == j)
                    v[j] = i;
            }
        }
    }
} //-->do sieve upto max element of given queries

// to find least prime factor
// for single query: O(sqrt(n)) is prefered
// for more queries: sieve O(nloglogn) is prefered

// find whether given number perfect square or not
bool perfectSquare(int n)
{
    int count = 0;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            count++;
            if (i * i != n)
                count++;
        }
        if (count % 2)
            return 1;
        return 0;
    }
}

bool prefectSquare(int n)
{
    int p = sqrt(n);
    if (p * p == n)
        return 1;
    return 0;
}

// binary exponentiation
int power(int a, int b, int mod)
{
    int ans = 1;
    while (b)
    {
        if (b % 2)
            ans = (ans * a) % mod, b--;
        else
            a = (a * a) % mod, b /= 2;
    }
    return ans;
}

// modulo multiplicative inverse
// brute force
int multiplicativeInverse(int a, int m)
{
    for (int x = 1; x < m; x++)
    {
        if (((a % m) * (x % m)) % m == 1)
            return x;
    }
}
// optimal
int multiplicativeInverse(int a, int m)
{
    int g = gcd(a, m);
    if (g != 1)
        return 0;
    return power(a, m - 2, m);
}
// (a/b)%m -->(a*b^-1)%m

// binary coefficient --> required to precompute factorial array for many queries
int fact[1000001];
fact.resize(n + 1);
fact[0] = 1, fact[1] = 1;
for (int i = 2; i < n + 1; i++)
{
    fact[i] = i * fact[i - 1];
}
int ncr(int n, int r)
{
    int b = (fact[n] * power(fact[r], mod - 2)) % mod;
    int c = (b * power(fact[n - r], mod - 2)) % mod;
    return c;
}

// number palindrome
bool isPalindrome(string s)
{
    int n = s.size();
    for (int i = 0; i < n / 2; i++)
    {
        if (s[i] != s[n - i - 1])
            return 0;
    }
    return 1;
}

// finding largest prime factor of given queires O(nloglogn) -->sieve
long long largestPrimeFactor(int n)
{
    vector<int> v(n + 2);
    for (int i = 0; i < n + 2; i++)
    {
        v[i] = i;
    }
    for (int i = 2; i < n + 2; i += 2)
        v[i] = 2;
    for (int i = 3; i < n + 2; i += 2)
    {
        if (v[i] == i)
        {
            for (int j = 2 * i; j < n + 2; j += i)
            {
                v[j] = i;
            }
        }
    }
    return v[n];
}

// finding largest prime factor of given n O(sqrt(n))
long long largestPrimefactor(int n)
{
    vector<int> v;
    int p = n;
    if (n % 2 == 0)
    {
        v.push_back(2);
        while (n % 2 == 0)
            n /= 2;
    }
    for (int i = 3; i * i <= p; i += 2)
    {
        if (n % i == 0)
        {
            v.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 2)
        v.push_back(n);
    sort(v.begin(), v.end());
    return v[v.size() - 1];
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
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    fact[0] = 1;
    // Factorial array precomputation
    for (int i = 1; i <= 1000001; i++)
        fact[i] = (i * fact[i - 1]) % mod;
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}
