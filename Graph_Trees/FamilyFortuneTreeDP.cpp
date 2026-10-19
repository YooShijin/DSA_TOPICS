// Asmit Kumar 15 oct 2026
// Problem: pick exactly K nodes from a rooted tree to maximize their value sum,
//          with the rule that you cannot pick two nodes where one is an ancestor
//          of the other.
//
// This file: the NAIVE tree DP. Every node allocates a full (K + 1) sized array,
//            so the time is O(n * K) for the merges plus O(n * K) just for the
//            allocation and scanning at every node. In practice people call this
//            the "O(n * K * K) looking" version, though the inner work is already
//            bounded by O(n * K) because of the maxK2 cutoff.

#include <bits/stdc++.h>
using namespace std;
#define ll long long

// NEG marks an impossible state: "this many nodes cannot be picked here".
// We never add two NEG values together, so plain LLONG_MIN is fine here.
const ll NEG = LLONG_MIN;

int K;                   // how many nodes we must pick in total
vector<ll> nodes;        // nodes[i] = value of node i
vector<vector<int>> adj; // adjacency list (undirected edges)

// go(i, par) returns an array dp of length K + 1 where:
//   dp[k] = best sum when picking exactly k nodes inside i's subtree
//           (respecting the no ancestor/descendant rule),
//           or NEG if picking k nodes here is impossible.
vector<ll> go(int i, int par)
{
    // Base notebook for this subtree:
    // picking 0 nodes gives sum 0, everything else is impossible for now.
    vector<ll> dp(K + 1, NEG);
    dp[0] = 0;

    // Fold each child's subtree into dp, one child at a time.
    for (int j : adj[i])
    {
        if (j == par)
            continue; // skip the edge back to the parent

        // dp2[k] = best sum picking k nodes inside child j's subtree.
        vector<ll> dp2 = go(j, i);

        // maxK2 = the largest count the child can actually provide.
        // Every count from 0 up to maxK2 is valid (you can always drop a node),
        // so we stop the inner loop there instead of scanning all the way to K.
        int maxK2 = K;
        while (dp2[maxK2] == NEG)
            maxK2 -= 1;

        // Knapsack style merge of (children merged so far) with (this child).
        //
        //   new_dp[a + b] = max(new_dp[a + b], dp[a] + dp2[b])
        //
        // a = nodes taken from the children already merged (indexes dp)
        // b = nodes taken from this new child            (indexes dp2)
        //
        // Why "a" goes DOWNWARD (from K to 0):
        //   dp is updated in place. If a went upward, a write to dp[a + b] made
        //   while handling a small "a" would be read again at a larger "a", which
        //   would count this same child twice. Going downward, every dp[a] we read
        //   still holds only the OLD children. This is the exact reason 0/1 knapsack
        //   loops backward.
        for (int a = K; a >= 0; a -= 1)
        {
            if (dp[a] == NEG)
                continue; // can't pick "a" nodes from earlier children, skip
            for (int b = 0; b <= maxK2 && a + b <= K; b++)
            {
                // b = 0 just keeps dp[a] unchanged (take nothing from this child),
                // which is how "skip a whole child" stays possible.
                dp[a + b] = max(dp[a + b], dp2[b] + dp[a]);
            }
        }
    }

    // Now consider picking node i itself.
    // If we pick i, none of its descendants may be picked, so picking i is only
    // ever a set of exactly 1 node. That is why this touches dp[1] only, and it
    // must happen AFTER all children are merged (never inside the child loop, or i
    // would get combined with its own descendants).
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

    // Root the tree at node 1. par = 0 means "no real parent" for the root.
    vector<ll> dp = go(1, 0);

    // dp[K] at the root is the answer. NEG means K nodes could not be picked at all
    // (for example K is larger than the number of leaves).
    cout << (dp[K] == NEG ? -1 : dp[K]) << '\n';
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