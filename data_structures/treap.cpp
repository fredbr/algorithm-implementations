#include <bits/stdc++.h>
#include "/home/fred/test_cases/jng.h"

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

	void op(node*& t)
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
		else if (v->val < t->val) insert(t->l, v);
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

	void split_insert(T val)
	{
		node *l = nullptr, *r = nullptr, *v = new node(val);
		split(root, l, r, val);
		merge(l, l, v);
		merge(root, l, r);
	}

	void erase(T val)
	{
		erase(root, val);
	}

	int size()
	{
		return sz(root);
	}
};

ostream& operator<<(ostream& out, const treap<int>::node *t)
{	
	if (!t) return out;

	out << t->l << t->val << " " << t->r;
	return out;
}

ostream& operator<<(ostream& out, const treap<ints>& tp)
{
	cout << tp.root;

	return out;
}

const int maxn = 10101010;

int v[maxn];

int main()
{
	ios_base::sync_with_stdio(false), cin.tie(0);
	treap<int> s{};

	int n;
	cin >> n;

	for (int i = 0; i < n; i++)
		cin >> v[i];

	// auto timer = new ContextTimer("build");

	for (int i = 0; i < n; i++)
		s.split_insert(v[i]);

	// delete timer;

	cout << s.root << "\n";
}