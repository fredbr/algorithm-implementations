#include <bits/stdc++.h>

using namespace std;

// compresses values in positions [ini, fim) to [pos, n+pos]
template <typename Iter>
void compress(Iter ini, Iter fim, int pos=1)
{
	using T = typename decay<decltype(*ini)>::type;

	vector<T> vv(ini, fim);
	sort(vv.begin(), vv.end());
	vv.erase(unique(vv.begin(), vv.end()), vv.end());

	for_each(ini, fim, [&] (T& x) {
		x = lower_bound(vv.begin(), vv.end(), x) - vv.begin() + pos;
	});
}

int va[] = {0, 1000, 2000, 5000, 3000}; 
vector<int> v{1000, 2000, 5000, 3000};

int main()
{
	compress(va+1, va+5);
	compress(v.begin(), v.end(), 0);

	for (int i = 1; i <= 4; i++)
		cout << va[i] << " ";
	cout << "\n";

	for (int i : v) cout << i << " ";
	cout << "\n";
}
