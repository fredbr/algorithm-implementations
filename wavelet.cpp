#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

const int maxn = 100100;
const int maxm = 1000000000;

int v[maxn];

struct wtree
{
	int lo, hi;
	wtree *l, *r;
	vi b;

	wtree(int *from, int *to, int x, int y)
	{
		lo = x, hi = y;

		if (lo == hi or from >= to) return;

		int mid = (lo+hi)/2;

		auto f = [&](int x) -> bool
		{ 
			return x <= mid;
		};

		b.reserve(to-from+1);
		b.push_back(0);

		for (auto it = from; it != to; it++) {

			b.push_back(b.back() + f(*it));
		}

		auto pivot = stable_partition(from, to, f);

		l = new wtree(from, pivot, lo, mid);
		r = new wtree(pivot, to, mid+1, hi);
	}

	// kth element between l and r
	int kth(int l, int r, int k)
	{
		if (l > r) return 0;
		if (lo == hi) return lo;

		int inleft = b[r] - b[l-1];

		int lb = b[l-1];
		int rb = b[r];

		if (k <= inleft) return this->l->kth(lb+1, rb, k);
		return this->r->kth(l-lb, r-rb, k-inleft);
	}

	// number of elements between l and r less or equal than k
	int lte(int l, int r, int k)
	{
		if (l > r or k < lo or k > hi) return 0;

		if (hi <= k) return r-l+1;

		int lb = b[l-1], rb = b[r];
	
		return this->l->lte(lb+1, rb, k) + this->r->lte(l-lb, r-rb, k);
	}

	// number of elements between l and r equal to k
	int count(int l, int r, int k)
	{
		if (l > r or k < lo or k > r) return 0;

		if (lo == hi) return r-l+1;

		int lb = b[l-1], rb = b[r], mid = (l+r)/2;

		if (k <= mid) return this->l->count(lb+1, rb, k);
		return this->r->count(l-lb, r-rb, k);
	}

	~wtree()
	{
		delete l;
		delete r;
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	// cin.tie(0);

	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) cin >> v[i];

	wtree *t = new wtree(v+1, v+n+1, 1, maxm);

	int q;
	cin >> q;

	while (q--) {

		int l, r, k;
		cin >> l >> r >> k;

		int res = t->kth(l, r, k);

		cout << res << "\n";
	}

	return 0;
}