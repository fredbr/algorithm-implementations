#include <bits/stdc++.h>

using namespace std;

const int maxn = 20;

int n, m;
vector<int> v[maxn];

int solve(int x, int mask, int cnt)
{
	if (x == n+1) return cnt;

	int num = 0;
	for (int u : v[x]) {
		if (mask&(1<<u))
			num |= (1<<u);
	}

	if (num == mask)
		return max(solve(x+1, mask, cnt),
			       solve(x+1, mask|(1<<x), cnt+1));

	return solve(x+1, mask, cnt);
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

	int ans = solve(1, 0, 0);

	cout << ans << "\n";
}