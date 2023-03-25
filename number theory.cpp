#include <bits/stdc++.h>
using namespace std;
#define int long long
// cout<<fixed<<setprecision(4)<<3.14159;
#define mod 10000009

// gcd
int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

// primeOrNot
bool primeOrNot(int n)
{
    int count = 0;
    for (int i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            count++;
            if (i * i != n)
                count++;
        }
        if (count > 2)
            return false;
    }
    if (count == 2)
        return true;
    else
        return false;
}
bool primeornot(int n)
{ // perfect method
    if (n <= 1)
    {
        return 0;
    }
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        { // encountering first factor
            return 0;
        }
    }
    return 1;
}

// checking prime or not and also no of divisors o(sqrt(n))
int noOfDivisors(int n)
{
    int divisors = 0;
    for (int i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            divisors++;
            if ((i * i) != n)
                divisors++;
        }
    }
    return divisors;
}
// if(divisors==2) // PRIME
// else NOT PRIME

// Euclidean Algo
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
} // __gcd(a,b) inbulit
// gcd(a,b)==gcd(a-b,b)==gcd(a,b-a)

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

// smallest prime factor using sieve
int spf[10000001];
void spfsieve()
{
    int max = 1000000;
    for (int i = 1; i <= max; i++)
        spf[i] = i;
    for (int i = 2; i * i <= max; i++)
    {
        if (spf[i] == i)
        {
            for (int j = i * i; j <= max; j += i)
            {
                spf[j] = i;
            }
        }
    }
}
map<int, int> m;
void primeFactorisation(int n)
{
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            int count = 0;
            while (n % i == 0)
            {
                count++;
                n /= i;
            }
            m[i] = count;
        }
    }
    if (n > 1)
        m[n]++;
}

// factors in vector

// THEOREM : pow(a,ETF(p))%p==1

// Binary Exponentiation
int power(int a, int n)
{
    int res = 1;
    while (n)
    {
        if (n % 2)
            res *= a, n--;
        else
            a *= a, n /= 2;
        res %= mod;
        a %= mod;
    }
    return res;
}

int fact[1000001];

// combinatorics
int ncr(int n, int r)
{
    return (fact[n] * (power(fact[n - r], mod - 2) * power(fact[r], mod - 2)) % mod) % mod;
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