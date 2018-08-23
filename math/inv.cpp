#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll mul(ll a, ll b, ll c)
{
	return __int128(a)*b%c;
}

ll power(ll a, ll b, ll c)
{
	ll ans = 1;
	while (b) {
		if (b&1) ans = mul(ans, a, c);
		a = mul(a, a, c);
		b >>= 1;
	}
	return ans;
}

ll inv(ll x, ll mod)
{
	return power(x, mod-2, mod);
}

int main()
{
	ll x, mod;
	cin >> x >> mod;

	cout << x << " * " << inv(x, mod) << " = " << (x*inv(x, mod)%mod);
	cout << " (mod mod)\n";
}