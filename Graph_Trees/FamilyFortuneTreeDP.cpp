// Asmit Kumar 15 oct 2026
// This is naive DP on tree so t.c. is O(n*k*k)
// Select exactly k nodes to get the max sum, can't select two nodes where one is ancestor of other
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll NEG = LLONG_MIN;

int K;
vector<ll> nodes;
vector<vector<int>> adj;

vector<ll> go(int i, int par)
{
    vector<ll> dp(K + 1, NEG);
    dp[0] = 0;

    for (int j : adj[i])
    {
        if (j == par)
            continue;
        vector<ll> dp2 = go(j, i);
        int maxK2 = K;
        while (dp2[maxK2] == NEG)
            maxK2--;

        for (int a = K; a >= 0; a--)
        {
            if (dp[a] == NEG)
                continue;
            for (int b = 0; b <= maxK2 && a + b <= K; b++)
            {
                dp[a + b] = max(dp[a + b], dp2[b] + dp[a]);
            }
        }
    }
    if (K >= 1)
        dp[1] = max(dp[1], nodes[i]);
    return dp;
}

void solve()
{
    int n;
    cin >> n >> K;
    nodes.assign(n + 1, 0);
    for (int i = 1; i <= n; i++)
        cin >> nodes[i];
    adj.assign(n + 1, {});
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<ll> dp = go(1, 0);
    cout << (dp[K] == NEG ? -1 : dp[K]) << '\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t > 0)
    {
        solve();
        t -= 1;
    }
    return 0;
}