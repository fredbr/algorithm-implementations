#include <bits/stdc++.h>

using namespace std;

const int maxn = 500000;
const int maxlog = 20;

int n;
int v[maxn];
int rmq[maxn][maxlog];

inline int msb(int x)
{
	return 31-__builtin_clz(x);
}

inline int gcd(int a, int b)
{
	while (b) {

		a %= b;
		swap(a, b);
	}
	return a;
}

void build()
{
	for (int i = 1; i <= n; i++) rmq[i][0] = v[i];

	for (int j = 1; 1<<(j) <= n; j++) {

		for (int i = 1; i+(1<<j)-1 <= n; i++) {

			rmq[i][j] = gcd(rmq[i][j-1], rmq[i+(1<<(j-1))][j-1]);
		}
	}
}

int query(int l, int r)
{
	int diff = r-l;

	if (diff == 0) return rmq[l][0];

	int bdiff = msb(diff);
	int mbdiff = (1<<bdiff);

	int ql = rmq[l][bdiff];
	int qr = rmq[r-mbdiff+1][bdiff];

	return gcd(ql, qr);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;

	for (int i = 1; i <= n; i++) cin >> v[i];

	build();

	int q;
	cin >> q;

	for (int i = 0; i < q; i++) {

		int a, b;

		cin >> a >> b;

		cout << query(a, b) << "\n";
	}

	cout << "\n";

	return 0;
}