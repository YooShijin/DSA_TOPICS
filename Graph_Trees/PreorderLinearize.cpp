#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll tim = 1;
void dfs(int i, vector<vector<int>> &adj, vector<int> &tin, vector<int> &tout, int par)
{
    tin[i] = tim++;
    for (auto &child : adj[i])
    {
        if (child == par)
        {
            continue;
        }
        dfs(child, adj, tin, tout, i);
    }
    tout[i] = tim;
}
class segtree
{
    vector<int> seg;
    int n;

public:
    segtree(vector<int> &arr)
    {
        this->n = arr.size() - 1;
        seg.assign(4 * n + 1, 0);
        build(1, 1, n, arr);
    }
    void build(int tid, int lx, int ly, vector<int> &arr)
    {
        if (lx == ly)
        {
            seg[tid] = arr[lx];
            return;
        }
        int mid = (lx + ly) / 2;
        build(2 * tid, lx, mid, arr);
        build(2 * tid + 1, mid + 1, ly, arr);
        seg[tid] = seg[2 * tid] + seg[2 * tid + 1];
    }
    void update(int ind, int val)
    {
        update(1, ind, val, 1, n);
    }
    void update(int tid, int ind, int val, int lx, int ly)
    {
        if (lx == ly)
        {
            seg[tid] = val;
            return;
        }

        int mid = (lx + ly) / 2;

        if (ind <= mid)
        {
            update(2 * tid, ind, val, lx, mid);
        }
        else
        {
            update(2 * tid + 1, ind, val, mid + 1, ly);
        }

        seg[tid] = seg[2 * tid] + seg[2 * tid + 1];
    }
    int query(int l, int r)
    {
        return query(1, 1, n, l, r);
    }
    int query(int tid, int lx, int ly, int l, int r)
    {
        if (l <= lx && r >= ly)
        {
            return seg[tid];
        }
        if (r < lx || l > ly)
        {
            return 0;
        }
        {

            int mid = (lx + ly) / 2;
            int left = query(2 * tid, lx, mid, l, r);
            int right = query(2 * tid + 1, mid + 1, ly, l, r);
            return left + right;
        }
    }
};
void solve()
{
    ll n, q;
    cin >> n >> q;
    vector nodes(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        cin >> nodes[i];
    }
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= n - 1; i++)
    {
        ll u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> tin(n + 1, 0);
    vector<int> tout(n + 1, 0);

    dfs(1, adj, tin, tout, -1);
    vector<int> flat(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        flat[tin[i]] = nodes[i];
    }
    segtree segtr(flat);

    while (q--)
    {
        ll type;
        cin >> type;
        if (type == 1)
        {
            int node, val;
            cin >> node >> val;
            nodes[node] = val;
            segtr.update(tin[node], val);
        }
        else if (type == 2)
        {
            int u;
            cin >> u;
            cout << segtr.query(tin[u], tout[u] - 1) << endl;
        }
        else
        {
            int u, v;
            cin >> u >> v;
            if (tin[u] <= tin[v] && tout[v] <= tout[u])
            {
                cout << "YES";
            }
            else
            {
                cout << "NO";
            }
            cout << endl;
        }
    }
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}

/*
subtreeSum(u) = query(tin[u], tout[u])

subtreeSize(u) = (tout[u] - tin[u] + 1) / 2

u is an ancestor of v if:
tin[u] <= tin[v] && tout[v] <= tout[u]
*/