#include <bits/stdc++.h>

using namespace std;


// compresses positions [0,n) to values [1, n]
template <typename T>
void compress(T&& v, int n)
{
	vector<typename decay<decltype(v[0])>::type> vv(n);
	for (int i = 0; i < n; i++)
		vv[i] = v[i];

	sort(vv.begin(), vv.end());

	for (int i = 0; i < n; i++)
		v[i] = lower_bound(vv.begin(), vv.end(), v[i]) - vv.begin() + 1;
}

int va[] = {0, 1000, 2000, 5000, 3000}; 
vector<int> v{1000, 2000, 5000, 3000};

int main()
{
	compress(va+1, 4);
	compress(v, 4);

	for (int i = 1; i <= 4; i++)
		cout << va[i] << " ";
	cout << "\n";

	for (int i : v) cout << i << " ";
	cout << "\n";
}