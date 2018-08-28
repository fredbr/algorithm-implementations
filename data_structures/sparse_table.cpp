#include <bits/stdc++.h>

using namespace std;

template <int size, int lsize>
struct SparseTable
{
	int table[size][lsize];

	int msb(int x)
	{
		return 31 - __builtin_clz(x);
	}

	void build(int *v, int n)
	{
		for (int i = 1; i <= n; i++)
			table[i][0] = v[i];

		for (int bk = 1; bk < lsize; bk++) {
			for (int i = 1; i <= n; i++) {
				int ni = i + (1<<(bk-1));
				table[i][bk] = max(table[i][bk-1], table[ni][bk-1]);
			}
		}
	}
	
	int get(int l, int r)
	{
		int sz = r-l;
		if (sz == 0) return table[l][0];

		int szb = msb(sz);
		int rr = r-(1<<szb)+1;

		return max(table[l][szb], table[rr][szb]);
	}
};

const int maxn = 101010;
const int maxlog = 20;

SparseTable<maxn, maxlog> st;

int main()
{
}