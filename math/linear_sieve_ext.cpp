#include <bits/stdc++.h>

using namespace std;

const int maxn = 10101010;

int cnt[maxn], lp[maxn];

void sieve(int n)
{
	vector<int> pr;
	for (int i = 2; i <= n; i++) {
		if (lp[i] == 0) {
			cnt[i] = 1;
			lp[i] = i;
			pr.push_back(i);
		}

		for (int p : pr) {
			if (p > lp[i] or p*i > n) break;

			lp[p*i] = p;
			
			if (i%p == 0) {
				cnt[i*p] = cnt[i]+1; 
			}
			else {			
				cnt[i*p] = 1;
			}
		}
	}
}

int main()
{
	int n;
	cin >> n;

	sieve(n);

	for (int i = 1; i <= n; i++)
		cout << i << " : " << lp[i]  << "^" << cnt[i] << "\n";
}