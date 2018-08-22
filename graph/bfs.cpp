#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

vector<int> v[maxn];
int vis[maxn];

void bfs(int x)
{
	queue<int> q;
	q.push(x);
	vis[x] = 1;

	while (!q.empty()) {
		int at = q.front();
		q.pop();

		// body 
		for (int u : v[at]) {
			if (!vis[u]) {
				vis[u] = 1;
				q.push(u);
			}
		}

		// after
	}
}

int main()
{

}