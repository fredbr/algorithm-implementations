#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> ii;

const int inf = 0x3f3f3f3f;

struct minqueue
{
	deque<ii> dq;

	int l, r;

	minqueue() {

		l = 1;
		r = 1;
	}

	void add(int x)
	{
		while(dq.size() >= 1 and dq.back().ff >= x) dq.pop_back();

		dq.push_back({x, r++});
	}

	void pop()
	{
		if (dq.front().ss == l++) dq.pop_front();
	}

	int get()
	{
		return dq.empty()? inf: dq[0].ff;
	}
};

int main()
{
	return 0;
}