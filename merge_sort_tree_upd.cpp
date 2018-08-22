#include <bits/stdc++.h>

#define LEFT ((no<<1)+1)
#define RIGHT ((no<<1)+2)

using namespace std;

template <typename T>
struct treap
{
	struct node
	{
		T val;
		int h, sz;
		node *l, *r;

		node(T v)
		    : val(v), h(rand()), sz(1), l(nullptr), r(nullptr) {};
	};

	node *root;

	treap() : root(nullptr) {};

	int sz(node* t)
	{
		return t? t->sz : 0;
	}

	void op(node* t)
	{
		if (!t) return;

		t->sz = sz(t->l) + 1 + sz(t->r);
	}

	void merge(node *&t, node *l, node *r)
	{
		if (!l or !r) return void(t = l? l : r);

		if (l->h > r->h) merge(l->r, l->r, r), t = l;
		else merge(r->l, l, r->l), t = r;

		op(t);
	}

	void split(node *t, node *&l, node *&r, T val)
	{
		if (!t) return void(l = r = nullptr);

		if (val <= t->val) split(t->l, l, t->l, val), r = t;
		else split(t->r, t->r, r, val), l = t;

		op(l), op(r);
	}

	void insert(node *&t, node *v)
	{
		if (!t) return void(t = v);

		if (v->h > t->h) split(t, v->l, v->r, v->val), t = v;
		else if (v->val <= t->val) insert(t->l, v);
		else insert(t->r, v);

		op(t);
	}

	void erase(node *&t, T v)
	{
		if (!t) return;

		if (t->val == v) {
			node *tmp = t;
			merge(t, t->l, t->r);
			delete tmp;
		}
		else if (t->val > v) erase(t->l, v);
		else erase(t->r, v);

		op(t);
	}

	void insert(T val)
	{
		node *v = new node(val);
		insert(root, v);
	}

	void erase(T val)
	{
		erase(root, val);
	}

	int size()
	{
		return sz(root);
	}

	int cnt(T x, T y)
	{
		node *l = nullptr, *r = nullptr;

		split(root, l, root, x);
		split(root, root, r, y);

		int ans = sz(root);

		merge(root, l, root);
		merge(root, root, r);

		return ans;
	}
};

ostream& operator<<(ostream& out, const treap<int>::node *t)
{	
	if (!t) return out;

	if (t->l) out << t->l;
	out << t->val << " ";
	if (t->r) out << t->r;
	return out;
}

ostream& operator<<(ostream& out, const treap<int>& tp)
{
	out << tp.root;

	return out;
}

template <typename T, const int maxn>
struct mtree
{
	treap<T> tree[maxn*3]{};
	T *v;

	mtree() = default;

	mtree(T *vv) : v(vv) {};  

	void build(int no, int l, int r)
	{
		if (l == r) return void(tree[no].insert(v[l]));

		for (int i = l; i <= r; i++) tree[no].insert(v[i]);

		int m = (l+r)>>1;

		build(LEFT, l, m);
		build(RIGHT, m+1, r);	
	}

	void upd(int no, int l, int r, int pos, T val)
	{	
		tree[no].erase(v[pos]);
		tree[no].insert(val);

		if (l == r) return void(v[pos] = val);

		int m = (l+r)>>1;

		if (pos <= m) upd(LEFT, l, m, pos, val);
		else upd(RIGHT, m+1, r, pos, val);
	}

	// no of ocurrences of numbers of values [x,y) in [a,b]
	int get(int no, int l, int r, int a, int b, T x, T y)
	{
		if (a <= l and r <= b) return tree[no].cnt(x, y);

		int m = (l+r)>>1;

		if (b <= m) return get(LEFT, l, m, a, b, x, y);
		if (a > m) return get(RIGHT, m+1, r, a, b, x, y);

		return get(LEFT, l, m, a, b, x, y) +
		       get(RIGHT, m+1, r, a, b, x, y);
	}

	void print(int no, int l, int r)
	{
		cout << tree[no] << "\n";

		int m = (l+r)>>1;

		if (l == r) return;

		print(LEFT, l, m);
		print(RIGHT, m+1, r);
	}
};
	
const int maxn = 101;

int v[maxn];
mtree<int, maxn> t{v};

int main()
{
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++)
		cin >> v[i];

	t.build(0, 1, n);
	t.print(0, 1, n);
}