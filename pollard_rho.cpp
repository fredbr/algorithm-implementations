#include <bits/stdc++.h>

#pragma GCC optmize("Ofast")

using namespace std;

// typedef __int128 ll;
typedef long long ll;

ll mul(ll a, ll b, ll c)
{
	// ll ans = ll(0);
	// while (b) {

	// 	if (b&1) ans = (ans+a)%c;
	// 	a = (a+a)%c;
	// 	b >>= 1;
	// }
	// return ans;
	return (__int128)a*b%c;
}

ll power(ll a, ll b, ll c)
{
	ll ans = ll(1);
	while (b) {

		if (b&1) ans = mul(ans, a, c)%c;
		a = mul(a, a, c);
		b >>= 1;
	}
	return ans;
}

ll f(ll x, ll p, ll inc)
{
	return (mul(x, x, p) + inc) % p;
}

ll gcdd(ll a, ll b)
{
	while (b) {

		a = a%b;
		swap(a, b);
	}
	return a;
}

ll rho(ll seed, ll p, ll inc)
{
	ll x = seed, y = seed, d = ll(1);
	while (d == ll(1)) {

		x = f(x, p, inc);
		y = f(f(y, p, inc), p, inc);
		d = gcdd(llabs(x-y), p);
	}

	if (d == p) return ll(-1);
	return d;
}

bool witness(ll base, ll s, ll d, ll n)
{
	ll x = power(base, d, n);
	ll y;
	while (s) {

		y = mul(x, x, n);
		if (y == ll(1) and x != ll(1) and x != n-ll(1)) return false;
		s--;
		x = y;
	}
	if (y != ll(1)) return false;
	return true;
}

ll primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};

bool is_prime(ll x)
{
	if (x == ll(2) or x == ll(3) or x == ll(1)) return true;
	if (x % ll(2) == 0 or x % ll(3) == 0) return false;

	ll s = ll(1), d = x>>1;
	while (!(d&ll(1))) s++, d>>= 1;

	for (ll p : primes) {
		if (p == x) return true;
		if (!witness(p, s, d, x)) return false;
	}
	return true;
}

mt19937_64 rd;

ll rho(ll x)
{	
	if (x%ll(2) == ll(0)) return ll(2);
	if (x%ll(3) == ll(0)) return ll(3);

	if (is_prime(x)) return -1ll;

	uniform_int_distribution<ll> rng(ll(2), x-ll(1));

	for (ll i = 2; i <= 11; i++) {
		ll ans = rho(rng(rd), x, i);
		if (ans != -1 and ans != x) return ans;
	}
	return ll(-1);
}

vector<ll> factor(ll x)
{
	vector<ll> fac;
	queue<ll> prox;

	prox.push(x);

	while (!prox.empty()) {

		ll a = prox.front();
		prox.pop();
		if (is_prime(a)) fac.push_back(a);
		else {
			
			ll b = rho(a);

			if (b != -1) prox.push(b), prox.push(a/b);
			else fac.push_back(a);
		}
	}
	sort(fac.begin(), fac.end());
	return fac;
}

int main()
{
	ll x;
	x = scan();

	vector<ll> fac = factor(x);

	for (ll i : fac) print(i);
	cout << "\n";
}