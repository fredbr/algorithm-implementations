#include <bits/stdc++.h>

using namespace std;

template <int size>
struct Bit
{
	int b[size];

	void add(int x, int d)
	{
		for (int i = x; i < size; i += i&-i)
			b[i] += d;
	}

	int get(int x)
	{
		int ans = 0;
		for (int i = x; i; i -= i&-i)
			ans += b[i];
		return ans;
	}

	void build(int* v, int n)
	{
		for (int i = 1; i <= n; i++) {
			b[i] += v[i];
			if (i + (i&-i) < size)
				b[i + (i&-i)] += b[i]; 
		}
	}

	void linearize(int *v, int n)
	{
		for (int i = n; i >= 1; i--) {
			if (i + (i&-i) < size)
				b[i + (i&-i)] -= b[i];
		}
		for (int i = 1; i <= n; i++ )
			v[i] = b[i];
	}
};

const int maxn = 101010;

int v[maxn];
Bit<maxn> bit;

int main()
{
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++)
		cin >> v[i];

	bit.build(v, n);

	int q;
	cin >> q;

	while (q--) {
		int op;
		cin >> op;

		// update
		if (op == 1) {
			int pos, val;
			cin >> pos >> val;

			bit.add(pos, val-v[pos]);
			v[pos] = val;
		}
		// query
		else {
			int x;
			cin >> x;

			cout << bit.get(x) << "\n";
		}
	}

	bit.linearize(v, n);
	for (int i = 1; i <= n; i++)
		cout << v[i] << " ";
	cout << "\n";
}