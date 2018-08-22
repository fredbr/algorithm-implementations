#include <bits/stdc++.h>

#define LEFT ((no<<1)+1)
#define RIGHT ((no<<1)+2)

using namespace std;

template <typename T, const int maxn>
struct mtree
{
	vector<T> tree[maxn*4];
	T* v;

	mtree() = default;
	mtree(T* vv) : v(vv) {};

	void build(int no, int l, int r)
	{
		if (l == r) return void(tree[no].push_back(v[l]));

		int m = (l+r)>>1;

		build(LEFT, l, m);
		build(RIGHT, m+1, r);

		merge(tree[LEFT].begin(), tree[LEFT].end(),
		      tree[RIGHT].begin(), tree[RIGHT].end(),
		      back_inserter(tree[no]));
	}

	inline int f(int no, int x, int y)
	{
		return upper_bound(tree[no].begin(), tree[no].end(), y) -
		       lower_bound(tree[no].begin(), tree[no].end(), x);
	}

	int get(int no, int l, int r, int a, int b, int x, int y)
	{
		if (a <= l and r <= b) return f(no, x, y);

		int m = (l+r)>>1;

		if (b <= m) return get(LEFT, l, m, a, b, x, y);
		if (a > m) return get(RIGHT, m+1, r, a, b, x, y);

		return get(LEFT, l, m, a, b, x, y) +
		       get(RIGHT, m+1, r, a, b, x, y);
	}
};

int main()
{
}