#include <bits/stdc++.h>

using namespace std;

using ii = pair<int, int>;

const int inf = 0x3f3f3f3f;
const int maxn = 200010;

int n, k;
vector<int> v[maxn];

int sz[maxn];
int cvis[maxn];

int tam(int x, int p)
{
	sz[x] = 1;

	for (int u : v[x]) {
		if (cvis[u] or u == p) continue;

		sz[x] += tam(u, x);
	}

	return sz[x];
}

int tot;
ii best;

void split(int x, int p)
{
	int heav = tot - sz[x];

	for (int u : v[x]) {
		if (cvis[u] or u == p) continue;

		heav = max(heav, sz[u]);
		split(u, x);
	}

	if (best.second > heav) best = {x, heav};
}

int centroid(int x)
{
	tot = tam(x, x);
	best = {0, inf};
	split(x, x);
	return best.first;
}

void solve(int x)
{
	int cent = centroid(x);
	cvis[cent] = 1;

	for (int u : v[cent]) {
		if (cvis[u]) continue;
		solve(u);
	}
}

int main()
{

}