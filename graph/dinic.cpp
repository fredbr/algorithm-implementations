
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define mk make_pair

typedef long long ll;
typedef pair<int, int> pii;

const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 1e5 + 5;

template<typename T>
struct Dinic {
	static constexpr T flow_inf = 1e18;
	
	struct FlowEdge {
		int v, u;
		T cap, flow = 0;
		FlowEdge(int v, int u, T cap) : v(v), u(u), cap(cap) {}
	};

	vector<FlowEdge> edges;
	vector<vector<int>> adj;
	int n, m = 0;
	int s, t;
	vector<int> level, ptr;
	queue<int> q;

	Dinic(int n, int s, int t) : n(n), s(s), t(t) {
		adj.resize(n);
		level.resize(n);
		ptr.resize(n);
	}

	void add_edge(int v, int u, T cap) {
		edges.emplace_back(v, u, cap);
		edges.emplace_back(u, v, 0);
		adj[v].push_back(m);
		adj[u].push_back(m + 1);
		m += 2;
	}

	bool bfs() {
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (int id : adj[v]) {
				if (edges[id].cap - edges[id].flow <= 0)
					continue;
				if (level[edges[id].u] != -1)
					continue;
				level[edges[id].u] = level[v] + 1;
				q.push(edges[id].u);
			}
		}
		return level[t] != -1;
	}

	T dfs(int v, T pushed) {
		if (pushed == 0) return 0;

		if (v == t) return pushed;
		
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
			int id = adj[v][cid];
			int u = edges[id].u;

			if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow <= 0) continue;
			
            T tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
			
            if (tr == 0) continue;
			
            edges[id].flow += tr;
			edges[id ^ 1].flow -= tr;
			
            return tr;
		}
		return 0;
	}

	T flow() {
		T f = 0;
		while (true) {
			fill(level.begin(), level.end(), -1);
			level[s] = 0;
			q.push(s);
			if (!bfs())
				break;
			fill(ptr.begin(), ptr.end(), 0);
			while (T pushed = dfs(s, flow_inf)) {
				f += pushed;
			}
		}
		return f;
	}
};
