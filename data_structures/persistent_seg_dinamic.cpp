#include <bits/stdc++.h>

#define ff first
#define ss second
#define MID ((l+r)/2)

using namespace std;

typedef pair<int, int> ii;

const int maxn = 100010;

struct node 
{
	int sum;

	node *l, *r;

	node() {

		l = r = nullptr;

		sum = 0;
	}
};

typedef node* pnode;

int n;
ii v[maxn];
int v2[maxn];
pnode root[maxn];

int sum(pnode t)
{
	return t? t->sum: 0;
}

pnode build(int l, int r)
{
	pnode cur = new node();

	if (l == r) return cur;

	cur->l = build(l, MID);
	cur->r = build(MID+1, r);

	return cur;
}

pnode update(pnode idx, int l, int r, int pos, int val)
{
	pnode cur = new node();

	cur->sum = idx->sum;
	cur->l = idx->l;
	cur->r = idx->r;

	if (l == r) {

		cur->sum = val;
		return cur;
	}

	if (pos <= MID) cur->l = update(cur->l, l, MID, pos, val);
	else cur->r = update(cur->r, MID+1, r, pos, val);

	cur->sum = sum(cur->l) + sum(cur->r);

	return cur;
}

int query(pnode idx, int l, int r, int a, int b)
{
	if (a <= l and b >= r) return sum(idx);

	if (l > b or r < a) return 0;

	int lchild = query(idx->l, l, MID, a, b);
	int rchild = query(idx->r, MID+1, r, a, b);

	return lchild+rchild;
}

int get(int a, int b, int k)
{
	int l = 1, r = n, idx;

	while (l != r) {

		idx = (l+r)/2;

		int num = query(root[idx], 1, n, a, b);

		// cout << l << " " << idx << " " << r << " " << num << "\n";

		if (num < k) l = idx+1;
		else r = idx;
	}

	idx = (l+r)/2;
	
	return idx;
}

int c[maxn];

int main()
{
	cin >> n;

	for (int i = 1; i <= n; i++) cin >> v[i].ff, v[i].ss = i, v2[i] = v[i].ff;

	map<int, int> mp;

	sort(v2+1, v2+n+1);

	int id = 1;

	for (int i = 1; i <= n; i++) {

		if (mp[v2[i]] == 0) mp[v2[i]] = id, c[id++] = v2[i];
	}

	for (int i = 1; i <= n; i++) v[i].ff = mp[v[i].ff];

	sort(v+1, v+n+1);

	root[0] = build(1, n);

	for (int i = 1; i <= n; i++) {

		root[i] = update(root[i-1], 1, n, v[i].ss, 1);
	}

	int q;
	cin >> q;

	while(q--) {

		int l, r, k;
		cin >> l >> r >> k;

		// int ans = query(root[k], 1, n, l, r);

		// cout << "\n";
		int ans = get(l, r, k);
		// cout << "\n";

		// cout << ans << "\n";
		cout << c[ans] << "\n";
	}

	return 0;
}