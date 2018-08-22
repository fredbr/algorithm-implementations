#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;

ll mod;

struct mat
{
	ll a, b, c, d;

	mat& operator*=(const mat& rhs)
	{
		mat tmp;
		tmp.a = (a*rhs.a + b*rhs.c)%mod;
		tmp.b = (a*rhs.b + b*rhs.d)%mod;
		tmp.c = (c*rhs.a + d*rhs.c)%mod;
		tmp.d = (c*rhs.b + d*rhs.d)%mod;
		*this = tmp;
		return *this;
	}
};

mat power(mat a, ll b)
{
	mat ans = {1, 0, 0, 1};
	while (b) {

		if (b&1) ans *= a;
		a *= a;
		b >>= 1;
	}
	return ans;
}

ii fib(ll x, ll m)
{
	mod = m;
	mat ans = power({1, 1, 1, 0}, x);
	return {ans.b, ans.a};
}

ll pis(ll x)
{
	if (x <= 5)	{

		return vector<int>{0, 1, 3, 8, 6, 20}[x];
	}
	
	ll num;

	if (x % 5 == 1 or x % 5 == 4) num = x-1;
	else num = 2*x+2;

	vector<ll> div;
	for (ll i = 1; i < sqrt(num); i++)
		if (num % i == 0)
			div.push_back(i), div.push_back(num/i);

	if (num % int(sqrt(num)) == 0)
		div.push_back(int(sqrt(num)));

	sort(div.begin(), div.end());

	for (ll i : div)
		if (fib(i, x) == ii(0, 1))
			return i;
	return num;
}

ll gcd(ll a, ll b)
{
	if (b == 0) return a;
	return gcd(b, a%b);
}

ll lcm(ll a, ll b)
{
	return __int128(a)*b/gcd(a, b);
}

ll power(ll a, ll b)
{
	ll ans = 1;
	while (b) {

		if (b&1) ans *= a;
		a *= a;
		b >>= 1;
	}
	return ans;
}

int main()
{	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	ll n;
	cin >> n;

	ll nn = n;

	vector<ii> primes;
	ll sqt = sqrt(n);
	for (ll i = 2; i <= sqt; i++) {
	
		if (n%i == 0) {
			primes.push_back({i, 1});
			n /= i;
			while (n % i == 0)
				primes.back().ss++, n/=i;
		}
	}
	if (n != 1)
		primes.push_back({n, 1});

	n = nn;

	ll ans = 1;

	for (auto x : primes) {

		ll tmp = power(x.ff, x.ss-1);
		tmp *= pis(x.ff);

		ans = lcm(ans, tmp);
	}

	cout << ans << "\n";
}