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
ll n, p;
vll a(2002, 0);
ll sum = 0;
void add(ll x)
{
    sum += x;
}
void remove(ll x)
{
    sum = sum - x;
}

bool good()
{
    return sum >= p;
}
void solve()
{

    cin >> n >> p;
    ll tot = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        tot += a[i];
    }
    for (int i = 0; i < n; i++)
    {
        a[n + i] = a[i];
    }
    ll cycles = p / tot;
    ll rem = p % tot;

    if (rem == 0)
    {
        cout << 1 << " " << cycles * n << endl;
        return;
    }

    p = rem;
    ll ans = cycles * n;
    ll temp = n;
    ll start = 0;
    ll j = 0;
    for (int i = 0; i < 2 * n; i++)
    {
        add(a[i]);
        while (j < n && good())
        {
            if ((i - j + 1) < temp)
            {
                temp = i - j + 1;
                start = j;
            }

            remove(a[j]);
            j++;
        }
    }

    cout << start + 1 << " " << ans + temp << endl;
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