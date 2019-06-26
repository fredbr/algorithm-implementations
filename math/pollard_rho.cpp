#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

inline ll mul(ll a, ll b, ll c)
{
#ifdef __SIZEOF_INT128__
	return (__uint128_t)a*b%c;
#else
	ll ans = 0;
	while (b) {
		if (b&1) ans = (a+ans)%c;
		a = (a+a)%c;
		b >>= 1;
	}
	return ans;
#endif
}

namespace Prime {

	ll power(ll a, ll b, ll c) {
		ll ans = 1;
		while (b) {

			if (b&1) ans = mul(ans, a, c);
			a = mul(a, a, c);
			b >>= 1;
		}
		return ans;
	}

	bool witness(ll base, ll s, ll d, ll n)	{
		ll x = power(base, d, n);
		ll y;
		while (s--) {
			y = mul(x, x, n);
			if (y == 1 and x != 1 and x != n-1) return false;
			x = y;
		}
		if (y != 1) return false;
		return true;
	}

	ll primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};

	bool is_prime(ll x) {
		if (x == 2 or x == 3 or x == 1) return true;
		if (x % 2 == 0 or x % 3 == 0) return false;

		ll s = 1, d = x>>1;
		while (!(d&1)) s++, d>>= 1;

		for (ll p : primes) {
			if (p == x) return true;
			if (!witness(p, s, d, x)) return false;
		}
		return true;
	}
} //end namespace Prime

namespace Factor {

	int const num_tries = 10;

	inline ll f(ll x, ll p, ll inc) {
		return (mul(x, x, p) + inc) % p;
	}

	inline ll gcdd(ll a, ll b) {
		while (b) {
			a = a%b;
			swap(a, b);
		}
		return a;
	}

	inline ll rho(ll seed, ll p, ll inc) {
		ll x = seed, y = seed, d = 1;
		while (d == 1) {
			x = f(x, p, inc);
			y = f(f(y, p, inc), p, inc);
			d = gcdd(llabs(x-y), p);
		}

		if (d == p) return 0;
		return d;
	}

	mt19937_64 rd;

	ll rho(ll x) {	
		if (x%2 == 0) return 2;
		if (x%3 == 0) return 3;

		uniform_int_distribution<ll> rng(2, x-1);

		for (ll i = 2; i < num_tries; i++) {
			ll ans = rho(rng(rd), x, i);
			if (ans != 0 and ans != x) return ans;
		}
		return 0;
	}

	void factor(vector<ll>& v, ll x) {
		if (Prime::is_prime(x)) v.push_back(x);
		else {
			ll y = rho(x);
			factor(v, y);
			factor(v, x/y);
		}
	}
} // end namespace Factor

int main()
{
	ll x;
	cin >> x;

	vector<ll> fac;

	Factor::factor(fac, x);
	for (ll i : fac) cout << i << " ";
	cout << "\n";
}