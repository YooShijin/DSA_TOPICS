#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int to;
    int id;

    Edge(int to, int id) : to(to), id(id) {}
};

class Graph
{
public:
    int N, M;
    vector<vector<Edge>> adj;

    Graph(int n)
    {
        N = n;
        M = 0;
        adj.resize(N);
    }

    void add(int u, int v)
    {
        // Both directions share the same edge ID.
        // This lets DFS skip only the exact parent edge.
        adj[u].push_back(Edge(v, M));
        adj[v].push_back(Edge(u, M));
        M++;
    }
};

class CutFinder
{
public:
    Graph &g;

    int cnt;
    vector<int> pre, low;
    vector<int> bridges;
    vector<bool> art;

    CutFinder(Graph &graph) : g(graph)
    {
        int N = g.N;

        cnt = 0;
        pre.assign(N, -1);
        low.assign(N, 0);
        art.assign(N, false);

        // The graph might be disconnected, so start DFS
        // from every vertex that has not been visited.
        for (int i = 0; i < N; i++)
        {
            if (pre[i] == -1)
            {
                // g.M is not a real edge ID, so it acts as
                // a sentinel for the DFS root.
                dfs(i, i, g.M);
            }
        }
    }

    int dfs(int i, int p, int id)
    {
        // If i is already visited, we have found an edge
        // to a previously discovered vertex.
        //
        // Update the low-link value of the current vertex p
        // using the discovery time of i.
        //
        // In an undirected DFS, a visited neighbor reached
        // through a non-parent edge is an ancestor or a
        // descendant. Edges to descendants cannot improve
        // low[p], while edges to ancestors may improve it.
        if (pre[i] != -1)
        {
            low[p] = min(low[p], pre[i]);
            return low[p];
        }

        // pre[u] = DFS discovery time of u.
        pre[i] = cnt++;

        // Initially, the earliest reachable discovery time
        // is the vertex's own discovery time.
        low[i] = pre[i];

        // Used to identify whether the DFS root has
        // already discovered one DFS child.
        bool hasFwd = false;

        for (Edge e : g.adj[i])
        {
            // Skip the exact edge used to enter this vertex.
            // Edge IDs are important when parallel edges exist.
            if (e.id == id)
                continue;

            // If e.to is unvisited, DFS explores it and returns -1.
            // If it is already visited, the return value is
            // nonnegative and the back-edge case is handled inside dfs().
            int result = dfs(e.to, i, e.id);

            if (result < 0)
            {
                // e.to was newly explored, so it is a DFS child.
                //
                // After returning from the child, its low value
                // may tell us that the child's subtree can reach
                // an ancestor of i.
                low[i] = min(low[i], low[e.to]);

                // BRIDGE CONDITION:
                //
                // If low[child] == pre[child], the child's subtree
                // cannot reach any vertex discovered before child.
                // Therefore, the tree edge connecting i to child
                // is a bridge.
                //
                // This equality works because low[child] <= pre[child].
                if (low[e.to] == pre[e.to])
                {
                    bridges.push_back(e.id);
                }

                // ARTICULATION POINT CONDITION:
                //
                // For a non-root vertex i:
                // If low[child] >= pre[i], the child's subtree
                // cannot reach an ancestor of i without going
                // through i. Removing i disconnects that subtree.
                //
                // For a DFS root:
                // It is an articulation point only if it has
                // at least two DFS-tree children.
                if (i != p ? low[e.to] >= pre[i] : hasFwd)
                {
                    art[i] = true;
                }

                // Mark that at least one DFS child has been explored.
                // This makes the next child trigger the root condition.
                hasFwd = true;
            }
        }

        // Return -1 to signal that this vertex was newly explored.
        // The caller uses this convention to distinguish DFS children
        // from edges to already visited vertices.
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

    while (M--)
    {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        g.add(u, v);
    }

    CutFinder solver(g);

    cout << "Bridges:\n";

    // Edge IDs are assigned from 0, so these are zero-based IDs.
    for (int id : solver.bridges)
    {
        cout << id << '\n';
    }

    cout << "Articulation points:\n";

    for (int i = 0; i < N; i++)
    {
        if (solver.art[i])
        {
            cout << i + 1 << ' ';
        }
    }

    cout << '\n';

    return 0;
}