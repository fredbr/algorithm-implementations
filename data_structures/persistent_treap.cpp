#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

template <typename T>
struct treap
{
	struct node
	{
		node *l, *r;
		int h, sz;
		T val;
		bool old;

		node(T val)
			: val(val), h(rand()), sz(1), l(nullptr), r(nullptr), old(0) {};

		node(node* t)
		{
			*this = *t;
			old = 1;
		}
	};

	node *root;

	treap()
		: root(nullptr) {} ;

	treap(const treap& t)
	{
		if (t.root) root = new node(t.root);
		else root = nullptr;
	}

	int sz(node *t)
	{
		return t? t->sz : 0;
	}	

	void op(node *t)
	{
		if (!t) return;

		t->sz = sz(t->l) + sz(t->r) + 1;
	}

	void clone(node *t)
	{
		if (!t) return;

		if (t->old == 0) return;

		if (t->l) t->l = new node(t->l);
		if (t->r) t->r = new node(t->r);

		t->old = 0;
	}

	void merge(node *&t, node *l, node *r)
	{
		clone(l), clone(r);

		if (!l or !r) return void (t = l? l: r);

		if (l->h > r->h) merge(l->r, l->r, r), t = l;
		else merge(r->l, l, r->l), t = r;

		op(t);
	}

	void split(node *t, node *&l, node *&r, T val)
	{
		clone(t);

		if (!t) return void(l = r = nullptr);

		if (t->val < val) split(t->r, t->r, r, val), l = t;
		else split(t->l, l, t->l, val), r = t;

		op(l), op(r);
	}

	void insert(node *&t, node *v)
	{
		clone(t);

		if (!t) t = v;
		else if (v->h > t->h)
			split(t, v->l, v->r, v->val), t = v;
		else if (t->val < v->val) insert(t->r, v);
		else insert(t->l, v);

		op(t);
	}

	void erase(node *&t, T v)
	{
		clone(t);

		if (!t) return;
		if (t->val == v) {

			node *tmp = t;
			merge(t, t->l, t->r);
			delete tmp;
		}
		else if (t->val < v) erase(t->r, v);
		else erase(t->l, v);

		op(t);
	}

	char kth(node *t, int k)
	{	
		if (!t) return -1;

		int pos = sz(t->l) + 1;

		if (k == pos) return t->val.ss;
		else if (pos > k) return kth(t->l, k);
		else return kth(t->r, k-pos);
	}

	void insert(char v)
	{	
		node *t = new node(ii(sz(root), v));
		insert(root, t);
	}

	void erase(T v)
	{
		erase(root, v);
	}

	char kth(int k)
	{
		return kth(root, k);
	}
};

treap<int> v[maxn];

int main()
{

}