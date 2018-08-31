#include <bits/stdc++.h>

using namespace std;

const int maxn = 1010;

int n, m;

int a[maxn], b[maxn];
int dp[maxn][maxn];

int solve(int i, int j)
{
	if (i > n or j > m) return 0;
	if (dp[i][j] >= 0) return dp[i][j];

	if (a[i] == b[j]) return dp[i][j] = 1 + solve(i+1, j+1);

	return dp[i][j] = max(solve(i+1, j), solve(i, j+1));
}

int d[2][maxn];

int main()
{
	memset(dp, -1, sizeof(dp));

	cin >> n >> m;

	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= m; i++)
		cin >> b[i];

	int ans = solve(1, 1);
	cout << ans << "\n";

	int now = 0, old = 1;

	for (int i = n; i >= 1; --i) {
		swap(now, old);
		for (int j = m; j >= 1; --j) {
			if (a[i] == b[j]) d[now][j] = 1 + d[old][j+1];
			else d[now][j] = max(d[old][j],
				                 d[now][j+1]);
		}
	}

	cout << d[now][1] << "\n";
}