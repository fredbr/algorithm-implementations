#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

// Disjoint Set Union / Union-Find
template <int size>
struct Dsu
{
	// parent and weight of subtree i
	int pai[size], w[size];

	// find the superior parent of x
	int find(int x)
	{
		// if x if already the superior parent
		if (x == pai[x]) return x;
		// compresses the path between x and if superior parent
		return pai[x] = find(pai[x]);
	}

	// joins the subtree of x and y
	void join(int x, int y)
	{
		// finds the subtree each x and y are part of
		x = find(x), y = find(y);

		// if already joined : nothing to do
		if (x == y) return;

		// x must have more elements than y in order
		// to have the small-to-large preperty
		if (w[x] < w[y]) swap(x, y);

		// x becomes the superior parent of y
		pai[y] = x;

		// fix weights
		w[x] += w[y];
	}

	void clear()
	{
		// initialize every set x to contain only x
		// (empty sets)
		for (int i = 0; i < size; i++)
			pai[i] = i, w[i] = 1;
	}
};

Dsu<maxn> dsu;

int main()
{
	
}