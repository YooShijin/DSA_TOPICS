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
    vector<bitset<41>> tree;

    segtree(int sz)
    {
        n = sz;
        tree.resize(4 * n + 1);
    }
    bitset<41> merge(bitset<41> &a, bitset<41> &b)
    {
        return a | b;
    }

    void build(vector<ll> &a, int x, int lx, int rx)
    {
        if (lx == rx)
        {
            tree[x].reset();
            tree[x].set(a[lx]);
            return;
        }

        int m = (lx + rx) / 2;

        build(a, 2 * x, lx, m);
        build(a, 2 * x + 1, m + 1, rx);

        tree[x] = merge(tree[2 * x], tree[2 * x + 1]);
    }

    void build(vector<ll> &a)
    {
        build(a, 1, 0, n - 1);
    }

    void set(int idx, int x, int lx, int rx, ll val)
    {
        if (lx == rx)
        {
            tree[x].reset();
            tree[x].set(val);
            return;
        }

        int m = (lx + rx) / 2;

        if (idx <= m)
            set(idx, 2 * x, lx, m, val);
        else
            set(idx, 2 * x + 1, m + 1, rx, val);

        tree[x] = merge(tree[2 * x], tree[2 * x + 1]);
    }

    void set(int idx, ll val)
    {
        set(idx, 1, 0, n - 1, val);
    }

    bitset<41> query(int x, int lx, int rx, int l, int r)
    {
        if (r < lx || l > rx)
            return bitset<41>();

        if (l <= lx && rx <= r)
            return tree[x];

        int m = (lx + rx) / 2;

        return query(2 * x, lx, m, l, r) |
               query(2 * x + 1, m + 1, rx, l, r);
    }
    bitset<41> query(int l, int r)
    {
        return query(1, 0, n - 1, l, r);
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
        if (q == 2)
        {
            ll i, v;
            cin >> i >> v;
            i--;
            seg.set(i, v);
        }
        else
        {
            ll l, r;
            cin >> l >> r;
            l--;
            r--;
            ll temp = seg.query(l, r).count();
            cout << temp << endl;
        }
    }
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
