#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;
const int maxlog = 20;

vector<int> v[maxn];
int dep[maxn];
int anc[maxn][maxlog];

void dfs(int x, int p)
{
	for (int u : v[x]) {
		if (u == p) continue;

		anc[u][0] = x;

		for (int i = 1; i < maxlog; i++)
			anc[u][i] = anc[anc[u][i-1]][i-1];

		dep[u] = dep[x]+1;
		dfs(u, x);
	}
}

int lca(int x, int y)
{
	if (x == y) return x;

	if (dep[x] > dep[y]) swap(x, y);

	for (int i = maxlog-1; i >= 0 and dep[x] != dep[y]; i--)
		if (dep[y]-(1<<i) >= dep[x])
			y = anc[y][i];

	if (x == y) return x;

	for (int i = maxlog-1; i >= 0; i--)
		if (anc[x][i] != anc[y][i] and
			anc[x][i] != 0 and anc[y][i] != 0)
			x = anc[x][i], y = anc[y][i];

	if (x == y) return x;
	return anc[x][0];
}

int main()
{
	int n;
	cin >> n;

	for (int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;

		v[a].push_back(b);
		v[b].push_back(a);
	}

	dfs(1, 1);

	while (1) {

		int x, y;
		cin >> x >> y;

		if (x == 0) break;

		int ans = lca(x, y);
		cout << ans << "\n";
	}
}