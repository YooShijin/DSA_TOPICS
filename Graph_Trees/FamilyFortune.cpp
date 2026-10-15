// Asmit Kumar 15 oct 2026
// Select exactly k nodes to get the max sum, can't select two nodes where one is ancestor of other
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll tim = 0;
void dfs(int i, vector<vector<int>> &adj, vector<int> &invp, vector<int> &jump, int par)
{
    int pre = tim++;
    invp[pre] = i;
    for (auto &child : adj[i])
    {
        if (child == par)
        {
            continue;
        }
        dfs(child, adj, invp, jump, i);
    }
    jump[pre] = tim;
}

void solve()
{
    ll n, K;
    cin >> n >> K;
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
    vector<int> invp(n);
    vector<int> jump(n);

    tim = 0;
    dfs(1, adj, invp, jump, -1);

    int ans = INT_MIN;
    vector<int> curr(n + 1, INT_MIN);
    curr[0] = 0;
    for (int k = 0; k < K; k++)
    {
        vector<int> next(n + 1, INT_MIN);
        for (int i = 0; i < n; i++)
        {

            curr[i + 1] = max(curr[i + 1], curr[i]);
            if (curr[i] == INT_MIN)
                continue;
            next[jump[i]] = max(
                next[jump[i]],
                curr[i] + nodes[invp[i]]);
        }
        curr = next;
    }
    ans = *max_element(curr.begin(), curr.end());
    cout << (ans == INT_MIN ? -1 : ans) << '\n';
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}
