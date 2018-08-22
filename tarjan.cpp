#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> ii;

const int maxn = 100010;

vector<int> v[maxn];

int n, m;
int cnt = 0;
int num[maxn];
int low[maxn];
int pai[maxn];
int art[maxn];
vector<ii> bridge;
int root;
int rootc = 0;

void dfs(int x)
{
	low[x] = num[x] = ++cnt;

	for (int u : v[x]) {

		if (num[u] == 0) {

			pai[u] = x;

			if (x == root) rootc++;

			dfs(u);

			if (low[u] >= num[x]) art[x] = 1;

			if (low[u] > num[x]) bridge.push_back({x, u});

			low[x] = min(low[u], low[x]);
		
		} else if (u != pai[x]) low[x] = min(low[x], num[u]);
	}
}

int main()
{
	cin >> n >> m;

	for (int i = 0; i < m; i++) {

		int a, b;
		cin >> a >> b;

		v[a].push_back(b);
		v[b].push_back(a);
	}

	for (int i = 1; i <= n; i++) {

		if (num[i] == 0) {

			root = i;
			rootc= 0;

			dfs(i);

			art[root] = (rootc > 1);
		}
	}

	cout << "articulation \n";
	for (int i = 1; i <= n; i++) {

		if (art[i]) cout << i << "\n";
	}

	cout << "\n\n";
	cout << "bridge \n";

	for (ii i : bridge) cout << i.ff << " " << i.ss << "\n";
	cout << "\n";

	return 0;
}