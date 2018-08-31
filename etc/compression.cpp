#include <bits/stdc++.h>

using namespace std;

template <typename T>
void compress(T *v, int n)
{
	vector<T> vv(n+1);
	for (int i = 1; i <= n; i++)
		vv[i] = v[i];

	sort(vv.begin()+1, vv.end());

	for (int i = 1; i <= n; i++)
		v[i] = lower_bound(vv.begin()+1, vv.end(), v[i]) - vv.begin();
}

int main()
{
}