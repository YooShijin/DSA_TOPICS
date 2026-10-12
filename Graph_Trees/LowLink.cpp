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

        for (int i = 0; i < N; i++)
        {
            if (pre[i] == -1)
            {
                dfs(i, i, g.M);
            }
        }
    }

    int dfs(int i, int p, int id)
    {
        if (pre[i] != -1)
        {
            low[p] = min(low[p], pre[i]);
            return low[p];
        }

        pre[i] = cnt++;
        low[i] = pre[i];

        bool hasFwd = false;

        for (Edge e : g.adj[i])
        {
            if (e.id == id)
                continue;

            int result = dfs(e.to, i, e.id);

            if (result < 0)
            {
                low[i] = min(low[i], low[e.to]);

                if (low[e.to] == pre[e.to])
                {
                    bridges.push_back(e.id);
                }

                if (i != p ? low[e.to] >= pre[i] : hasFwd)
                {
                    art[i] = true;
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