#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

tuple<ll, ll, ll> gcdext(ll a, ll b)
{
	if (b == 0)
		return {1, 0, a};
	int x, y, g;
	tie(x, y, g) = gcdext(b, a%b);
	return {y, x-(a/b)*y, g};
}

ostream& operator<<(ostream& out, const tuple<ll,ll,ll>& x)
{
	out << "(";
	out << get<0>(x) << ", ";
	out << get<1>(x) << ", ";
	out << get<2>(x) << ")";
	return out;
}

int main()
{	
	ll x, y;
	cin >> x >> y;

	auto ans = gcdext(x, y);

	cout << ans << "\n";
}