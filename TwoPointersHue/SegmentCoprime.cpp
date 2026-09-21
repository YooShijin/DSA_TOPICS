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

struct stack
{
    vll s, sgcd;
    void push(ll x)
    {

        if (empty())
        {
            sgcd.push_back(x);
        }
        else
        {
            sgcd.push_back(::gcd(sgcd.back(), x));
        }
        s.push_back(x);
    }
    ll pop()
    {
        ll temp = s.back();
        s.pop_back();
        sgcd.pop_back();
        return temp;
    }
    bool empty()
    {
        return s.empty();
    }
    ll gcd()
    {
        if (empty())
            return 0;

        return sgcd.back();
    }
};
ll n;
::stack s1, s2;
void add(ll x)
{
    s2.push(x);
}
void remove()
{
    if (s1.empty())
    {
        while (!s2.empty())
        {
            s1.push(s2.pop());
        }
    }

    s1.pop();
}

vll a(100005, 0);
bool good()
{
    ll gd = std::gcd(s1.gcd(), s2.gcd());
    return gd == 1;
}

void solve()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    ll ans = INT_MAX;
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        add(a[i]);
        while (j <= i && good())
        {
            ans = std::min(ans, i - j + 1LL);
            remove();
            j++;
        }
    }
    if (ans == INT_MAX)
    {
        cout << -1 << endl;
        return;
    }
    cout << ans << endl;
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