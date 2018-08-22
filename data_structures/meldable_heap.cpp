#include <bits/stdc++.h>

using namespace std;

struct node
{
	int val;

	node *l, *r;

	node(int val)
		: val(val), l(nullptr), r(nullptr) {};
};

mt19937 rd;
uniform_int_distribution<int> toss(0, 1);

node* meld(node *&l, node *&r)
{
	if (!l) return r;
	if (!r) return l;

	if (l->val > r->val) swap(l, r);

	if (toss(rd)) l->l = meld(l->l, r);
	else l->r = meld(l->r, r);

	return l;
}

void insert(node *&t, int x)
{
	node *aux = new node(x);

	t = meld(t, aux);
}

void pop(node *&t)
{
	if (!t) return;

	t = meld(t->l, t->r);
}

int min(node *t)
{
	return t? t->val: 0;
}

node *t = nullptr;

int main()
{
	insert(t, 2);
	insert(t, 3);
	insert(t, 4);
	print(t);
	cout << "\n";
	cout << min(t) << "\n";
	pop(t);
	cout << min(t) << "\n";
}