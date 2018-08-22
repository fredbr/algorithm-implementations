#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

const int maxn = 10101;

ii v[maxn];
int dist[maxn];

void sssp(int x)
{
	memset(dist, 0x3f, sizeof(dist));
	dist[x] = 0;

	priority_queue<ii, vector<ii>, greater<ii>> pq;
	pq.push({0, x});

	while (!pq.empty()) {
		int at, w;
		tie(w, at) = pq.top();
		pq.pop();

		if (w > dist[at]) continue;

		for (ii uu : v[at]) {
			int u, ww;
			tie(u, ww) = uu;

			if (dist[u] > w+ww) {
				dist[u] = w+ww;
				pq.push({dist[u], u});
			}
		}
	}
}