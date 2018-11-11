#include <bitset>
#include <iostream>

using namespace std;

int const maxn = 101;
int const maxm = 100000001;

int v[maxn];
// must to have two bitsets as one serves as temporary to avoid
// stack oveflow which happens when large bitsets are implicitly 
// allocated eg. dp |= dp<<v[i] (dp<<v[i] is allocated on the heap)
bitset<maxm> dp, dp2;

// find first value > m that cannot be formed by the sums of
// numbers from v
int main()
{
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) cin >> v[i];

    dp[0] = true;
    dp2[0] = true;
    for (int i = 0; i < n; i++) {
        dp2 <<= v[i];
        dp |= dp2;
        dp2 = dp;
    }

    dp.flip();
    cout << dp._Find_next(m) << "\n";
}