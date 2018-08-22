#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll mod = 1e9 + 7;
const int maxn = 1e6 + 10;	

ll fac[maxn];
ll inv[maxn];
ll invfac[maxn];

void init()
{	
	fac[0] = 1ll;
	for (ll i = 1; i < maxn; i++)
		fac[i] = fac[i-1] * i % mod;

	inv[1] = 1ll;
	for (ll i = 2; i < maxn; i++)
		inv[i] = (mod - (mod/i) * inv[mod%i] % mod) % mod;

	invfac[0] = 1ll;
	for (ll i = 1; i < maxn; i++)
		invfac[i] = invfac[i-1] * inv[i] % mod;
}

ll choose(int n, int k)
{
	return (fac[n] * invfac[k]) % mod * invfac[n-k] % mod;
}

int main()
{
	init();
	
	int n, k;
	cin >> n >> k;

	cout << choose(n, k) << "\n";
}
