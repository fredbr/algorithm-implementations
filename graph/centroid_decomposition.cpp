#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> ii;

const int inf = 0x3f3f3f3f;
const int maxn = 200010;
const int maxk = 1000010;

int n, k;
vector<ii> v[maxn];

int sz[maxn];
int vis[maxn];

int f[maxk];
int num[maxk];

int tam(int x, int p)
{
	sz[x] = 1;

	for (ii uu : v[x]) {

		int u = uu.ff;

		if (vis[u] or u == p) continue;

		sz[x] += tam(u, x);
	}

	return sz[x];
}

int tot;
ii best;

void split(int x, int p)
{
	int heav = tot - sz[x];

	for (ii uu : v[x]) {

		int u = uu.ff;

		if (vis[u] or u == p) continue;

		split(u, x);

		heav = max(heav, sz[u]);
	}

	if (best.ss > heav) best = {x, heav};
}

int centroid(int x)
{
	tot = tam(x, x);
	best = {0, inf};
	split(x, x);
	return best.ff;
}

void add(int x, int p, int dist, int cnt)
{
	if (dist > k) return;

	if (num[dist] == 0) f[dist] = cnt;
	else f[dist] = min(f[dist], cnt);

	num[dist]++;

	for (ii uu : v[x]) {

		int u = uu.ff, w = uu.ss;

		if (u == p or vis[u]) continue;

		add(u, x, dist+w, cnt+1);
	}
}

void rem(int x, int p, int dist, int cnt)
{
	if (dist > k) return;

	num[dist]--;

	for (ii uu : v[x]) {

		int u = uu.ff, w = uu.ss;

		if (u == p or vis[u]) continue;

		rem(u, x, dist+w, cnt+1);
	}
}

int get(int x, int p, int dist, int cnt)
{
	if (dist > k) return inf;

	int ans = inf;
	if (num[k-dist] != 0) ans = min(ans, f[k-dist]+cnt);

	for (ii uu : v[x]) {

		int u = uu.ff, w = uu.ss;

		if (u == p or vis[u]) continue;

		ans = min(ans, get(u, x, dist+w, cnt+1));
	}

	return ans;
}

int solve(int x)
{
	int cent = centroid(x);
	vis[cent] = 1;

	int ans = inf;

	num[0] = 1;
	f[0] = 0;

	for (ii uu : v[cent]) {

		int u = uu.ff, w = uu.ss;

		if (vis[u]) continue;

		ans = min(ans, get(u, cent, w, 1));

		add(u, cent, w, 1);
	}

	rem(cent, cent, 0, 0);

	for (ii uu : v[cent]) {

		int u = uu.ff;

		if (vis[u]) continue;

		ans = min(ans, solve(u));
	}

	return ans;
}

int main()
{

}