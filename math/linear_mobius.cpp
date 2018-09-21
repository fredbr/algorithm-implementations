#include <bits/stdc++.h>

using namespace std;

const int maxn = 10101010;

int mu[maxn], lp[maxn];

void sieve(int n)
{
	fill(mu, mu+maxn, -1);
	mu[1] = 1;

	vector<int> pr;
	for (int i = 2; i <= n; i++) {
		if (lp[i] == 0) {
			lp[i] = i;
			pr.push_back(i);
		}

		for (int p : pr) {
			if (p > lp[i] or p*i > n) break;
			if (i%p == 0)
				mu[i*p] = 0; 
			lp[p*i] = p;
			mu[p*i] *= mu[i];
		}
	}
}

int main()
{
	int n;
	cin >> n;

	sieve(n);

	for (int i = 1; i <= n; i++)
		cout << i << " : " << mu[i] << "\n";
}