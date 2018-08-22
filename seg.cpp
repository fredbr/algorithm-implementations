#include <bits/stdc++.h>

#define LEFT ((no<<1)+1)
#define RIGHT ((no<<1)+2)

using namespace std;

const int maxn = 101010;

template <typename T, const int maxn>
struct seg
{
	T tree[maxn*3];
	T *v;

	seg() = default;

	seg(T* vv) : v(vv) {};

	T op(T a, T b)
	{
		return min(a, b);
	}

	void build(int no, int l, int r)
	{
		if (l == r) return void(tree[no] = v[l]);

		int m = (l+r)>>1;

		build(LEFT, l, m);
		build(RIGHT, m+1, r);

		tree[no] = op(tree[LEFT], tree[RIGHT]);
	}

	T get(int no, int l, int r, int a, int b)
	{
		if (a <= l and r <= b) return tree[no];

		int m = (l+r)>>1;

		if (b <= m) return get(LEFT, l, m, a, b);
		if (a > m) return get(RIGHT, m+1, r, a, b);

		return op(get(LEFT, l, m, a, b),
		          get(RIGHT, m+1, r, a, b));
	}

	void upd(int no, int l, int r, int p, T val)
	{
		if (l == r) return void(tree[no] = val);

		int m = (l+r)>>1;

		if (p <= m) upd(LEFT, l, m, p, val);
		else upd(RIGHT, m+1, r, p, val);

		tree[no] = op(tree[LEFT], tree[RIGHT]);
	}
};

int v[maxn];
seg<int, maxn> s[10];

int main()
{
}

