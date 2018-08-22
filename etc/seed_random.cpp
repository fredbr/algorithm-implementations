#include <bits/stdc++.h>

using namespace std;

struct random_seeder
{
	template <typename T>
	void generate(T begin, T end) const
	{
		for (random_device r; begin != end; ++begin)
			*begin = r();
	}
} sd;

int main()
{
	mt19937_64 rnd{sd};

	uniform_int_distribution<int> rng(0, 255);

	for (int i = 0; i < 10; i++) cout << char(rng(rnd));

	return 0;
}