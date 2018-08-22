#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

vector<int> v[maxn];
int vis[maxn];

// if general graph
int dfs(int x)
{
	vis[x] = 1;
	// body
	for (int u : v[x])
		if (!vis[u]) dfs(u);
	// after
}

// if tree
int dfs(int x, int p)
{
	// body
	for (int u : v[x]) {
		if (u == p) continue;
		dfs(u, x);
	}
	// after
}