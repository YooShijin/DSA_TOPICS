// Asmit Kumar 15 oct 2026
// This is amortized DP on tree so t.c. is O(n*k)
// Here we are just merging the dp arrays where we only have the size of the array as the size of subarray at max
// Select exactly k nodes to get the max sum, can't select two nodes where one is ancestor of other
// Asmit Kumar 15 oct 2026
// Select exactly k nodes to get the max sum, can't select two nodes where one is ancestor of other

// Every merge is one of these:

// Case	Cost of one merge	Why the total is ≤ n·K
// small + small (both < K)	s1 × s2	Count pairs: s1 × s2 is the number of node pairs (u from one side, v from the other) meeting at this node. Each pair meets only once, at their lowest common ancestor. Inside a group of fewer than K nodes there are fewer than size × K such pairs. The groups don’t overlap, so the sum is ≤ n·K.
// small + big	s_small × K	Charge K to each node on the small side. A node can only be on the small side of such a merge once, because afterwards it’s inside a big piece forever. So the total is ≤ n·K.
// big + big	K × K	At most n / K such merges (Example 2), so the total is ≤ n·K.

// Adding them up gives about 3·n·K = O(n·K).

#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll NEG = LLONG_MIN;

int K;

void mergeInto(vector<ll> &dp, vector<ll> &dp2)
{
    if (dp2.size() > dp.size())
        swap(dp, dp2);

    int len = min((int)(dp.size() + dp2.size()) - 1, K + 1);
    dp.resize(len, NEG);

    for (int a = len - 1; a >= 0; a -= 1)
    {
        if (dp[a] == NEG)
            continue;
        for (int b = 1; b < (int)dp2.size() && a + b < len; b++)
        {
            dp[a + b] = max(dp[a + b], dp[a] + dp2[b]);
        }
    }
}

void solve()
{
    int n;
    cin >> n >> K;
    vector<ll> nodes(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> nodes[i];
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> order, par(n + 1, 0);
    order.reserve(n);
    vector<int> st = {1};
    par[1] = -1;
    while (!st.empty())
    {
        int u = st.back();
        st.pop_back();
        order.push_back(u);
        for (int v : adj[u])
        {
            if (v == par[u])
                continue;
            par[v] = u;
            st.push_back(v);
        }
    }

    vector<vector<ll>> dp(n + 1);
    for (int idx = n - 1; idx >= 0; idx -= 1)
    {
        int i = order[idx];
        vector<ll> cur = {0};

        for (int j : adj[i])
        {
            if (j == par[i])
                continue;
            mergeInto(cur, dp[j]);
            vector<ll>().swap(dp[j]);
        }

        if (K >= 1)
        {
            if (cur.size() < 2)
                cur.resize(2, NEG);
            cur[1] = max(cur[1], nodes[i]);
        }
        dp[i] = move(cur);
    }

    ll ans = (K < (int)dp[1].size()) ? dp[1][K] : NEG;
    cout << (ans == NEG ? -1 : ans) << '\n';
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