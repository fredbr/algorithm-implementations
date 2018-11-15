#include <bits/stdc++.h>

using namespace std;

const int maxn = 101010;

template <typename T>
class Treap {
private:
	struct Node
	{
		Node *l, *r;
		int h, sz;
		T val;
		bool old;

		Node(T const& val)
			: l(nullptr), r(nullptr), h(rand()), sz(1), val(val), old(false) {};

		Node(Node* t)
		{
			*this = *t;
			old = true;
		}
	};

	Node *root;

	int sz(Node *t)
	{
		return t? t->sz : 0;
	}	

	void op(Node *t)
	{
		if (!t) return;

		t->sz = sz(t->l) + sz(t->r) + 1;
	}

	void clone(Node *t)
	{
		if (!t) return;

		if (t->old == false) return;

		if (t->l) t->l = new Node(t->l);
		if (t->r) t->r = new Node(t->r);

		t->old = true;
	}

	void merge(Node *&t, Node *l, Node *r)
	{
		clone(l), clone(r);

		if (!l or !r) return void (t = l? l: r);

		if (l->h > r->h) merge(l->r, l->r, r), t = l;
		else merge(r->l, l, r->l), t = r;

		op(t);
	}

	void split(Node *t, Node *&l, Node *&r, T val)
	{
		clone(t);

		if (!t) return void(l = r = nullptr);

		if (t->val < val) split(t->r, t->r, r, val), l = t;
		else split(t->l, l, t->l, val), r = t;

		op(l), op(r);
	}

	void insert(Node *&t, Node *v)
	{
		clone(t);

		if (!t) t = v;
		else if (v->h > t->h)
			split(t, v->l, v->r, v->val), t = v;
		else if (t->val < v->val) insert(t->r, v);
		else insert(t->l, v);

		op(t);
	}

	void erase(Node *&t, T v)
	{
		clone(t);

		if (!t) return;
		if (t->val == v) {
			Node *tmp = t;
			merge(t, t->l, t->r);
			delete tmp;
		}
		else if (t->val < v) erase(t->r, v);
		else erase(t->l, v);

		op(t);
	}

	T const& kth(Node *t, int k)
	{	
		int pos = sz(t->l) + 1;

		if (k == pos) return t->val;
		else if (pos > k) return kth(t->l, k);
		else return kth(t->r, k-pos);
	}

public:
	Treap() : root(nullptr) {} ;

	~Treap() = default;
	// n sei o que fazer :/

	Treap(Treap const& tp) : root(new Node(tp.root)) {};
	
	Treap(Treap&& tp) : root(tp.root) {};

	Treap& operator=(Treap const& tp) {
		root = new Node(tp.root);
		return *this;
	}

	Treap& operator=(Treap&& tp) {
		root = tp.root;
		return *this;
	}

	void insert(T const& v)
	{	
		Node *t = new Node(v);
		insert(root, t);
	}

	void erase(T const& v)
	{
		erase(root, v);
	}

	T const& kth(int k)
	{
		return kth(root, k+1);
	}
};

Treap<int> v[maxn];

int main()
{
	v[0].insert(4);
	
	v[1] = v[0];
	v[1].insert(6);

	v[2] = v[1];
	v[2].erase(4);

	cout << v[0].kth(0) << "\n";
	cout << v[1].kth(0) << " " << v[1].kth(1) << "\n";
	cout << v[2].kth(0) << "\n";
}