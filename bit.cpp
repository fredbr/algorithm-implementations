#include <bits/stdc++.h>

using namespace std;

// const int maxn = 1010101;

template <typename T, const int maxn>
struct bit
{
	T v[maxn];

	void add(int x, const T& d)
	{
		for (int i = x; i < maxn; i += i&-i)
			v[i] += d;
	}

	T get(int x)
	{
		T ans{};
		for (int i = x; i > 0; i -= i&-i)
			ans += v[i];
		return ans;
	}
};

bit<long long, 1010101> b;

int main()
{

}