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
    vector<int> eu, ev;

    Graph(int n) {
        N = n;
        M = 0;
        adj.resize(N);
    }

    void add(int u, int v) {
        adj[u].push_back(Edge(v, M));
        adj[v].push_back(Edge(u, M));
        eu.push_back(u);
        ev.push_back(v);
        M++;
    }
};

class BlockFinder {
public:
    Graph &g;

    int cnt;
    vector<int> pre, low;
    vector<int> stk;
    vector<bool> used;
    vector<bool> art;
    vector<int> bridges;
    vector<vector<int>> comps;
    vector<int> lonely;

    BlockFinder(Graph &graph) : g(graph) {
        int N = g.N;

        cnt = 0;
        pre.assign(N, -1);
        low.assign(N, 0);
        art.assign(N, false);
        used.assign(g.M + 1, false);

        for (int i = 0; i < N; i++) {
            if (pre[i] == -1) {
                used[g.M] = false;
                dfs(i, i, g.M);

                if (stk.size() > 1) {
                    makeComp(g.M);
                } else {
                    lonely.push_back(i);
                }
                stk.clear();
            }
        }
    }

    vector<int>& makeComp(int id) {
        comps.emplace_back();
        while (stk.back() != id) {
            comps.back().push_back(stk.back());
            stk.pop_back();
        }
        return comps.back();
    }

    int dfs(int i, int p, int id) {
        if (!used[id]) {
            used[id] = true;
            stk.push_back(id);
        }

        if (pre[i] != -1) {
            low[p] = min(low[p], pre[i]);
            return low[p];
        }

        pre[i] = cnt++;
        low[i] = pre[i];

        bool hasFwd = false;

        for (Edge e : g.adj[i]) {
            if (e.id == id)
                continue;

            if (dfs(e.to, i, e.id) < 0) {
                low[i] = min(low[i], low[e.to]);

                if (low[e.to] == pre[e.to]) {
                    bridges.push_back(e.id);
                }

                if (i != p ? low[e.to] >= pre[i] : hasFwd) {
                    art[i] = true;
                    makeComp(e.id).push_back(e.id);
                    stk.pop_back();
                }

                hasFwd = true;
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

    BlockFinder solver(g);

    vector<vector<int>> blocks;

    for (auto &comp : solver.comps) {
        vector<int> verts;
        for (int id : comp) {
            verts.push_back(g.eu[id]);
            verts.push_back(g.ev[id]);
        }
        sort(verts.begin(), verts.end());
        verts.erase(unique(verts.begin(), verts.end()), verts.end());
        blocks.push_back(verts);
    }

    for (int v : solver.lonely) {
        blocks.push_back({v});
    }

    cout << blocks.size() << '\n';
    for (auto &b : blocks) {
        cout << b.size();
        for (int v : b) cout << ' ' << v + 1;
        cout << '\n';
    }

    return 0;
}
