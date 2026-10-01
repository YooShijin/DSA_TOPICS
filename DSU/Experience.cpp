#include <bits/stdc++.h>
using namespace std;

class DSU
{
    vector<int> parent;
    vector<int> size;
    vector<long long> add;
    vector<long long> delta;

public:
    DSU(int n)
    {
        parent.resize(n + 1);
        size.assign(n + 1, 1);
        add.assign(n + 1, 0);
        delta.assign(n + 1, 0);

        for (int i = 1; i <= n; i++)
            parent[i] = i;
    }

    int get(int x)
    {
        if (parent[x] == x)
            return x;

        int p = parent[x];
        parent[x] = get(p);
        delta[x] += delta[p];

        return parent[x];
    }

    void join(int a, int b)
    {
        a = get(a);
        b = get(b);

        if (a == b)
            return;

        if (size[a] < size[b])
            swap(a, b);

        parent[b] = a;
        delta[b] = add[b] - add[a];
        size[a] += size[b];
    }

    void addValue(int x, long long v)
    {
        int root = get(x);
        add[root] += v;
    }

    long long getValue(int x)
    {
        int root = get(x);
        return add[root] + delta[x];
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    DSU dsu(n);

    while (q--)
    {
        string op;
        cin >> op;

        if (op == "join")
        {
            int x, y;
            cin >> x >> y;
            dsu.join(x, y);
        }
        else if (op == "add")
        {
            int x;
            long long v;
            cin >> x >> v;
            dsu.addValue(x, v);
        }
        else
        {
            int x;
            cin >> x;
            cout << dsu.getValue(x) << '\n';
        }
    }
}