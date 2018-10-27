#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

int ilog2(ull x)
{
	int ans = 0;
	if (x&0xffffffff00000000) ans += 32, x >>= 32;
	if (x&0xffff0000) ans += 16, x >>= 16;
	if (x&0xff00) ans += 8, x >>= 8;
	if (x&0xf0) ans += 4, x >>= 4;
	if (x&0xc) ans += 2, x >>= 2;
	if (x&0x2) ans += 1;
	return ans;
}

int ilog10(ull x)
{
	int ans = 0;
	if (x >= 1000000000000000ull) ans += 16, x /= 10000000000000000ull;
	if (x >= 10000000ull) ans += 8, x /= 100000000ull;
	if (x >= 1000ull) ans += 4, x /= 10000ull;
	if (x >= 10ull) ans += 2, x /= 100ull;
	if (x >= 1ull) ans++;
	return ans;
}

int main()
{
	mt19937_64 rd;
	int n = 100;

	for (int i = 0; i < n; i++) {
		ull x = rd();
		cout << "x = " << x << " (" << hex << x << ")";
		cout << " | ilog2(x) = " << dec << ilog2(x);
		cout << " | ilog10(x) = " << ilog10(x) << "\n";
	}
}