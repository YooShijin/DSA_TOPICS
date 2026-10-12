#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int id;

    Edge(int to, int id) : to(to), id(id) {}
};

class Graph {
public:
    int N, M;
    vector<vector<Edge>> adj;

    Graph(int n) {
        N = n;
        M = 0;
        adj.resize(N);
    }

    void add(int u, int v) {
        adj[u].push_back(Edge(v, M));
        adj[v].push_back(Edge(u, M));
        M++;
    }
};

class TwoEdgeFinder {
public:
    Graph &g;

    int cnt;
    vector<int> pre, low;
    vector<int> stk;
    vector<int> bridges;
    vector<int> compOf;
    vector<vector<int>> comps;

    TwoEdgeFinder(Graph &graph) : g(graph) {
        int N = g.N;

        cnt = 0;
        pre.assign(N, -1);
        low.assign(N, 0);
        compOf.assign(N, -1);

        for (int i = 0; i < N; i++) {
            if (pre[i] == -1) {
                dfs(i, i, g.M);
                makeComp(i);
            }
        }
    }

    void makeComp(int v) {
        comps.emplace_back();
        int x;
        do {
            x = stk.back();
            stk.pop_back();
            compOf[x] = (int)comps.size() - 1;
            comps.back().push_back(x);
        } while (x != v);
    }

    int dfs(int i, int p, int id) {
        if (pre[i] != -1) {
            low[p] = min(low[p], pre[i]);
            return low[p];
        }

        pre[i] = cnt++;
        low[i] = pre[i];
        stk.push_back(i);

        for (Edge e : g.adj[i]) {
            if (e.id == id)
                continue;

            if (dfs(e.to, i, e.id) < 0) {
                low[i] = min(low[i], low[e.to]);

                if (low[e.to] == pre[e.to]) {
                    bridges.push_back(e.id);
                    makeComp(e.to);
                }
            }
        }

        return -1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    Graph g(N);

    for (int k = 0; k < M; k++) {
        int u, v;
        cin >> u >> v;
        g.add(u - 1, v - 1);
    }

    TwoEdgeFinder solver(g);

    cout << solver.comps.size() << '\n';
    for (auto comp : solver.comps) {
        sort(comp.begin(), comp.end());
        cout << comp.size();
        for (int v : comp) cout << ' ' << v + 1;
        cout << '\n';
    }

    return 0;
}
