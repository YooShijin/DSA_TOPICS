#include <bits/stdc++.h>
using namespace std;

#define ll long long

int tim = 1;

struct Item
{
    int index;
    int mini;
};

vector<vector<int>> adj;

class segtree
{
    vector<Item> seg;
    int n;

public:
    segtree(vector<int> &nums)
    {
        // Index 0 is unused, so the actual number of elements is nums.size() - 1.
        n = nums.size() - 1;
        seg.assign(4 * n + 2, {-1, INT_MAX});

        build(nums);
    }

    void build(vector<int> &nums)
    {
        // The Euler tour and its depth array use 1-based indexing.
        build(1, 1, n, nums);
    }

    Item build(int node, int lx, int ly, vector<int> &nums)
    {
        if (lx == ly)
        {
            // Store the index and depth at this Euler tour position.
            return seg[node] = {lx, nums[lx]};
        }

        int mid = (lx + ly) / 2;

        Item left = build(2 * node, lx, mid, nums);
        Item right = build(2 * node + 1, mid + 1, ly, nums);

        // Keep the Euler tour position having the minimum depth.
        if (left.mini <= right.mini)
        {
            return seg[node] = left;
        }
        else
        {
            return seg[node] = right;
        }
    }

    Item query(int l, int r)
    {
        // Ensure the query interval is in increasing order.
        if (l > r)
        {
            swap(l, r);
        }

        return query(1, l, r, 1, n);
    }

    Item query(int node, int l, int r, int lx, int ly)
    {
        // The current segment lies completely inside the query interval.
        if (l <= lx && ly <= r)
        {
            return seg[node];
        }

        // The current segment does not overlap the query interval.
        if (l > ly || r < lx)
        {
            return {-1, INT_MAX};
        }

        int mid = (lx + ly) / 2;

        Item left = query(2 * node, l, r, lx, mid);
        Item right = query(2 * node + 1, l, r, mid + 1, ly);

        // Return the position with the minimum depth.
        if (left.mini <= right.mini)
        {
            return left;
        }
        else
        {
            return right;
        }
    }
};

// Construct the full Euler tour recursively.
// x is the current node, p is its parent, and d is its depth.
void dfs(int x, int p, int d, vector<int> &flat, vector<int> &flathi)
{
    // Record the current node when entering it.
    flat[tim] = x;

    // Store its depth at the same Euler tour position.
    flathi[tim] = d;

    // Advance to the next unused Euler tour position.
    tim++;

    for (auto &u : adj[x])
    {
        // Since the tree is undirected, do not traverse back to the parent.
        if (u == p)
        {
            continue;
        }

        // Visit the child. Its depth is one greater than its parent's.
        dfs(u, x, d + 1, flat, flathi);

        // DFS has returned from the child, so record the parent again.
        flat[tim] = x;
        flathi[tim] = d;
        tim++;
    }
}

void solve()
{
    ll n, q;
    cin >> n >> q;

    // Nodes are numbered from 1 to n.
    adj.assign(n + 1, {});

    int root = 1;

    // Read the undirected tree edges.
    for (int i = 1; i < n; i++)
    {
        ll u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Reset the timer before constructing the Euler tour.
    tim = 1;

    // A tree with n nodes has 2*n - 1 entries in its full Euler tour.
    // Index 0 is unused because this implementation uses 1-based indexing.
    vector<int> flat(2 * n, 0);
    vector<int> flathi(2 * n, 0);

    // Construct the Euler tour and record the depth of every occurrence.
    dfs(root, 0, 0, flat, flathi);

    // Store the first occurrence of every node in the Euler tour.
    map<int, int> mp;

    for (int i = 1; i < tim; i++)
    {
        if (mp.count(flat[i]))
        {
            continue;
        }

        mp[flat[i]] = i;
    }

    // Build the segment tree over the Euler tour's depth array.
    segtree seg(flathi);

    while (q--)
    {
        ll a, b;
        cin >> a >> b;

        // Take the first occurrence of each queried node.
        int l = mp[a];
        int r = mp[b];

        // The LCA is the node with minimum depth between these positions.
        Item res = seg.query(l, r);

        // res.index is an Euler tour position, not a node number.
        cout << flat[res.index] << '\n';
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}