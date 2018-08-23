#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;
const int maxq = 101010;

struct Query
{
	int l, bk, r, id;

	bool operator<(Query const& rhs) {
		if (bk == rhs.bk) {
			if (bk&1) return r > rhs.r;
			else return r < rhs.r;
		}
		return bk < rhs.bk;
	}
};

int ans;
int v[maxn], res[maxn];
Query qr[maxq];

void add(int x)
{

}

void rem(int x)
{

}

int main()
{
	int n, q;
	cin >> n >> q;

	int sqt = sqrt(n)+1;

	for (int i = 0; i < n; i++)
		cin >> v[i];

	for (int i = 0; i < q; i++)
		cin >> qr[i].l >> qr[i].r, qr[i].bk = qr[i].l/sqt, qr[i].id = i;

	sort(qr, qr+q);

	int cl = 0, cr = -1;
	for (int i = 0; i < q; i++) {
		int l = qr[i].l, r = qr[i].r;

		while (cr < r) add(++cr);
		while (cl > l) add(--cl);
		while (cr > r) rem(cr--);
		while (cl < l) rem(cl++);

		res[qr[i].id] = ans;
	}

	for (int i = 0; i < q; i++)
		cout << res[i] << "\n";
}