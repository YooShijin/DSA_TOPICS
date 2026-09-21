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
ll n;
ll m;
ll d;
vll ans;
vector<vector<pair<ll, ll>>> adj;
bool isp(ll node, ll m, vll &temp)
{
    vll dis(n + 1, INT_MAX);
    dis[1] = 0;
    vll par(n + 1, -1);
    queue<ll> q;
    q.push(node);
    while (!q.empty())
    {
        auto u = q.front();
        q.pop();
        for (auto &ele : adj[u])
        {
            auto [v, c] = ele;
            if (c <= m && v != par[u] && dis[v] > dis[u] + 1)
            {
                dis[v] = dis[u] + 1;
                par[v] = u;
                q.push(v);
            }
        }
    }
    if (dis[n] <= d)
    {
        ans = par;
    }

    return dis[n] <= d;
}

void solve()
{
    cin >> n >> m >> d;
    adj.resize(n + 1);
    for (int i = 0; i < m; i++)
    {
        ll u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back({v, c});
    }
    ll l = -1;
    ll r = 1e9 + 5;

    while (r > l + 1)
    {
        ll m = (l + r) / 2;
        vll temp;
        if (isp(1, m, temp))
        {
            r = m;
        }
        else
        {
            l = m;
        }
    }
    if (r == (1e9 + 5))
    {
        cout << -1 << endl;
        return;
    }
    vll path;
    path.push_back(n);
    int i = n;
    while (ans[i] != -1)
    {
        path.push_back(ans[i]);
        i = ans[i];
    }
    cout << path.size() - 1 << endl;
    reverse(path.begin(), path.end());
    for (auto i : path)
    {
        cout << i << " ";
    }
    cout << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    while (t--)
        solve();
    return 0;
}