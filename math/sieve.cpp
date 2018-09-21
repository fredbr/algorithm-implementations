#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010101;

char s[maxn];
// bitset<maxn> s;

vector<int> sieve(int n)
{
	for (int i = 2; i*i <= n; i++)
		if (!s[i]) 
			for (int j = i*i; j <= n; j += i)
				s[j] = 1;

	vector<int> primes;
	for (int i = 2; i <= n; i++)
		if (!s[i]) primes.push_back(i);

	return primes;
}

int main()
{
	int n;
	cin >> n;

	auto ans = sieve(n);

	cout << ans.size() << "\n";
}