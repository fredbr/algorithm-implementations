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

	ll s = 1, d = n/2;
	while (d%2 == 0)
		s++, d /= 2;

	for (ll p : primes) {

		if (n == p) return true;
		if (!witness(p, d, s, n)) return false;
	}

	return true;
}

struct seeder
{
	template <typename T>
	void generate(T begin, T end)
	{
		for (random_device r; begin != end; ++begin)
			*begin = r();
	}
};

using test_func = bool (*)(ll);
using init_func = vector<ll> (*)(test_func, int);

int test(string_view test_name, test_func func, init_func init_vector, int iters)
{
	auto v = init_vector(func, iters);

	auto timer = chrono::steady_clock::now();

	int ans = 0;
	for (ll x : v)
		ans += func(x);

	auto fim = (chrono::steady_clock::now()-timer).count()/1000000.0;
	cout << test_name << "\n";
	cout << ans << " / " << iters << "\n";
	cout << fim << "ms" <<"\n\n";

	return ans;
}

int main(int argc, char** argv)
{
	int num_iters = 100000;

	if (argc > 1) num_iters = stoi(argv[1]);

	auto init_random_vector = [](test_func pr, int sz) -> vector<ll>
	{
		seeder s;
		mt19937_64 rd{s};
		uniform_int_distribution<ll> rng(2, 3'000'000'000'000'000'000ll);

		vector<ll> v(sz);

		for (ll& x : v)
			x = rng(rd);

		return v;
	};

	auto init_prime_vector = [](test_func pr, int sz) -> vector<ll>
	{
		seeder s;
		mt19937_64 rd{s};
		uniform_int_distribution<ll> rng(2, 3'000'000'000'000'000'000ll);

		vector<ll> v(sz);

		for (ll& x : v) {			
			x = rng(rd);
			while (!pr(x)) x++;
		}

		return v;
	};

	test("random", is_prime, init_random_vector, num_iters);
	test("random_primes", is_prime, init_prime_vector, num_iters);
}