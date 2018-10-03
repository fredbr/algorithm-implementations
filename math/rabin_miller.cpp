#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

inline ll mul(ll a, ll b, ll c)
{
	return __int128(a)*b%c;
}

inline ll power(ll a, ll b, ll c)
{
	ll res = 1;
	while(b) {

		if (b&1) res = mul(res, a, c);
		a = mul(a, a, c);
		b >>= 1;
	}
	return res;
}

inline bool witness(ll a, ll d, ll s, ll n)
{
	ll x = power(a, d, n), y;

	while (s--) {

		y = mul(x, x, n);

		if (y == 1 and x != 1 and x != n-1) return false;

		x = y;
	}

	if (y != 1) return false;
	return true;
}

ll primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};

inline bool is_prime(ll n)
{
	if (n == 2 or n == 3) return true;
	if (n%2 == 0 or n%3 == 0) return false;

	ll s = __builtin_ctzll(n-1), d = (n-1)>>s;

	for (ll p : primes) {

		if (n == p) return true;
		if (!witness(p, d, s, n)) return false;
	}

	return true;
}

int main()
{
	ll x;
	cin >> x;

	cout << boolalpha << is_prime(x) << "\n";
}