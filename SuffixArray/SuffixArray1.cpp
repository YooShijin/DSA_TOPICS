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
    string s;
    cin >> s;
    s += '$';
    ll n = s.size();
    vector<ll> p(n), c(n);
    {
        // K =0
        vector<pair<char, ll>> a(n);
        FOR(i, 0, n)
        {
            a[i] = {s[i], i};
        }
        sort(a.begin(), a.end());
        FOR(i, 0, n)
        {
            p[i] = a[i].second;
        }
        c[p[p[0]]] = 0;
        FOR(i, 1, n)
        {
            if (a[i].first == a[i - 1].first)
            {
                c[p[i]] = c[p[i - 1]];
            }
            else
            {
                c[p[i]] = c[p[i - 1]] + 1;
            }
        }
    }
    ll k = 0;
    while ((1 << k) < n)
    {
        // (k+1)th iteration..

        vector<pair<pair<ll, ll>, ll>> a(n);
        FOR(i, 0, n)
        {
            a[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
        }
        sort(a.begin(), a.end());
        FOR(i, 0, n)
        {
            p[i] = a[i].second;
        }
        c[p[p[0]]] = 0;
        FOR(i, 1, n)
        {
            if (a[i].first == a[i - 1].first)
            {
                c[p[i]] = c[p[i - 1]];
            }
            else
            {
                c[p[i]] = c[p[i - 1]] + 1;
            }
        }
        k++;
    }
    FOR(i, 0, n)
    {
        cout << p[i] << " ";
    }
    return;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t = 1;
    cin >> t;
    while (t--)
    {
        solve();
        cout << endl;
    }
    return 0;
}