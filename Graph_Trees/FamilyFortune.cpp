// Asmit Kumar, 15 Oct 2026
// Select exactly K nodes to maximize their total reward.
// Constraint: No two selected nodes can have an ancestor-descendant relationship.

#include <bits/stdc++.h>
using namespace std;

#define ll long long

/*
    TECHNIQUE:
    TREE PREORDER FLATTENING + DP

    PROBLEM:
    We have a tree. Each node has a reward.
    We must select exactly K nodes to maximize the sum of their rewards.

    CONSTRAINT:
    We cannot select two nodes if one is an ancestor of the other.

    MAIN IDEA:
    1. Flatten the tree using preorder DFS.
    2. For each preorder position, calculate where its subtree ends.
    3. Use DP to decide whether to select or skip each node.

    The important observation is:

    If we select a node, we must skip all its descendants.

    In preorder, every subtree occupies a contiguous interval.
    Therefore, after selecting a node at preorder position i,
    we can jump directly to the first position after its subtree.

    This lets us solve the problem using DP on a linear array.

    Complexity:
    DFS preprocessing: O(N)
    DP:                O(N * K)
    Extra space:       O(N)
*/

ll tim = 0;

/*
    PREORDER DFS

    invp[p] = actual node ID at preorder position p.

    jump[p] = first preorder position AFTER the subtree
              of the node at preorder position p.

    We use zero-based preorder positions:
        0, 1, 2, ..., N-1

    The timer starts at 0 and increments whenever we enter a node.

    Example tree:

             1
            / \
           2   3
          / \
         4   5

    Preorder traversal:
        1, 2, 4, 5, 3

    Therefore:
        invp[0] = 1
        invp[1] = 2
        invp[2] = 4
        invp[3] = 5
        invp[4] = 3

    Now consider node 2.

    Its subtree contains:
        2, 4, 5

    These nodes occupy preorder positions:
        1, 2, 3

    The first position after its subtree is 4.

    Therefore:
        jump[1] = 4

    This is an EXCLUSIVE boundary.

    The subtree of the node at position p occupies:
        [p, jump[p])

    WHY IS THIS USEFUL?

    If we select node 2 at position 1, we must not select
    nodes 4 or 5 because they are descendants of node 2.

    Instead of processing positions 2 and 3, we jump directly
    to position 4.

    This is how we enforce the ancestor-descendant constraint.
*/

void dfs(int i, vector<vector<int>> &adj,
         vector<int> &invp, vector<int> &jump, int par)
{
    // Current preorder position of node i.
    int pre = tim++;

    // Store the actual node ID at this preorder position.
    invp[pre] = i;

    for (auto &child : adj[i])
    {
        // Avoid traversing back to the parent.
        if (child == par)
        {
            continue;
        }

        // Process the child's subtree.
        dfs(child, adj, invp, jump, i);
    }

    /*
        All descendants of node i have now been processed.

        tim is the first preorder position after its subtree.

        Therefore:
            jump[pre] = tim

        For a leaf, jump[pre] = pre + 1.
        For a node with descendants, jump[pre] skips
        the entire subtree.
    */

    jump[pre] = tim;
}

