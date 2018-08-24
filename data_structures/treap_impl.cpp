#include <bits/stdc++.h>

using namespace std;

template <typename T>
class Treap {
private:
	struct Node
	{
		T val;
		int h, sz;
		Node *l, *r;

		Node(T x)
			: val(x), h(rand()), sz(1), l(nullptr), r(nullptr) {};

		friend ostream& operator<<(ostream& out, Node const& t)
		{
			if (t.l) out << *t.l;
			out << t.val << " ";
			if (t.r) out << *t.r;
			return out;
		}
	};

	void op(Node *t)
	{
		if (!t) return;
		t->sz = 1;
		if (t->l) t->sz += t->l->sz;
		if (t->r) t->sz += t->r->sz;	
	}

	void merge(Node *&t, Node *l, Node *r)
	{
		if (!l or !r)
			return void(t=l?l:r);
		if (l->h > r->h)
			merge(l->r, l->r, r), t = l;
		else
			merge(r->l, l, r->l), t = r;
		op(t);
	}

	void split(Node *t, Node *&l, Node *&r, int pos)
	{
		if (!t) return void(l=r=nullptr);

		int p = 1;
		if (t->l) p += t->l->sz;

		if (p < pos)
			split(t->r, t->r, r, pos-p), l = t;
		else 
			split(t->l, l, t->l, pos), r = t;
		op(l), op(r);
	}

	void erase(Node *&t, int pos)
	{
		if (!t) return;
		
		int p = 1;
		if (t->l) p += t->l->sz;

		if (p == pos) {
			Node *aux = t;
			merge(t, t->l, t->r);
			delete aux;
		}
		else if (p < pos) erase(t->r, pos-p);
		else erase(t->l, pos);
		op(t);
	}

	T kth(Node *t, int pos)
	{
		int p = 1;
		if (t->l) p += t->l->sz;

		if (p == pos) return t->val;
		if (pos > p) return kth(t->r, pos-p);
		else return kth(t->l, pos);
	}

	void del(Node *t)
	{
		if (t->l) del(t->l);
		if (t->r) del(t->r);
		delete t;
	}

	Node *root;

public:
	void insert(int pos, T val)
	{
		Node *l = nullptr, *r = nullptr, *aux = new Node(val);

		split(root, l, r, pos+1);
		merge(l, l, aux);
		merge(root, l, r);
	}

	void erase(int pos)
	{
		erase(root, pos+1);
	}

	void erase_range(int ini, int fim)
	{
		Node *l = nullptr, *r = nullptr, *aux=nullptr;

		split(root, l, aux, ini+1);
		split(aux, aux, r, fim-ini+1);
		if (aux) del(aux);
		merge(root, l, r);
	}

	T kth(int pos)
	{
		return kth(root, pos+1);
	}

	friend ostream& operator<<(ostream& out, Treap const& tp)
	{
		if (!tp.root) return out;
		out << *tp.root;
		return out;
	}

	Treap()
	{
		root = nullptr;
	}

	~Treap()
	{
		if (root) del(root);
	}
};

int main()
{
	Treap<int> tp;

	tp.insert(0, 5);
	tp.insert(1, 3);
	tp.insert(0, 2);
	cout << tp << "\n";

	tp.erase(0);
	cout << tp << "\n";
	
	cout << tp.kth(1) << "\n";

	tp.erase_range(1, 2);
	cout << tp << "\n";
}