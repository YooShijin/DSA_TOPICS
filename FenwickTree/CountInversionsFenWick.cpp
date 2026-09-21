#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define pb push_back
#define vi vector<int>
#define vll vector<ll>
#define pii pair<int, int>
#define pll pair<ll, ll>
#define all(x) (x).begin(), (x).end()
#define ff first
#define ss second

#define FOR(i, a, b) for (ll i = a; i < b; i++)
#define RFOR(i, a, b) for (ll i = a; i > b; i--)

#ifndef ONLINE_JUDGE
#define debug(x)         \
    cerr << #x << " = "; \
    _print(x);           \
    cerr << endl;
#else
#define debug(x)
#endif

void _print(int x) { cerr << x; }
void _print(ll x) { cerr << x; }
void _print(ld x) { cerr << x; }
void _print(char x) { cerr << x; }
void _print(string x) { cerr << x; }
void _print(bool x) { cerr << (x ? "true" : "false"); }

template <class T, class V>
void _print(pair<T, V> p);
template <class T>
void _print(vector<T> v);
template <class T>
void _print(set<T> v);
template <class T, class V>
void _print(map<T, V> v);
template <class T>
void _print(multiset<T> v);

template <class T, class V>
void _print(pair<T, V> p)
{
    cerr << "{";
    _print(p.ff);
    cerr << ", ";
    _print(p.ss);
    cerr << "}";
}
template <class T>
void _print(vector<T> v)
{
    cerr << "[ ";
    for (T i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <class T>
void _print(set<T> v)
{
    cerr << "[ ";
    for (T i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <class T>
void _print(multiset<T> v)
{
    cerr << "[ ";
    for (T i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}
template <class T, class V>
void _print(map<T, V> v)
{
    cerr << "[ ";
    for (auto i : v)
    {
        _print(i);
        cerr << " ";
    }
    cerr << "]";
}

ll binpow(ll a, ll n)
{
    ll ans = 1;
    ll b = n;
    while (b)
    {
        if (b & 1)
        {
            ans = ans * a;
        }
        a = a * a;
        b = b >> 1;
    }
    return ans;
}

class FenwickTree
{
private:
    int n;
    vector<long long> BIT;

public:
    FenwickTree(int size)
    {
        n = size;
        BIT.assign(n + 1, 0);
    }
    void update(int i, long long val)
    {

        while (i <= n)
        {
            BIT[i] += val;
            i += i & (-i);
        }
    }
    // gives the sum from 1 to index i
    long long sum(int i)
    {
        long long temp = 0;
        while (i > 0)
        {
            temp += BIT[i];
            i -= i & (-i);
        }
        return temp;
    }
    // gives the sum from i to j
    long long rangeSum(int i, int j)
    {
        return sum(j) - sum(i);
    }
};
void solve()
{
    ll n, q;
    cin >> n >> q;
    vll a(n);
    FenwickTree bit(n + 1);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        bit.update(i + 1, a[i]);
    }
    for (int i = 1; i < n + 1; i++)
    {
        cout << bit.rangeSum(i - 1, i) << " ";
    }
    cout << endl;
    while (q--)
    {
        ll t;
        cin >> t;
        if (t == 1)
        {
            ll ind, val;
            cin >> ind >> val;
            bit.update(ind, val);
        }
        else
        {
            ll a, b;
            cin >> a >> b;
            cout << bit.rangeSum(a - 1, b) << endl;
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}