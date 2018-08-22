#include <bits/stdc++.h>
#include "/home/fred/test_cases/jng.h"

using namespace std;

typedef unsigned int ui;

const int maxn = 10101010;

struct node
{
	int val;
	int h, sz;

	node *l, *r;

	node(int val)
		: val(val), h(rand()), sz(1), l(nullptr), r(nullptr) {};
	node(int val, int sz)
		: val(val), h(0), sz(sz), l(nullptr), r(nullptr) {};

};

int v[maxn];

node* build(int l, int r)
{
	if (l == r) return new node(v[l], 1);
	if (l > r) return nullptr;

	int m = (l+r)>>1;

	node *at = new node(v[m], r-l+1);

	at->l = build(l, m-1);
	at->r = build(m+1, r);

	return at;
}

int s = 0;

void fix(int n, node *no)
{
	queue<node*> q;
	q.push(no);

	int step = (ui(-1))/(n+1);

	int at = 0x7fffffff;
	at -= step;

	while (!q.empty()) {

		node *t = q.front();
		q.pop();

		t->h = at;
		at -= step;

		if (t->l) q.push(t->l);
		if (t->r) q.push(t->r);
	}
}

ostream& operator<<(ostream& out, node *t)
{
	if (!t) return out;

	out << t->l <<  t->val << " "<< t->r;

	return out;
}

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(0);

	int n;
	cin >> n;

	for (int i = 0; i < n; i++) cin >> v[i];

	auto timer = new ContextTimer("build");
	
	sort(v, v+n);
	
	node *t = build(0, n-1);

	fix(n, t);

	delete timer;

	cout << t->val << "\n";
}