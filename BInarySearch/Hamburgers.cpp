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

vll req(3, 0);
vll av(3, 0);
vll p(3, 0);
ll ru;
bool isp(ll m)
{
    ll mon = ru;
    for (int i = 0; i < 3; i++)
    {
        ll rem = max(0LL, req[i] * m - av[i]);
        if (rem * p[i] <= mon)
        {
            mon = mon - rem * p[i];
        }
        else
        {
            return false;
        }
    }

    return true;
}

void solve()
{
    string s;
    cin >> s;
    for (auto i : s)
    {
        if (i == 'B')
        {
            req[0]++;
        }
        else if (i == 'S')
        {
            req[1]++;
        }
        else
        {
            req[2]++;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        cin >> av[i];
    }
    for (int i = 0; i < 3; i++)
    {
        cin >> p[i];
    }
    cin >> ru;
    ll l = 0;
    ll r = 1e14;
    while (r > l + 1)
    {
        ll m = (l + r) / 2;
        if (isp(m))
        {
            l = m;
        }
        else
        {
            r = m;
        }
    }

    cout << l << endl;
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