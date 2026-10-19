#include <bits/stdc++.h>

using namespace std;
#define ll long long
int tim = 1;
class segtree
{
    vector<int> seg;
    int n;

public:
    segtree(vector<int> &nums)
    {
        n = nums.size();
        seg.assign(4 * n + 2, 0);

        build(nums);
    }
    void build(vector<int> &nums)
    {
        build(1, 1, n, nums);
    }
    int build(int node, int lx, int ly, vector<int> nums)
    {
        if (lx == ly)
        {
            return seg[node] = nums[lx];
        }
        int mid = (lx + ly) / 2;
        int left = build(2 * node, lx, mid, nums);
        int right = build(2 * node + 1, mid + 1, ly, nums);
        seg[node] = min(left, right);
    }
    int query(int l, int r)
    {
        return query(1, l, r, 1, n);
    }
    int query(int node, int l, int r, int lx, int ly)
    {
        if (l <= lx && ly <= r)
        {
            return seg[node];
        }
        if (l > ly || r < lx)
        {
            return INT_MAX;
        }
        int mid = (lx + ly) / 2;
        int left = query(2 * node, l, r, lx, mid);
        int right = query(2 * node + 1, l, r, mid + 1, ly);
        return min(left, right);
    }
};
void solve()
{
    ll n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n);
    ll root = 1;
    for (int i = 1; i < n; i++)
    {
        ll u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    while (q--)
    {
        ll a, b;
        cin >> a >> b;
    }
    return;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}