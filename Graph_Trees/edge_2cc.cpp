// edge_2cc.cpp
//
// WHAT THIS FINDS: 2-edge-connected components, and the bridges of the graph.
//
// DEFINITIONS
//   Bridge: an edge whose removal increases the number of connected components.
//           In other words, an edge that is the ONLY link between two parts of
//           the graph. Cutting it splits the graph.
//   2-edge-connected component (2ECC): a maximal set of vertices such that you
//           can get between any two of them even after deleting ANY single edge.
//           Equivalently: remove every bridge, and each remaining connected
//           piece is one 2ECC.
//
//   Picture it as: the bridges are the "weak" single edges. Delete them all,
//   and the graph falls apart into blobs. Each blob is a 2ECC.
//
// HOW IT WORKS (Tarjan with pre / low times)
//   Run a DFS. Give each vertex a discovery time pre[v] (the order it was first
//   visited). low[v] = the smallest pre reachable from v's subtree using tree
//   edges plus at most going up ONE back edge.
//
//   Child edge (i -> e.to): after exploring the child, if
//         low[e.to] == pre[e.to]
//   then the child's whole subtree could NOT reach anything above the edge
//   (i, e.to). So that edge is the only way out: it is a BRIDGE. At that moment
//   everything still on the stack down to e.to forms one finished 2ECC.
//
//   The DFS stack "stk" holds vertices in visit order. When we close off a 2ECC
//   we pop vertices from the stack until we reach the component's entry vertex.

#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int to; // the other endpoint of this edge
    int id; // unique edge index, used to avoid walking back along the same edge
    Edge(int to, int id) : to(to), id(id) {}
};

class Graph
{
public:
    int N, M;                 // N vertices, M edges
    vector<vector<Edge>> adj; // adjacency list

    Graph(int n)
    {
        N = n;
        M = 0;
        adj.resize(N);
    }

    // Add an undirected edge u-v. Both directions share the same edge id.
    void add(int u, int v)
    {
        adj[u].push_back(Edge(v, M));
        adj[v].push_back(Edge(u, M));
        M++;
    }
};

class TwoEdgeFinder
{
public:
    Graph &g;

    int cnt;                   // next discovery time to hand out
    vector<int> pre, low;      // pre[v] = discovery time, low[v] = lowest reachable
    vector<int> stk;           // DFS stack of vertices not yet assigned a component
    vector<int> bridges;       // ids of bridge edges
    vector<int> compOf;        // compOf[v] = which 2ECC vertex v belongs to
    vector<vector<int>> comps; // the 2ECCs, each a list of vertices

    TwoEdgeFinder(Graph &graph) : g(graph)
    {
        int N = g.N;

        cnt = 0;
        pre.assign(N, -1); // -1 means "not visited yet"
        low.assign(N, 0);
        compOf.assign(N, -1);

        // Handle every connected part of the graph.
        for (int i = 0; i < N; i++)
        {
            if (pre[i] == -1)
            {
                // g.M is a fake edge id for the root, so the root has no "came from" edge.
                dfs(i, i, g.M);
                // When the DFS of this part ends, whatever is left on the stack is
                // the 2ECC containing the root i. Close it off.
                makeComp(i);
            }
        }
    }

    // Pop vertices off the stack down to and including v. They form one 2ECC.
    void makeComp(int v)
    {
        comps.emplace_back();
        int x;
        do
        {
            x = stk.back();
            stk.pop_back();
            compOf[x] = (int)comps.size() - 1;
            comps.back().push_back(x);
        } while (x != v);
    }

    // Returns -1 on a fresh visit (tree edge). Returns low[p] on a repeat visit
    // (back edge), which lets the caller update its own low via the return value.
    int dfs(int i, int p, int id)
    {
        // Already visited: this is a back edge from p to i. It lets p reach pre[i].
        if (pre[i] != -1)
        {
            low[p] = min(low[p], pre[i]);
            return low[p];
        }

        // First visit: stamp discovery time and push onto the component stack.
        pre[i] = cnt++;
        low[i] = pre[i];
        stk.push_back(i);

        for (Edge e : g.adj[i])
        {
            if (e.id == id)
                continue; // do not immediately walk back along the edge we came in on

            // dfs returns < 0 only for a fresh (tree) child. Back edges already
            // updated low[i] inside the "already visited" branch above.
            if (dfs(e.to, i, e.id) < 0)
            {
                low[i] = min(low[i], low[e.to]);

                // The child subtree could not escape above edge (i, e.to):
                // that edge is a bridge, and e.to's subtree is a finished 2ECC.
                if (low[e.to] == pre[e.to])
                {
                    bridges.push_back(e.id);
                    makeComp(e.to);
                }
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
        g.add(u - 1, v - 1); // convert 1-indexed input to 0-indexed internally
    }

    TwoEdgeFinder solver(g);

    // Print how many 2ECCs, then each one as "size v1 v2 ..." (back to 1-indexed).
    cout << solver.comps.size() << '\n';
    for (auto comp : solver.comps)
    {
        sort(comp.begin(), comp.end());
        cout << comp.size();
        for (int v : comp)
            cout << ' ' << v + 1;
        cout << '\n';
    }

    return 0;
}

// =====================================================================
// WORKED EXAMPLE
//
// Input (two triangles joined by a single edge 3-4):
//   6 7
//   1 2
//   2 3
//   3 1      <- triangle on {1,2,3}
//   3 4      <- the ONLY link between the two triangles = a BRIDGE
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
// The only bridge is edge 3-4. Delete it and the graph splits into:
//        {1,2,3}   and   {4,5,6}
// Each is still connected after removing any single one of its own edges,
// so each is a 2-edge-connected component.
//
// Program output:
//   2
//   3 4 5 6
//   3 1 2 3
//
// Reading it: "2" components. First line "3 4 5 6" = a component of size 3
// containing vertices 4,5,6. Second line "3 1 2 3" = size 3 with vertices 1,2,3.
// (The {4,5,6} blob is closed first because the bridge 3-4 is detected while
//  unwinding out of that deeper subtree.)
// =====================================================================