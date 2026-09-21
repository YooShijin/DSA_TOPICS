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

ll m;
struct Node
{
    ll a;
    ll b;
    ll c;
    ll d;
};

class segtree
{
public:
    int n;
    vector<Node> tree;

    segtree(int sz)
    {
        n = sz;
        tree.resize(4 * n + 1);
    }

    Node calc(Node A, Node B)
    {
        Node C;
        C.a = (A.a * B.a + A.b * B.c) % m;
        C.b = (A.a * B.b + A.b * B.d) % m;
        C.c = (A.c * B.a + A.d * B.c) % m;
        C.d = (A.c * B.b + A.d * B.d) % m;
        return C;
    }

    void build(vector<vector<ll>> &a, int x, int lx, int rx)
    {
        if (lx == rx)
        {
            tree[x] = {
                a[lx][0], // a
                a[lx][1], // b
                a[lx][2], // c
                a[lx][3]  // d
            };
            return;
        }

        int m = (lx + rx) / 2;

        build(a, 2 * x, lx, m);
        build(a, 2 * x + 1, m + 1, rx);

        tree[x] = calc(tree[2 * x], tree[2 * x + 1]);
    }

    void build(vector<vector<ll>> &a)
    {
        build(a, 1, 0, n - 1);
    }

    Node query(int x, int lx, int rx, int l, int r)
    {
        if (r < lx || l > rx)
        {
            return {
                1,
                0,
                0,
                1};
        }
        if (l <= lx && r >= rx)
        {
            return tree[x];
        }
        int m = (lx + rx) / 2;
        Node left = query(2 * x, lx, m, l, r);
        Node right = query(2 * x + 1, m + 1, rx, l, r);

        return calc(left, right);
    }
    Node query(int l, int r)
    {
        return query(1, 0, n - 1, l, r);
    }
};
void solve()
{
    ll n, k;
    cin >> m >> n >> k;
    vector<vector<ll>> vec(n);
    for (int i = 0; i < n; i++)
    {
        vll temp;
        ll a, b, c, d;

        cin >> a;
        cin >> b;
        cin >> c;
        cin >> d;
        temp.push_back(a);
        temp.push_back(b);
        temp.push_back(c);
        temp.push_back(d);
        vec[i] = temp;
    }
    segtree seg = segtree(n);
    seg.build(vec);
    while (k--)
    {

        ll l, r;
        cin >> l >> r;
        l--;
        r--;
        Node temp = seg.query(l, r);
        cout << temp.a << " " << temp.b << endl;
        cout << temp.c << " " << temp.d << endl;
        cout << endl;
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
