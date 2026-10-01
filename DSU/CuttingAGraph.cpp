#include <bits/stdc++.h>
using namespace std;

class DSU
{
    vector<int> parent;
    vector<int> size;

public:
    DSU(int n)
    {
        parent.resize(n + 1);
        size.assign(n + 1, 1);

        for (int i = 1; i <= n; i++)
            parent[i] = i;
    }

    int get(int x)
    {
        if (parent[x] == x)
            return x;

        return parent[x] = get(parent[x]);
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
    }

    bool connected(int a, int b)
    {
        return get(a) == get(b);
    }
};

struct Query
{
    string type;
    int u, v;
};

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
    }

    vector<Query> queries(k);

    for (int i = 0; i < k; i++)
    {
        cin >> queries[i].type >> queries[i].u >> queries[i].v;
    }

    DSU dsu(n);
    vector<string> ans;

    for (int i = k - 1; i >= 0; i--)
    {
        if (queries[i].type == "cut")
        {
            dsu.unite(queries[i].u, queries[i].v);
        }
        else
        {
            if (dsu.connected(queries[i].u, queries[i].v))
                ans.push_back("YES");
            else
                ans.push_back("NO");
        }
    }

    reverse(ans.begin(), ans.end());

    for (auto &x : ans)
        cout << x << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}