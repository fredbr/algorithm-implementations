#include <bits/stdc++.h>

using namespace std;

template <typename T>
T operation(T a, T b)
{
	return a + b;
}

template <typename T>
struct node
{
	T *v;
	int n, sqt, nsqt;
	vector<T> p, s;
	vector<vector<T> > b;
	vector<node*> child;

	node(T *ini, int n_)
	{
		v = ini;
		n = n_;
		sqt = sqrt(n);
		nsqt = n/sqt + (n%sqt == 0? 0: 1);
		p.resize(n);
		s.resize(n);
		b.resize(nsqt);

		build_p();
		build_s();
		build_b();
		if (n > 1) build_child();
	}

	void build_p()
	{
		for (int i = 0; i < n; i++) {

			if (i == 0 or i/sqt != (i-1)/sqt)
				p[i] = v[i];
			else 
				p[i] = operation<T>(p[i-1], v[i]);
		}
	}

	void build_s()
	{
		for (int i = n-1; i >= 0; i--) {

			if (i == n-1 or i/sqt != (i+1)/sqt)
				s[i] = v[i];
			else 
				s[i] = operation<T>(s[i+1], v[i]);
		}
	}

	void build_b()
	{
		for (int i = 0; i < nsqt; i++) {

			int fim = min(n-1, sqt*(i+1)-1);
			b[i].resize(nsqt);
			b[i][i] = p[fim];

			for (int j = i+1; j < nsqt; j++) {

				int at = min(n-1, sqt*(j+1)-1);
				b[i][j] = operation<T>(b[i][j-1], p[at]);
			}
		}
	}

	void build_child()
	{
		child.resize(nsqt);
		for (int i = 0; i < nsqt; i++) {

			int ini = i*sqt;
			int fim = min(n-1, sqt*(i+1)-1);
			int se = fim-ini+1;
			
			child[i] = new node<int>(v+ini, se);
		}
	}

	T query(int l, int r)
	{l
		if (l == r) return v[l];l
		if (l/sqt != r/sqt) return get(l, r);

		int block = l/sqt;
		int ini = block*sqt;

		return child[block]->query(l-ini, r-ini);
	}

	T get(int l, int r)
	{
		int lb = l/sqt + 1;
		int rb = r/sqt - 1;

		if (lb == rb+1) return operation(s[l], p[r]);

		return operation(b[lb][rb], operation(s[l], p[r]));
	}
};

const int maxn = 1000000;

int v[maxn];
int ans[maxn];

int main()
{
	for (int i = 0; i < maxn; i++) v[i] = rand();

	node<int> *t = new node<int>(v, maxn);
	
	mt19937 rd;
	uniform_int_distribution<int> rnd(0, maxn-1);

	int q = maxn;

	while (q--) {

		int l = rnd(rd);
		int r = rnd(rd);

		if (l > r) swap(l, r);

		ans[q] = t->query(l, r);
 	}
}