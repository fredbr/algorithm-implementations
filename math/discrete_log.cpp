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

// finds x such that (a^x) % mod == b
ll d_log(ll a, ll b, ll mod)
{
	ll m = ll(std::ceil(std::sqrt(mod)));
	unordered_map<ll, ll> tb;
	ll e = 1;

	for (ll i = 0; i < m; i++) {
		tb[e] = i;
		e = mul(e, a, mod);
	}

	ll f = power(a, mod-m-1, mod);
	e = b;

	for (ll i = 0; i < m; i++) {
		auto it = tb.find(e);
		if (it != tb.end()) {
			return i*m + it->second;
		}
		e = mul(e, f, mod);
	}

	return -1;
}

int main()
{
	ll a, b, p;
	cin >> a >> b >> p;

	cout <<d_log(a, b, p) << "\n";
}