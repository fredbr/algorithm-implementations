#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

const int maxn = 101010;

template <int size>
struct Dsu
{
	int pai[size], w[size];

	int find(int x)
	{
		if (x == pai[x]) return x;
		return pai[x] = find(pai[x]);
	}

	void join(int x, int y)
	{
		x = find(x), y = find(y);
		if (x == y) return;
		if (w[x] < w[y]) swap(x, y);
		pai[y] = x;
		w[x] += w[y];
	}

	void clear()
	{
		for (int i = 0; i < size; i++)
			pai[i] = i, w[i] = 1;
	}
};

struct Edge
{
	int a, b, w;

	bool operator<(const Edge& rhs) {
		return w < rhs.w;
	}
};

Dsu<maxn> dsu;

int kruskal(vector<Edge> &lista)
{
	dsu.clear();
	sort(lista.begin(), lista.end());

	int ans = 0;
	for (const Edge& ed : lista) {
		if (dsu.find(ed.a) == dsu.find(ed.b))
			continue;
		dsu.join(ed.a, ed.b);
		ans += ed.w;
	}

	return ans;
}

int main()
{

}