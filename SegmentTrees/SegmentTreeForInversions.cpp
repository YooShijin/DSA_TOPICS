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

class segtree
{
public:
    int n;
    vector<ll> tree;

    segtree(int sz)
    {
        n = sz;
        tree.resize(4 * sz + 1);
    }

    long long build(vector<ll> &a, int x, int lx, int rx)
    {
        if (lx == rx)
            return tree[x] = a[lx];

        int m = (lx + rx) / 2;

        long long left = build(a, 2 * x, lx, m);
        long long right = build(a, 2 * x + 1, m + 1, rx);

        return tree[x] = left + right;
    }

    void build(vector<ll> &a)
    {
        build(a, 1, 0, n - 1);
    }
    void set(int i, int x, int lx, int rx, long long val)
    {
        if (lx == rx)
        {
            tree[x] = val;
            return;
        }

        int m = (lx + rx) / 2;
        if (i <= m)
        {
            set(i, 2 * x, lx, m, val);
        }
        else
        {
            set(i, 2 * x + 1, m + 1, rx, val);
        }
        tree[x] = tree[2 * x] + tree[2 * x + 1];
    }
    void set(int i, long long val)
    {
        set(i, 1, 0, n - 1, val);
    }
    long long sum(int x, int lx, int rx, int l, int r)
    {
        if (r < lx || l > rx)
        {
            return 0;
        }

        if (l <= lx && rx <= r)
        {
            return tree[x];
        }
        int m = (lx + rx) / 2;
        long long leftSum = sum(2 * x, lx, m, l, r);
        long long rightSum = sum(2 * x + 1, m + 1, rx, l, r);

        return leftSum + rightSum;
    }
    long long sum(int l, int r)
    {
        return sum(1, 0, n - 1, l, r);
    }
};

void solve()
{
    ll n;
    cin >> n;
    vll a(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    segtree seg = segtree(n + 1);
    for (int i = 0; i < n; i++)
    {
        ll t = a[i];
        cout << seg.sum(t + 1, n) << " ";
        seg.set(t, 1);
    }
    cout << endl;
    return;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t = 1;
    while (t--)
    {
        solve();
    }
    return 0;
}
