// vertex_bcc.cpp
//
// WHAT THIS FINDS: biconnected components (also called "blocks"), plus it marks
//                  articulation points and bridges along the way.
//
// DEFINITIONS
//   Articulation point (cut vertex): a vertex whose removal increases the number
//           of connected components. Delete it and the graph falls apart.
//   Bridge: an edge whose removal disconnects the graph (same as in the 2ECC file).
//   Biconnected component / block: a maximal set of EDGES such that any two of
//           them lie on a common simple cycle. Intuition: a block has no
//           articulation point inside it. Every block is one of:
//              - a maximal 2-vertex-connected chunk (a cycle or a denser piece), or
//              - a single bridge edge (a block of exactly 2 vertices).
//           Blocks can SHARE a vertex, and that shared vertex is an articulation
//           point. This is the key difference from 2ECCs (which partition the
//           vertices): blocks partition the EDGES, and articulation points sit in
//           more than one block.
//
// HOW IT WORKS (Tarjan with pre / low, but the stack holds EDGE ids)
//   Same pre / low idea as the 2ECC version. The difference: here the stack holds
//   EDGE ids, because a block is a set of edges. When we find that a child cannot
//   reach strictly above the current vertex i, i is an articulation point and the
//   edges sitting on top of the stack down to the child's entry edge form a block.
//
//   The articulation test:
//     - For a NON-root vertex i: i is an articulation point if some child e.to has
//           low[e.to] >= pre[i]   (the child cannot get above i without using i).
//     - For the ROOT (i == p): it is an articulation point only if it has TWO or
//           more DFS children. That is what "hasFwd" tracks (we already saw one
//           forward/tree child before this one).

#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int to; // other endpoint
    int id; // unique edge index (blocks are collected as sets of these ids)
    Edge(int to, int id) : to(to), id(id) {}
};

class Graph
{
public:
    int N, M;
    vector<vector<Edge>> adj;
    vector<int> eu, ev; // eu[id], ev[id] = the two endpoints of edge id (for output)

    Graph(int n)
    {
        N = n;
        M = 0;
        adj.resize(N);
    }

    void add(int u, int v)
    {
        adj[u].push_back(Edge(v, M));
        adj[v].push_back(Edge(u, M));
        eu.push_back(u);
        ev.push_back(v);
        M++;
    }
};

class BlockFinder
{
public:
    Graph &g;

    int cnt;                   // next discovery time
    vector<int> pre, low;      // discovery time and low-link
    vector<int> stk;           // stack of EDGE ids not yet placed in a block
    vector<bool> used;         // used[id] = is this edge already pushed on the stack
    vector<bool> art;          // art[v] = is vertex v an articulation point
    vector<int> bridges;       // ids of bridge edges
    vector<vector<int>> comps; // blocks, each as a list of edge ids
    vector<int> lonely;        // isolated vertices (no edges), each its own block

    BlockFinder(Graph &graph) : g(graph)
    {
        int N = g.N;

        cnt = 0;
        pre.assign(N, -1);
        low.assign(N, 0);
        art.assign(N, false);
        used.assign(g.M + 1, false); // +1 for the fake root edge id g.M

        for (int i = 0; i < N; i++)
        {
            if (pre[i] == -1)
            {
                used[g.M] = false; // reset the fake edge for this new DFS tree
                dfs(i, i, g.M);

                // Any edges left on the stack after this tree form one last block.
                // If the stack has more than the fake root marker, build that block;
                // otherwise vertex i was isolated.
                if (stk.size() > 1)
                {
                    makeComp(g.M);
                }
                else
                {
                    lonely.push_back(i);
                }
                stk.clear();
            }
        }
    }

    // Pop edge ids down to (but NOT including) the marker id, forming one block.
    vector<int> &makeComp(int id)
    {
        comps.emplace_back();
        while (stk.back() != id)
        {
            comps.back().push_back(stk.back());
            stk.pop_back();
        }
        return comps.back();
    }

