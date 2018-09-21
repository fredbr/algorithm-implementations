#include <bits/stdc++.h>

using namespace std;

const int maxn = 10101010;

int phi[maxn], lp[maxn];

void sieve(int n)
{
	iota(phi, phi+maxn, 0);
	vector<int> pr;
	for (int i = 2; i <= n; i++) {
		if (lp[i] == 0) {
			lp[i] = i;
			pr.push_back(i);
		}
		phi[i]--;

		for (int p : pr) {
			if (p > lp[i] or p*i > n) break;
			lp[p*i] = p;
			phi[p*i] -= phi[p*i]/p;
		}
	}
}

int main()
{
	int n;
	cin >> n;

	sieve(n);

	for (int i = 1; i <= n; i++)
		cout << i << " : " << phi[i] << "\n";
}