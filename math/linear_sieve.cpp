#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010101;

int lp[maxn];

vector<int> sieve(int n)
{
	vector<int> pr;
	for (int i = 2; i <= n; i++) {
		if (lp[i] == 0) {
			lp[i] = i;
			pr.push_back(i);
		}

		for (int p : pr) {
			if (p > lp[i] or p*i > n) break;
			lp[p*i] = p;
		}
	}
	return pr;
}

int main()
{
	int n;
	cin >> n;

	auto ans = sieve(n);

	for (int p : ans)
		cout << p << " ";
	cout << "\n";
	// cout << ans.size() << "\n";
}