void solve()
{
    ll n, K;
    cin >> n >> K;

    /*
        nodes[u] = reward/value of node u.

        Use long long because the sum of K node values
        may exceed the int range.
    */

    vector<ll> nodes(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        cin >> nodes[i];
    }

    /*
        Read the tree.

        The tree is undirected, so store both directions.
        We root it at node 1 during DFS.
    */

    vector<vector<int>> adj(n + 1);

    for (int i = 1; i <= n - 1; i++)
    {
        ll u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    /*
        PREPROCESSING

        invp[p] = node at preorder position p.
        jump[p] = first position after that node's subtree.

        There are N preorder positions: 0 through N-1.
    */

    vector<int> invp(n);
    vector<int> jump(n);

    // Reset the timer before processing this test case.
    tim = 0;

    dfs(1, adj, invp, jump, -1);

    /*
        DP OVER PREORDER POSITIONS

        We need to select exactly K nodes.

        NEG represents an unreachable DP state.

        Use a sufficiently small long long value so adding
        it to a reward does not overflow.
    */

    const ll NEG = LLONG_MIN / 4;

    /*
        curr[i] = maximum reward achievable by selecting
                  exactly k nodes, with the next preorder
                  position to process being i.

        The value k is represented by the outer loop.

        Initially, we have selected zero nodes.

        Before processing any nodes:
            curr[0] = 0

        All other states are unreachable.

        After each outer iteration, curr represents one
        additional selected node.

        Thus:
            Initially: 0 selected nodes
            After 1 iteration: exactly 1 selected node
            After 2 iterations: exactly 2 selected nodes
            ...
            After K iterations: exactly K selected nodes
    */

    vector<ll> curr(n + 1, NEG);

    curr[0] = 0;

    /*
        OUTER LOOP: NUMBER OF SELECTED NODES

        Each iteration increases the number of selected nodes
        by exactly one.

        We run exactly K iterations because the problem
        requires exactly K selected nodes.
    */

    for (int k = 0; k < K; k++)
    {
        /*
            next[j] = maximum reward achievable by selecting
                      exactly k + 1 nodes, with the next
                      preorder position being j.

            We build the next DP layer from curr.

            Initially, every state is unreachable.
        */

        vector<ll> next(n + 1, NEG);

        /*
            PROCESS PREORDER POSITIONS FROM LEFT TO RIGHT

            At position i, we have two choices:

            CHOICE 1: SKIP THE CURRENT NODE
            CHOICE 2: SELECT THE CURRENT NODE

            Skipping does not increase the number of selected
            nodes, so we update curr.

            Selecting increases the number of selected nodes
            by one, so we update next.
        */

        for (int i = 0; i < n; i++)
        {
            /*
                CHOICE 1: SKIP THE CURRENT NODE

                Do not select the node at preorder position i.

                Move to the next preorder position i + 1.

                The number of selected nodes stays the same,
                so this transition remains in the curr layer.

                curr[i + 1] = max(
                    curr[i + 1],
                    curr[i]
                );

                WHY IS THIS DONE IN PLACE?

                We process positions from left to right.

                When we reach position i + 1, it already includes
                the best value propagated from position i.

                This lets us continue skipping nodes in the
                current DP layer without creating another array.
            */

            curr[i + 1] = max(curr[i + 1], curr[i]);

            /*
                If curr[i] is unreachable, we cannot select
                a node from this state.

                Check before adding a reward to avoid doing
                arithmetic on the NEG sentinel.
            */

            if (curr[i] == NEG)
            {
                continue;
            }

            /*
                CHOICE 2: SELECT THE CURRENT NODE

                The actual node at preorder position i is:
                    invp[i]

                Its reward is:
                    nodes[invp[i]]

                If we select it, the new total reward is:
                    curr[i] + nodes[invp[i]]

                But we cannot select its descendants.

                Because preorder places the whole subtree
                in a contiguous interval, we jump to:
                    jump[i]

                Therefore, the transition is:

                    next[jump[i]] = max(
                        next[jump[i]],
                        curr[i] + nodes[invp[i]]
                    )

                WHY DO WE UPDATE next INSTEAD OF curr?

                curr represents solutions with exactly k
                selected nodes.

                Selecting the current node increases that
                number to k + 1.

                Therefore, the result belongs in the next layer.

                WHY DO WE JUMP?

                jump[i] is the first position after the
                current node's entire subtree.

                Skipping to jump[i] prevents us from selecting
                any descendant of the selected node.

                It also ensures we never move backward in
                preorder, so we cannot later select an ancestor
                of a node we've already selected.
            */

            next[jump[i]] = max(
                next[jump[i]],
                curr[i] + nodes[invp[i]]);
        }

        /*
            MOVE TO THE NEXT DP LAYER.

            We now have the best values for exactly k + 1
            selected nodes.

            On the next iteration, curr represents this layer.
        */

        curr = next;
    }

    /*
        FINAL ANSWER

        After K iterations, curr contains states for exactly
        K selected nodes.

        Some states may be unreachable.

        Take the maximum over all positions.

        If every state is NEG, selecting exactly K nodes
        under the ancestor-descendant restriction is impossible.

        In that case, the original code outputs -1.
    */

    ll ans = *max_element(curr.begin(), curr.end());

    cout << (ans == NEG ? -1 : ans) << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}

/*
    ============================================
    REVISION SUMMARY
    ============================================

    1. TREE FLATTENING

       invp[p] = actual node at preorder position p.

       jump[p] = first position after the subtree of that node.

       Subtree interval:
           [p, jump[p])

       Both arrays use zero-based preorder positions.


    2. WHY JUMP IS IMPORTANT

       If we select a node, we cannot select its descendants.

       All descendants are contiguous in preorder.

       Therefore, selecting position p moves us directly to:
           jump[p]

       This automatically skips the entire subtree.


    3. DP STATE

       curr[i] = maximum reward achievable with exactly k
                 selected nodes, where i is the next preorder
                 position to process.

       Initially:
           curr[0] = 0

       All other states are NEG.


    4. SKIP TRANSITION

       Skip the current node without selecting it.

           curr[i + 1] = max(curr[i + 1], curr[i])

       The number of selected nodes does not change.

       This transition stays in the current DP layer.


    5. SELECT TRANSITION

       Select the node at preorder position i.

           next[jump[i]] = max(
               next[jump[i]],
               curr[i] + nodes[invp[i]]
           )

       The number of selected nodes increases by one.

       We jump over the selected node's subtree to ensure
       that none of its descendants can also be selected.


    6. WHY EXACTLY K?

       The outer loop runs K times.

       Each iteration performs one selection transition,
       moving from a solution with k selected nodes to one
       with k + 1 selected nodes.

       Skipping nodes does not increase the selection count.

       Therefore, after K iterations, the reachable states
       represent solutions with exactly K selected nodes.


    7. COMPLEXITY

       DFS preprocessing: O(N)
       DP:                O(N * K)
       Extra space:       O(N)

       The DP uses two arrays of size N + 1.


    8. WHEN IS THIS TECHNIQUE USEFUL?

       Use preorder flattening + jump + DP when:

       - You must select some nodes from a tree.
       - Selecting a node excludes its descendants.
       - You need to maximize or minimize some score.
       - You must select exactly K nodes or process a limited
         number of selections.

       Similar reasoning can apply to independent-set-style
       tree problems, although many variants are better solved
       using ordinary tree DP instead.
*/