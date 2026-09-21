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
void solve()
{
    ll n, q;
    cin >> n >> q;
    vll v(n);
    FOR(i, 0, n)
    cin >> v[i];

    ll S = 300;
    vll sq;

    for (int i = 0; i < n; i += S)
    {
        ll t = v[i];
        for (int j = i + 1; j < min(i + S, n); j++)
            t = max(t, v[j]);
        sq.push_back(t);
    }

    ll fin = 0;

    while (q--)
    {
        ll l, r;
        cin >> l >> r;
        l--, r--;

        ll hue = l;
        l++;
        r--;
        ll ans = 0;

        while (l <= r)
        {
            if (l % S == 0 && l + S - 1 <= r)
            {
                ans = max(ans, sq[l / S]);
                l += S;
            }
            else
            {
                ans = max(ans, v[l]);
                l++;
            }
        }

        if (ans <= v[hue])
            fin++;
    }

    cout << fin << endl;
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