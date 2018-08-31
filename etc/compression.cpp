#include <bits/stdc++.h>

using namespace std;

template <typename T>
void compress(T& v, int n)
{
	vector<typename remove_reference<decltype(v[0])>::type> vv(n+1);
	for (int i = 1; i <= n; i++)
		vv[i] = v[i];

	sort(vv.begin()+1, vv.end());

	for (int i = 1; i <= n; i++)
		v[i] = lower_bound(vv.begin()+1, vv.end(), v[i]) - vv.begin();
}

int va[5] = {0, 1000, 2000, 5000, 3000}; 
vector<int> v{0, 1000, 2000, 5000, 3000};

int main()
{
	compress(va, 4);
	compress(v, 4);

	for (int i = 1; i <= 4; i++)
		cout << va[i] << " ";
	cout << "\n";
	
	for (int i = 1; i <= 4; i++)
		cout << v[i] << " ";
	cout << "\n";

}