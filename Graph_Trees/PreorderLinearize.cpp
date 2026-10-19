#include <bits/stdc++.h>
using namespace std;

#define ll long long

/*
    TECHNIQUE: TREE EULER TOUR + SEGMENT TREE

    We support three operations on a rooted tree:

    1. Update the value of a node.
    2. Find the sum of values in a node's subtree.
    3. Check whether one node is an ancestor of another.

    MAIN IDEA:
    Flatten the tree into an array using DFS preorder.

    The important property is:
    ALL NODES IN A SUBTREE OCCUPY A CONTIGUOUS RANGE
    IN THE PREORDER ARRAY.

    This allows us to convert subtree queries into
    ordinary range queries on an array.

    We use:
    - tin[u]: preorder position of node u.
    - tout[u]: exclusive endpoint of u's subtree.
    - flat[]: node values arranged in preorder.
    - Segment tree: point updates and range sum queries.

    TIMESTAMP CONVENTION:
    tin[u] is assigned when entering u.
    tout[u] is assigned after processing all descendants.

    The timer starts at 1 and increases only when entering
    a node.

    Therefore, the subtree of u occupies:
        [tin[u], tout[u] - 1]

    Subtree size:
        tout[u] - tin[u]

    Ancestor condition:
        tin[u] <= tin[v] && tin[v] < tout[u]

    Note: These are preorder-flattening timestamps.
    They are NOT the entry/exit event timestamps used
    by the 2N-event Euler tour.
*/

ll tim = 1;

/*
    DFS PREORDER FLATTENING

    tin[u] = timer when we enter node u.
    tout[u] = timer after all descendants of u are processed.

    par prevents DFS from going back to its parent.

    Example tree:

            1
           / \
          2   3
         / \
        4   5

    DFS preorder:
        1, 2, 4, 5, 3

    Assigned positions:
        tin[1] = 1
        tin[2] = 2
        tin[4] = 3
        tin[5] = 4
        tin[3] = 5

    Subtree of node 2 occupies positions [2, 4].

    After processing node 2, timer = 5.
    Therefore:
        tout[2] = 5

    Its subtree interval is:
        [tin[2], tout[2] - 1] = [2, 4]

    Why does this work?
    DFS finishes the entire subtree of a node before
    visiting nodes outside that subtree.
    Hence, every subtree becomes a contiguous array range.
*/

void dfs(int i, vector<vector<int>> &adj,
         vector<int> &tin, vector<int> &tout, int par)
{
    // Assign the preorder position when entering node i.
    tin[i] = tim++;

    for (auto &child : adj[i])
    {
        // Ignore the edge leading back to the parent.
        if (child == par)
        {
            continue;
        }

        // Completely process the child's subtree first.
        dfs(child, adj, tin, tout, i);
    }

    /*
        All descendants of i have now been processed.

        tim is the first preorder position AFTER the subtree.

        Therefore, tout[i] is an EXCLUSIVE boundary.

        Subtree interval:
            [tin[i], tout[i] - 1]

        Subtree size:
            tout[i] - tin[i]
    */
    tout[i] = tim;
}

/*
    SEGMENT TREE FOR RANGE SUMS

    We build a segment tree over the flattened array.

    Supported operations:
        update(index, value): Set one array element.
        query(l, r): Sum array elements in [l, r].

    Both operations take O(log N) time.
    Building the tree takes O(N) time.

    IMPORTANT:
    The segment tree uses 1-based array indices.
    Therefore, flat[] has size N + 1, and index 0 is unused.
*/

class segtree
{
    vector<int> seg;
    int n;

public:
    segtree(vector<int> &arr)
    {
        // arr[0] is unused, so the actual size is arr.size() - 1.
        this->n = arr.size() - 1;

        // Allocate sufficient space for the segment tree.
        seg.assign(4 * n + 1, 0);

        // Build the tree over the interval [1, n].
        build(1, 1, n, arr);
    }

    /*
        BUILD THE SEGMENT TREE

        tid = current segment tree node index.
        [lx, ly] = array interval represented by this node.

        If lx == ly, this is a leaf representing one array element.

        Otherwise:
        1. Build the left child's interval.
        2. Build the right child's interval.
        3. Store the sum of both children.

        Each segment tree node stores the sum of its interval.
    */

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

    /*
        POINT UPDATE

        Set the value at array position ind to val.

        We descend to the leaf representing ind.
        After updating the leaf, we recalculate the sums
        of all its ancestors in the segment tree.

        Time complexity: O(log N).
    */

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

        // Recalculate the sum after updating the relevant child.
        seg[tid] = seg[2 * tid] + seg[2 * tid + 1];
    }

    /*
        RANGE SUM QUERY

        Return the sum of array elements in [l, r].

        For each segment tree node, there are three cases:

        1. Completely inside [l, r]:
           Return the stored sum directly.

        2. Completely outside [l, r]:
           Return 0 because this segment contributes nothing.

        3. Partially overlapping [l, r]:
           Query both children and add their answers.

        Time complexity: O(log N) for a standard range-sum query.
    */

    int query(int l, int r)
    {
        return query(1, 1, n, l, r);
    }

    int query(int tid, int lx, int ly, int l, int r)
    {
        // Current segment [lx, ly] is completely inside [l, r].
        if (l <= lx && ly <= r)
        {
            return seg[tid];
        }

        // Current segment is completely outside [l, r].
        if (r < lx || l > ly)
        {
            return 0;
        }

        // Partial overlap: combine the answers from both children.
        int mid = (lx + ly) / 2;

        int left = query(2 * tid, lx, mid, l, r);
        int right = query(2 * tid + 1, mid + 1, ly, l, r);

        return left + right;
    }
};

