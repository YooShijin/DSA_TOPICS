#include <bits/stdc++.h>
using namespace std;

class DSU
{
private:
    int n;
    vector<int> parent;
    vector<int> size;
    vector<int> maxi;
    vector<int> mini;

public:
    DSU(int sz)
    {
        n = sz;
        parent.assign(n + 1, 0);
        mini.assign(n + 1, 0);
        maxi.assign(n + 1, 0);
        size.assign(n + 1, 1);

        for (int i = 1; i <= n; i++)
        {
            parent[i] = i;
            mini[i] = i;
            maxi[i] = i;
        }
    }

    int get(int i)
    {
        if (parent[i] == i)
            return i;

        return parent[i] = get(parent[i]);
    }

    void unite(int a, int b)
    {
        a = get(a);
        b = get(b);

        if (a == b)
            return;

        if (size[a] < size[b])
            swap(a, b);

        parent[b] = a;
        size[a] += size[b];
        mini[a] = min(mini[a], mini[b]);
        maxi[a] = max(maxi[a], maxi[b]);
    }

    void info(int x)
    {
        int root = get(x);

        cout << mini[root] << ' '
             << maxi[root] << ' '
             << size[root] << '\n';
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;

    DSU dsu(n);

    while (q--)
    {
        string s;
        cin >> s;

        if (s[0] == 'u')
        {
            int a, b;
            cin >> a >> b;
            dsu.unite(a, b);
        }
        else
        {
            int a;
            cin >> a;
            dsu.info(a);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}