#include <bits/stdc++.h>
using namespace std;
#define ll long long
class DSU
{
private:
    int n;
    vector<int> parent;
    vector<int> size;

public:
    DSU(int sz)
    {
        n = sz;
        parent.assign(n + 1, 0);
        size.assign(n + 1, 1);
        init();
    }

    void init()
    {
        for (int i = 1; i <= n; i++)
        {
            parent[i] = i;
        }
    }
    int get(int i)
    {
        return parent[i] = (parent[i] == i) ? i : get(parent[i]);
    }
    void unite(int a, int b)
    {
        a = get(a);
        b = get(b);
        if(a == b){
            return;
        }
        if (size[a] < size[b])
        {
            swap(a,b);
        }
        parent[b] = a;
        size[a] += size[b];
    }
};
void solve()
{
    ll n, q;
    cin >> n;
    cin >> q;
    DSU dsu(n);
    while (q--)
    {
        ll a, b;
        string s;
        cin >> s;
        cin >> a >> b;
        if (s[0] == 'u')
        {
            dsu.unite(a, b);
        }
        else
        {
            if (dsu.get(a) == dsu.get(b))
            {
                cout << "YES" << "\n";
            }
            else
            {
                cout << "NO" << "\n";
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll t = 1;
    // cin>>t;
    while (t--)
    {
        solve();
    }
    return 0;
}