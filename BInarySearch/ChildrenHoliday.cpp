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

ll n, m;
vector<vector<ll>> v;
bool isp(ll tim)
{
    ll tot = 0;
    for (int i = 0; i < n; i++)
    {
        ll t = v[i][0];
        ll z = v[i][1];
        ll y = v[i][2];
        ll cycle = z * t + y;
        ll full = tim / cycle;
        ll ball = full * z;
        ll rem = tim % cycle;
        ball += min(z, rem / t);
        tot += ball;
    }

    return tot >= m;
}

void solve()
{
    cin >> m >> n;
    for (int i = 0; i < n; i++)
    {
        vll t(3, 0);
        cin >> t[0];
        cin >> t[1];
        cin >> t[2];
        v.push_back(t);
    }

    ll l = -1;
    ll r = 1e9;
    while (r > l + 1)
    {
        ll m = (l + r) >> 1;
        if (isp(m))
        {
            r = m;
        }
        else
        {
            l = m;
        }
    }
    cout << r << endl;
    ll tim = r;
    vll ans(n, 0);

    for (int i = 0; i < n; i++)
    {
        ll t = v[i][0];
        ll z = v[i][1];
        ll y = v[i][2];
        ll cycle = z * t + y;
        ll full = tim / cycle;
        ll ball = full * z;
        ll rem = tim % cycle;
        ball += min(z, rem / t);
        ans[i] = ball;
    }
    ll need = m;

    for (int i = 0; i < n; i++)
    {
        ans[i] = min(ans[i], need);
        need -= ans[i];
        cout << ans[i] << ' ';
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