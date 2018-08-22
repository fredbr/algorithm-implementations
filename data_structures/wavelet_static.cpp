#include <bits/stdc++.h>

#define LEFT ((no*2)+1)
#define RIGHT ((no*2)+2)

using namespace std;

typedef vector<int> vi;

const int maxn = 100010;
const int maxm = maxn;

int v[maxn];
vi b[maxn*4];
int mid;

inline bool f(int x)
{
	return x <= mid;
} 

void build(int no, int *from, int *to, int lo, int hi)
{
	if (from >= to or lo == hi) return;

	mid = (lo+hi)/2;

	b[no].push_back(0);

	for (int *it = from; it != to; it++) {

		b[no].push_back(b[no].back() + f(*it));
	}

	int *pivot = stable_partition(from, to, f);

	build(LEFT, from, pivot, lo, mid);
	mid = (lo+hi)/2;
	build(RIGHT, pivot, to, mid+1, hi);
}

int kth(int no, int lo, int hi, int l, int r, int k)
{
	if (l > r) return 0;

	if (lo == hi) return lo;

	mid = (lo+hi)/2;

	int lb = b[no][l-1];
	int rb = b[no][r];
	int inleft = rb - lb;

	if (inleft >= k) return kth(LEFT, lo, mid, lb+1, rb, k);
	return kth(RIGHT, mid+1, hi, l-lb, r-rb, k-inleft);
}

int main()
{
	int n, q;
	cin >> n >> q;

	for (int i = 1; i <= n; i++) cin >> v[i];

	build(0, v+1, v+1+n, 1, maxm);

	while (q--) {

		int l, r, k;
		cin >> l >> r >> k;

		int res = kth(0, 1, maxm, l, r, k);

		cout << res << "\n";
	}

	return 0;
}