    int dfs(int i, int p, int id)
    {
        // Push the edge we are entering through (once), so blocks collect edges.
        if (!used[id])
        {
            used[id] = true;
            stk.push_back(id);
        }

        // Already visited vertex: back edge. Update the PARENT's low via pre[i].
        if (pre[i] != -1)
        {
            low[p] = min(low[p], pre[i]);
            return low[p];
        }

        pre[i] = cnt++;
        low[i] = pre[i];

        bool hasFwd = false; // have we already descended into one tree child?

        for (Edge e : g.adj[i])
        {
            if (e.id == id)
                continue; // skip the edge we came in on

            if (dfs(e.to, i, e.id) < 0)
            { // fresh tree child
                low[i] = min(low[i], low[e.to]);

                // Bridge test: child cannot reach even pre[e.to] from above.
                if (low[e.to] == pre[e.to])
                {
                    bridges.push_back(e.id);
                }

                // Articulation test:
                //   non-root i: child trapped at or below i  -> low[e.to] >= pre[i]
                //   root i (i == p): articulation iff it has a SECOND child -> hasFwd
                if (i != p ? low[e.to] >= pre[i] : hasFwd)
                {
                    art[i] = true;
                    // Close off the block: edges on top of the stack down to edge e.id,
                    // plus e.id itself, are one block. (e.id is re-added then the marker
                    // is popped, which is what the .push_back(e.id) + pop_back do.)
                    makeComp(e.id).push_back(e.id);
                    stk.pop_back();
                }

                hasFwd = true;
            }
        }

        return -1;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    Graph g(N);
    for (int k = 0; k < M; k++)
    {
        int u, v;
        cin >> u >> v;
        g.add(u - 1, v - 1);
    }

    BlockFinder solver(g);

    // Each block is a set of edge ids. Turn it into its set of distinct vertices
    // for printing.
    vector<vector<int>> blocks;
    for (auto &comp : solver.comps)
    {
        vector<int> verts;
        for (int id : comp)
        {
            verts.push_back(g.eu[id]);
            verts.push_back(g.ev[id]);
        }
        sort(verts.begin(), verts.end());
        verts.erase(unique(verts.begin(), verts.end()), verts.end());
        blocks.push_back(verts);
    }
    for (int v : solver.lonely)
    {
        blocks.push_back({v}); // isolated vertex = a block on its own
    }

    cout << blocks.size() << '\n';
    for (auto &b : blocks)
    {
        cout << b.size();
        for (int v : b)
            cout << ' ' << v + 1;
        cout << '\n';
    }

    return 0;
}

// =====================================================================
// WORKED EXAMPLE  (same graph as the 2ECC file, so you can compare)
//
// Input:
//   6 7
//   1 2
//   2 3
//   3 1      <- triangle on {1,2,3}
//   3 4      <- bridge
//   4 5
//   5 6
//   6 4      <- triangle on {4,5,6}
//
// Drawing:
//   left triangle edges:  1 to 2, 2 to 3, 3 to 1
//   right triangle edges: 4 to 5, 5 to 6, 6 to 4
//   single joining edge:  3 to 4   (this is the bridge)
//
//        1                 4
//       / \               / \
//      2   3 === 3-4 === 5   6
//
// Blocks (sets of edges, shown by their vertices):
//   Block A: triangle {1,2,3}
//   Block B: the single bridge edge {3,4}   <- a bridge is its own block
//   Block C: triangle {4,5,6}
//
// Vertices 3 and 4 are ARTICULATION POINTS: 3 is shared by blocks A and B,
// 4 is shared by blocks B and C. Notice 3 and 4 each appear in two blocks,
// which is exactly why blocks partition edges, not vertices.
//
// Program output:
//   3
//   3 4 5 6
//   2 3 4
//   3 1 2 3
//
// Reading it: "3" blocks.
//   "3 4 5 6" = block with 3 vertices {4,5,6}        (triangle C)
//   "2 3 4"   = block with 2 vertices {3,4}          (the bridge B)
//   "3 1 2 3" = block with 3 vertices {1,2,3}        (triangle A)
//
// COMPARE WITH edge_2cc.cpp ON THE SAME GRAPH:
//   2ECCs were {1,2,3} and {4,5,6} only (2 components, the bridge is not its own
//   piece there). Here we get 3 blocks because the bridge {3,4} is its own block
//   and the articulation points 3 and 4 are shared across blocks.
// =====================================================================