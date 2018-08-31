#include <bits/stdc++.h>

using namespace std;

template <int sz>
struct Bit
{
	int b[sz];

	void upd(int x, int val)
	{
		for (int i = x; i < sz; i += i&-i)
			b[i] = max(b[i], val);
	}

	int get(int x)
	{
		int ans = 0;
		for (int i = x; i; i -= i&-i)
			ans = max(ans, b[i]);
		return ans;
	}
};

template <typename T>
void compress(T* v, int n)
{
	vector<T> vv(n+1);
	for (int i = 1; i <= n; i++)
		vv[i] = v[i];

	sort(vv.begin()+1, vv.end());

	for (int i = 1; i <= n; i++)
		v[i] = lower_bound(vv.begin()+1, vv.end(), v[i]) - vv.begin();
}

const int maxn = 101010;

int v[maxn];
Bit<maxn> bt;

int main()
{
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++)
		cin >> v[i];

	compress(v, n);

	for (int i = 1; i <= n; i++) {
		int x = bt.get(v[i]-1);
		bt.upd(v[i], x+1);
	}

	int ans = bt.get(n);

	cout << ans << "\n";
}