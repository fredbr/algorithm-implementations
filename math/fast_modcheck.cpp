#include <bits/stdc++.h>

using namespace std;

typedef unsigned int ui;
typedef unsigned long long ull;

ui fast_inv(ui a)
{
	ui ans = 1, lim = 31;
	while (lim--) {
		ans = ans*a;
		a = a*a;
	}
	return ans;
}

ui is_mul(ui a, ui b)
{
	ui num = fast_inv(b);
	ui lim = -1u/b;
	return a*num <= lim;
}

int main()
{
	mt19937 rd{random_device{}()};

	using uni = uniform_int_distribution<ui>;

	cout << is_mul(-1u, 3) << "\n";
}