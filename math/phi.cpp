#include <bits/stdc++.h>

using namespace std;

const int maxn = 1010101;
int s[maxn];

void sieve_phi()
{
	for (int i = 1; i < maxn; i++)
		s[i] = i;

	for (int i = 2; i < maxn; i++)
		if (s[i] == i)
			for (int j = i; j < maxn; j += i)
				s[j] -= s[j]/i;
}

int phi(int x)
{
	int ans = x, k = x;
	for (int i = 2; i*i <= x and k > 1; i++) {
		if (k%i ==0) {	
			ans -= ans/i;
			while (k%i == 0)
				k /= i;
		}
	}

	if (k != 1)
		ans -= ans/k;

	return ans;
}

int main()
{	
	sieve_phi();
}