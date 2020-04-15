struct DirectedDfs {
    vector<int> num, low, current, S;
    int counter;
    vector< vector<int> > scc;

    DirectedDfs() : num(V, -1), low(V, 0), current(V, 0), counter(0) {
        REP(i,V) if (num[i] == -1) dfs(i);
    }

    void dfs(int u) {
        low[u] = num[u] = counter++;
        S.push_back(u);
        current[u] = 1;
        for (auto v : G[u]) {
            if (num[v] == -1) dfs(v);
            if (current[v]) low[u] = min(low[u], low[v]);
        }
        if (low[u] == num[u]) {
            scc.push_back(vector<int>());
            while (1) {
                int v = S.back(); S.pop_back(); current[v] = 0;
                scc.back().push_back(v);
                if (u == v) break;
            }
        }
    }
};