void solve()
{
    ll n, q;
    cin >> n >> q;

    /*
        nodes[u] stores the current value of node u.

        Node values are kept separately because we need to
        remember each node's current value after updates.
    */

    vector nodes(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        cin >> nodes[i];
    }

    /*
        Read the tree.

        Each edge is undirected, so add both directions.
        The tree is rooted at node 1 for our DFS.
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

        tin[u] and tout[u] identify the subtree interval
        of each node in preorder.

        Initially:
            tim = 1

        After DFS:
            tin[u] = preorder position of u
            tout[u] = exclusive endpoint of u's subtree

        This code assumes the tree is rooted at node 1.
    */

    vector<int> tin(n + 1, 0);
    vector<int> tout(n + 1, 0);

    dfs(1, adj, tin, tout, -1);

    /*
        FLATTEN THE NODE VALUES

        flat[tin[u]] = nodes[u]

        Instead of storing values in node-number order,
        we store them in DFS preorder order.

        Example:

            Original tree:
                    1(5)
                   /   \
                 2(7)  3(2)
                 / \
               4(4) 5(8)

            Preorder:
                1, 2, 4, 5, 3

            Flattened values:
                5, 7, 4, 8, 2

        Now the subtree of node 2 is a contiguous range:
            [tin[2], tout[2] - 1]

        Therefore, a subtree sum becomes a range sum.
    */

    vector<int> flat(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        flat[tin[i]] = nodes[i];
    }

    // Build a segment tree over the flattened values.
    segtree segtr(flat);

    /*
        QUERY TYPES

        Type 1: 1 u val
            Update the value of node u to val.

        Type 2: 2 u
            Find the sum of values in the subtree of u.

        Type 3: 3 u v
            Check whether u is an ancestor of v.

        The exact input format depends on the original problem.
    */

    while (q--)
    {
        ll type;
        cin >> type;

        if (type == 1)
        {
            int node, val;
            cin >> node >> val;

            // Update the original node value.
            nodes[node] = val;

            /*
                Node node appears at position tin[node]
                in the flattened array.

                Update that position in the segment tree.
            */
            segtr.update(tin[node], val);
        }
        else if (type == 2)
        {
            int u;
            cin >> u;

            /*
                The subtree of u occupies:
                    [tin[u], tout[u] - 1]

                Query the segment tree for this range.

                This returns the sum of all node values in
                the subtree rooted at u, including u itself.
            */

            cout << segtr.query(tin[u], tout[u] - 1) << '\n';
        }
        else
        {
            int u, v;
            cin >> u >> v;

            /*
                ANCESTOR CHECK

                Using our preorder-flattening timestamps:

                    u is an ancestor of v iff
                    tin[u] <= tin[v] < tout[u]

                Why?

                The preorder interval of u contains exactly
                the nodes in u's subtree.

                If v's preorder position falls inside that
                interval, v belongs to u's subtree.

                This definition considers a node to be its
                own ancestor. Therefore, u == v returns YES.
            */

            if (tin[u] <= tin[v] && tin[v] < tout[u])
            {
                cout << "YES\n";
            }
            else
            {
                cout << "NO\n";
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}

/*
    REVISION SUMMARY
    ----------------

    1. DFS PREORDER FLATTENING

       tin[u] = preorder index of u
       tout[u] = exclusive endpoint of u's subtree

       Subtree interval:
           [tin[u], tout[u] - 1]

       Subtree size:
           tout[u] - tin[u]

    2. SUBTREE SUM

       Store:
           flat[tin[u]] = value[u]

       Then:
           subtreeSum(u) =
               segmentTree.query(tin[u], tout[u] - 1)

    3. NODE VALUE UPDATE

       Set:
           value[u] = newValue

       Update:
           segmentTree.update(tin[u], newValue)

    4. ANCESTOR CHECK

       u is an ancestor of v iff:
           tin[u] <= tin[v] && tin[v] < tout[u]

       This includes the case u == v.

    5. COMPLEXITY

       DFS preprocessing: O(N)
       Flattening:        O(N)
       Segment tree build: O(N)
       Type 1 update:      O(log N)
       Type 2 subtree sum: O(log N)
       Type 3 ancestor:    O(1)

       Total preprocessing: O(N)
       Each query: O(log N) worst case

    6. IMPORTANT DISTINCTION

       This code uses PREORDER FLATTENING, where each node
       appears once in flat[].

       It does not construct the full Euler tour of length
       2N - 1 used for LCA with RMQ.

       It also does not use the 2N-entry ENTER/EXIT event
       array.

       These representations are related, but their
       timestamp conventions and use cases differ.

    7. IMPLEMENTATION NOTES

       - tim is global and starts at 1.
       - If solve() is called multiple times, reset tim = 1
         before running DFS for each test case.
       - Recursive DFS may overflow the call stack on a very
         deep tree with around 200,000 nodes. Consider
         iterative DFS if the constraints require it.
       - Use long long for segment tree sums if node values
         or the total sum can exceed the int range.
*/