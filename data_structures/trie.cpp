#include <bits/stdc++.h>

using namespace std;

struct node
{
	node* b[26];
	bool fim = false;
};

node* root = new node();

void add(node* rt, string const& s)
{
	node *at = rt;

	for (char a : s) {
		if (!at->b[a-'a'])
			at->b[a-'a'] = new node();
		at = at->b[a-'a'];
	}
	at->fim = true;
}

bool find(node* rt, string const& s)
{
	node *at = rt;

	for (char a : s) {
		if (!at->b[a-'a'])
			return false;
		at = at->b[a-'a'];
	}
	return at->fim;
}

int main()
{

}