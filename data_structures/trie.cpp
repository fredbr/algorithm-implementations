#include <bits/stdc++.h>

using namespace std;

class Trie {
private:
	struct Node
	{
		Node* b[26];
		bool fim = false;
	};

	Node* root;

	void add(Node* rt, string const& s)
	{
		Node *at = rt;

		for (char a : s) {
			if (!at->b[a-'a'])
				at->b[a-'a'] = new Node();
			at = at->b[a-'a'];
		}
		at->fim = true;
	}

	bool find(Node* rt, string const& s)
	{
		Node *at = rt;

		for (char a : s) {
			if (!at->b[a-'a'])
				return false;
			at = at->b[a-'a'];
		}
		return at->fim;
	}
public:
	void insert(string const& s)
	{
		add(root, s);
	}

	bool find(string const& s)
	{
		return find(root, s);
	}

	Trie()
	{
		root = new Node();
	}
};

int main()
{
	Trie tr;

	tr.insert("teste");

	cout << boolalpha << tr.find("test") << "\n";
	cout << boolalpha << tr.find("teste") << "\n";
}