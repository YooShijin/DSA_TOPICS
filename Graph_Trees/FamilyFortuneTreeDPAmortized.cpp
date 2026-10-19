// Asmit Kumar 15 oct 2026
// Problem: pick exactly K nodes from a rooted tree to maximize their value sum,
//          with the rule that you cannot pick two nodes where one is an ancestor
//          of the other.
//
// This file: the AMORTIZED ("small to large" tree knapsack) version.
//
// Two upgrades over the naive version:
//   1) Each node's dp array is only as long as it needs to be, capped at K + 1.
//      A node whose subtree has S nodes can give at most min(S, K) picks, so its
//      array has length min(S, K) + 1 instead of always K + 1.
//   2) Recursion is replaced by an explicit stack order, so a very deep tree
//      (a long chain) does not overflow the call stack.
//
// Why the total is O(n * K):
//   One merge of two pieces of sizes s1, s2 costs min(s1,K) * min(s2,K).
//   Every PAIR of nodes (u, v) is multiplied together exactly once, at their
//   lowest common ancestor, and a piece's length is capped at K. Charging the
//   work to node pairs gives:
//     small + small (both < K): counts node pairs inside a group, total <= n*K
//     small + big            : charge K per small-side node, each node pays once
//     big + big              : at most n/K such merges, each K*K, total <= n*K
//   Summed up this is about 3*n*K = O(n*K).

#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll NEG = LLONG_MIN;

int K; // how many nodes we must pick in total

// mergeInto(dp, dp2): fold child array dp2 into the running array dp.
// After the call, dp[k] = best sum using k nodes drawn from everything merged
// so far PLUS this child. dp2 is consumed (its contents are no longer needed).
void mergeInto(vector<ll> &dp, vector<ll> &dp2)
{
    // Small to large: always merge the shorter array into the longer one.
    // The result is the same either way (merging is symmetric), but resizing the
    // already-bigger array in place does less work than growing the small one.
    if (dp2.size() > dp.size())
        swap(dp, dp2);

    // New length: at most (len(dp) + len(dp2) - 1) because the best we can hold is
    // (max picks from dp) + (max picks from dp2). Capped at K + 1 since we never
    // need more than K picks. This cap is what turns O(n^2) into O(n*K).
    int len = min((int)(dp.size() + dp2.size()) - 1, K + 1);
    dp.resize(len, NEG);

    // Standard knapsack combine:
    //   dp[a + b] = max(dp[a + b], dp[a] + dp2[b])
    // a indexes the running array (old children), b indexes this child.
    //
    // "a" goes DOWNWARD so each dp[a] we read still holds only the old children
    // (same reason as 0/1 knapsack, prevents using this child twice).
    for (int a = len - 1; a >= 0; a -= 1)
    {
        if (dp[a] == NEG)
            continue; // "a" picks impossible from earlier children, skip
        // b starts at 1, not 0: b = 0 would add dp2[0] = 0 and change nothing.
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

    // ==== Build a processing order WITHOUT recursion ====
    // Do an iterative DFS from the root (node 1). "order" ends up listing every
    // node BEFORE all of its descendants. par[v] records v's parent.
    vector<int> order, par(n + 1, 0);
    order.reserve(n);
    vector<int> st = {1};
    par[1] = -1; // root has no parent
    while (!st.empty())
    {
        int u = st.back();
        st.pop_back();
        order.push_back(u);
        for (int v : adj[u])
        {
            if (v == par[u])
                continue; // do not walk back to the parent
            par[v] = u;
            st.push_back(v);
        }
    }

    // ==== Process nodes in REVERSE order ====
    // Reverse of "order" means every child is finished before its parent, which is
    // exactly the order a recursive post-order DFS would compute results in.
    // dp[v] will hold v's finished array once we pass it.
    vector<vector<ll>> dp(n + 1);
    for (int idx = n - 1; idx >= 0; idx -= 1)
    {
        int i = order[idx];

        // Start this node's notebook at {0}: zero picks gives sum 0.
        // It will grow as children fold in.
        vector<ll> cur = {0};

        for (int j : adj[i])
        {
            if (j == par[i])
                continue;             // skip parent edge
            mergeInto(cur, dp[j]);    // fold child j into cur
            vector<ll>().swap(dp[j]); // free child j's memory now that it is used
        }

        // Add the option of picking node i itself (a set of exactly 1 node).
        // Must come AFTER merging children. A leaf's cur is just {0}, so make sure
        // index 1 exists before writing to it.
        if (K >= 1)
        {
            if (cur.size() < 2)
                cur.resize(2, NEG);
            cur[1] = max(cur[1], nodes[i]);
        }

        dp[i] = move(cur); // store for the parent to read later
    }

    // Answer is dp[root][K]. If the root's array is shorter than K + 1, then fewer
    // than K nodes can be picked in the whole tree, so the answer is -1.
    ll ans = (K < (int)dp[1].size()) ? dp[1][K] : NEG;
    cout << (ans == NEG ? -1 : ans) << '\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t; // number of test cases
    while (t > 0)
    {
        solve();
        t -= 1;
    }
    return 0;
}