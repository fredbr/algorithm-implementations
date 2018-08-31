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

	for (int i = 1; i <= n; i++)
		for (int j = m; j >= w[i]; j--)
			if (d[j-w[i]] >= 0)
				d[j] = max(d[j], d[j-w[i]]+c[i]);

	int ans = 0;
	for (int i = 0; i <= m; i++)
		ans = max(ans, d[i]);

	cout << ans << "\n";
}