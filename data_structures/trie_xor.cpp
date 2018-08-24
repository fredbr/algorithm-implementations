#include <bits/stdc++.h>

using namespace std;

class Trie {
private:
	struct Node
	{
		Node* b[2];
	};

	Node* root;

	void add(Node* rt, int s)
	{
		Node *at = rt;

		for (int idx = 30; idx >= 0; idx--) {
			int now = (s&(1<<idx))?1:0;

			if (!at->b[now])
				at->b[now] = new Node();
			at = at->b[now];
		}
	}

	int find(Node* rt, int s)
	{
		Node *at = rt;

		int ans = 0;
		for (int idx = 30; idx >= 0; idx--) {
			int now = (s&(1<<idx))?0:1;

			if (at->b[now])
				ans |= (now<<idx), at = at->b[now];
			else
				ans |= ((1-now)<<idx), at = at->b[1-now];
		}
		return ans;
	}
public:
	void insert(int s)
	{
		add(root, s);
	}

	int find(int s)
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

	tr.insert(3);
	tr.insert(5);

	cout << tr.find(2) << "\n";
}