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
    void set(int i, int x, int lx, int rx)
    {
        if (lx == rx)
        {
            tree[x] = 1 ^ tree[x];
            return;
        }

        int m = (lx + rx) / 2;
        if (i <= m)
        {
            set(i, 2 * x, lx, m);
        }
        else
        {
            set(i, 2 * x + 1, m + 1, rx);
        }
        tree[x] = tree[2 * x] + tree[2 * x + 1];
    }
    void set(int i)
    {
        set(i, 1, 0, n - 1);
    }
    long long kth(int x, int k, int lx, int rx)
    {
        if (tree[x] <= k)
        {
            return -1;
        }
        if (lx == rx)
        {
            return lx;
        }
        int m = (lx + rx) / 2;
        long long left = -1;
        long long right = -1;
        if (k < tree[2 * x])
        {
            left = kth(2 * x, k, lx, m);
        }
        else
        {
            right = kth(2 * x + 1, k - tree[2 * x], m + 1, rx);
        }

        return max(left, right);
    }
    long long kth(int k)
    {
        return kth(1, k, 0, n - 1);
    }
};

void solve()
{
    ll n, k;
    cin >> n >> k;
    vll a(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    segtree seg = segtree(n);
    seg.build(a);
    while (k--)
    {
        ll q;
        cin >> q;
        if (q == 1)
        {

            ll i;
            cin >> i;
            seg.set(i);
        }
        else
        {
            ll k;
            cin >> k;
            cout << seg.kth(k) << endl;
        }
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
