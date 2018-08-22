#include <bits/stdc++.h>

#define REP(i, n) for(int i = 0; i < int(n); ++i)
#define REP2(i, ini, fim) for (int i = int(ini); i <= int(fim); ++i)

using namespace std;

const int maxn = 101010;

namespace sarray
{
	string s;
	int n, gap;
	int sa[maxn], pos[maxn], tmp[maxn], lcp[maxn];

	bool suf_comp(int i, int j)
	{
		if (pos[i] != pos[j]) return pos[i] < pos[j];

		i += gap, j += gap;

		return (i < n and j < n)? pos[i] < pos[j] : i > j;
	}

	void build()
	{
		n = s.size();

		REP(i, n) sa[i] = i, pos[i] = s[i];

		for (gap=1;; gap <<= 1) {

			sort(sa, sa+n, suf_comp);

			REP(i, n-1) tmp[i+1] = tmp[i] + suf_comp(sa[i], sa[i+1]);
			REP(i, n) pos[sa[i]] = tmp[i];

			if (tmp[n-1] == n-1) break;
		}
	}

	void buildLCP()
	{
		for (int i = 0, k = 0; i < n; ++i) if (pos[i] != n - 1)
		{
			for (int j = sa[pos[i] + 1]; s[i + k] == s[j + k]; ++k);
			lcp[pos[i]] = k;
			if (k)--k;
		}
	}

	int ds()
	{
		int result = n - sa[0];
 
	    for (int i = 1; i < n; i++)
	        result += (n - sa[i]) - lcp[i - 1];
 
	    result++;
	    return result;
	}
} // namespace sarray

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	// int t;
	// cin >> t;
	
	// while (t--) {
	
		cin >> sarray::s;

		sarray::build();
		sarray::buildLCP();
		REP(i, sarray::n) cout << sarray::lcp[i] << " ";
		cout << "\n";
		// sarray::buildLCP();

		// cout << sarray::ds() << "\n";
	// }
}