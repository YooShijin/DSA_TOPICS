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

// class segtree
// {
// public:
//     int n;
//     vector<ll> tree;
//     vector<ll> sums;
//     vector<ll> pref;
//     vector<ll> suff;

//     segtree(int sz)
//     {
//         n = sz;
//         tree.resize(4 * sz + 1, 0);
//         sums.resize(4 * sz + 1, 0);
//         pref.resize(4 * sz + 1, 0);
//         suff.resize(4 * sz + 1, 0);
//     }

//     void build(vector<ll> &a, int x, int lx, int rx)
//     {
//         if (lx == rx)
//         {
//             tree[x] = max(0LL, a[lx]);
//             sums[x] = a[lx];
//             pref[x] = max(0LL, a[lx]);
//             suff[x] = max(0LL, a[lx]);
//             return;
//         }

//         int m = (lx + rx) / 2;

//         build(a, 2 * x, lx, m);
//         build(a, 2 * x + 1, m + 1, rx);
//         sums[x] = sums[2 * x] + sums[2 * x + 1];
//         tree[x] = max(tree[2 * x], tree[2 * x + 1]);
//         tree[x] = max(tree[x], suff[2 * x] + pref[2 * x + 1]);

//         pref[x] = max(pref[2 * x], sums[2 * x] + pref[2 * x + 1]);
//         suff[x] = max(suff[2 * x + 1], sums[2 * x + 1] + suff[2 * x]);
//     }

//     void build(vector<ll> &a)
//     {
//         build(a, 1, 0, n - 1);
//     }
//     void set(int i, int x, int lx, int rx, long long val)
//     {
//         if (lx == rx)
//         {
//             tree[x] = max(0LL, val);
//             sums[x] = val;
//             pref[x] = max(0LL, val);
//             suff[x] = max(0LL, val);
//             return;
//         }

//         int m = (lx + rx) / 2;
//         if (i <= m)
//         {
//             set(i, 2 * x, lx, m, val);
//         }
//         else
//         {
//             set(i, 2 * x + 1, m + 1, rx, val);
//         }
//         sums[x] = sums[2 * x] + sums[2 * x + 1];
//         tree[x] = max(tree[2 * x], tree[2 * x + 1]);
//         tree[x] = max(tree[x], suff[2 * x] + pref[2 * x + 1]);

//         pref[x] = max(pref[2 * x], sums[2 * x] + pref[2 * x + 1]);
//         suff[x] = max(suff[2 * x + 1], sums[2 * x + 1] + suff[2 * x]);
//     }
//     void set(int i, long long val)
//     {
//         set(i, 1, 0, n - 1, val);
//     }
//     // long long sum(int x, int lx, int rx, int l, int r)
//     // {
//     //     if (r < lx || l > rx)
//     //     {
//     //         return 0;
//     //     }

//     //     if (l <= lx && rx <= r)
//     //     {
//     //         return tree[x];
//     //     }
//     //     int m = (lx + rx) / 2;
//     //     long long leftSum = sum(2 * x, lx, m, l, r);
//     //     long long rightSum = sum(2 * x + 1, m + 1, rx, l, r);

//     //     return leftSum + rightSum;
//     // }
//     // long long sum(int l, int r)
//     // {
//     //     return sum(1, 0, n - 1, l, r);
//     // }
// };
const ll NEG = LLONG_MIN / 4;
struct Node
{
    ll sum;
    ll pref;
    ll suff;
    ll ans;
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

    Node merge(Node left, Node right)
    {
        Node res;

        res.sum = left.sum + right.sum;
        res.pref = max(left.pref, left.sum + right.pref);
        res.suff = max(right.suff, right.sum + left.suff);
        res.ans = max({left.ans, right.ans, left.suff + right.pref});

        return res;
    }

    void build(vector<ll> &a, int x, int lx, int rx)
    {
        if (lx == rx)
        {
            tree[x] = {
                a[lx],           // sum
                max(0LL, a[lx]), // prefix
                max(0LL, a[lx]), // suffix
                max(0LL, a[lx])  // maximum subarray
            };
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
            tree[x] = {
                val,
                max(0LL, val),
                max(0LL, val),
                max(0LL, val)};
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

    ll answer()
    {
        return tree[1].ans;
    }
    Node query(int x, int lx, int rx, int l, int r)
    {
        if (r < lx || l > rx)
        {
            return {
                0,   // sum
                NEG, // pref
                NEG, // suff
                NEG  // ans
            };
        }
        if (l <= lx && r >= rx)
        {
            return tree[x];
        }
        int m = (lx + rx) / 2;
        Node left = query(2 * x, lx, m, l, r);
        Node right = query(2 * x + 1, m + 1, rx, l, r);

        return merge(left, right);
    }
    Node query(int l, int r)
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
    cout << seg.answer() << endl;
    while (k--)
    {
        ll q;
        cin >> q;
        if (q == 1)
        {
            ll i, v;
            cin >> i >> v;
            seg.set(i, v);
            cout << seg.answer() << endl;
        }
        else
        {
            ll l, r;
            cin >> l >> r;
            Node temp = seg.query(l, r);
            cout << temp.ans << endl;
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
