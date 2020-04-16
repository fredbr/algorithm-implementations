#include <bits/stdc++.h>
using namespace std;

int const maxn = 101010;

int n;
vector<int> v[maxn];

struct BiconnectedComponent {
    vector<int> low, num, s;
    vector<vector<int>> components;
    int counter;

    BiconnectedComponent() : num(n, -1), low(n, -1), counter(0) {
    for (int i = 0; i < n; i++)
        if (num[i] < 0)
            dfs(i, 1);
    }

    void dfs(int x, int isRoot, int p) {
        low[x] = num[x] = ++counter;
        if (v[x].empty()) {
            components.push_back(vector<int>(1, x));
            return;
        }
        s.push_back(x);

        for (int u : v[x]) {
            if (num[u] > -1) low[x] = min(low[x], num[u]);
            else {
                dfs(u, 0, x);
                low[x] = min(low[x], low[u]);

                if (isRoot || low[u] >= num[x]) {
                    components.push_back(vector<int>(1, x));
                    while (1) {
                        int k = s.back();
                        s.pop_back();
                        components.back().push_back(k);
                        if (k == u) break;
                    }
                }
            }
        }
    }
};
