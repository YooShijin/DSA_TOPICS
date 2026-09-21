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

ll n, d;
vector<double> a;
ll ansl, ansr;
bool isp(double m)
{
    vector<double> pre(n + 1, 0.0);
    vector<double> pmin(n + 1, 0.0);
    vector<ll> pos(n + 1, 0);
    for (int i = 1; i < n + 1; i++)
    {
        pre[i] = pre[i - 1] + (a[i] - m);
        if (pre[i] < pmin[i - 1])
        {
            pmin[i] = pre[i];
            pos[i] = i;
        }
        else
        {
            pmin[i] = pmin[i - 1];
            pos[i] = pos[i - 1];
        }
    }
    for (int i = d; i < n + 1; i++)
    {
        if (pre[i] >= pmin[i - d])
        {
            ansr = i;
            ansl = pos[i - d] + 1;
            return true;
        }
    }
    return false;
}

void solve()
{
    cin >> n >> d;
    a.assign(n + 1, 0.0);
    for (int i = 1; i < n + 1; i++)
    {
        cin >> a[i];
    }

    double l = -1;
    double r = 101;
    ansr = n + 1;
    for (int i = 0; i < 100; i++)
    {
        double m = (l + r) / 2.0;
        if (isp(m))
        {
            l = m;
        }
        else
        {
            r = m;
        }
    }

    cout << ansl << " " << ansr << endl;
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