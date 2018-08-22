#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> ii;

struct minqueue
{
	deque<ii> dq;

	int l, r, sum;

	void clear()
	{
		l = r = sum = 0;
		dq.clear();
	}

	void push(int x)
	{
		while (!dq.empty() and dq.back().ff > x-sum) dq.pop_back();
		dq.push_back({x-sum,r});
		r++;
	}

	void pop()
	{
		if (!dq.empty() and dq.front().ss == l) dq.pop_front();
		l++;
	}

	void add(int x)	{sum += x;}

	int getmin() {return dq[0].ff+sum;}

	int size() {return r-l;}
};

const int maxn = 1000;
const int maxm = 100000;
const int inf = 0x3f3f3f;

minqueue q[maxm];

int d[maxm];
int w[maxn], e[maxn], c[maxn];

int main()
{
	int n, m;
	cin >> n >> m;

	for (int i = 1; i <= n; i++) cin >> w[i] >> e[i] >> c[i];

	for (int i = 1; i <= m; i++) d[i] = inf;

	for (int i = 1; i <= n; i++) {

		for (int j = 0; j < w[i]; j++) q[j].clear();

		for (int j = 0; j <= m; j++) {

			minqueue& mq = q[j%w[i]];

			if (mq.size() > e[i]) mq.pop();

			mq.add(c[i]);
			mq.push(d[j]);

			d[j] = mq.getmin();
		}
	}

	for (int i = 0; i <= m; i++) cout << d[i] << " ";
	cout << "\n";
}