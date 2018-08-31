#include <bits/stdc++.h>

using namespace std;

const int maxn = 1010;
const int maxm = 101010;

int w[maxn], c[maxn];
int d[maxm];

int main()
{
	int n, m;
	cin >> n >> m;

	for (int i = 1; i <= n; i++)
		cin >> w[i] >> c[i];

	memset(d, -1, sizeof(d));
	d[0] = 0;

	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			if (w[j] <= i and d[i-w[j]] >= 0)
				d[i] = max(d[i], d[i-w[j]] + c[j]);

	int ans = 0;
	for (int i = 0; i <= m; i++)
		ans = max(ans, d[i]);

	cout << ans << "\n";
}