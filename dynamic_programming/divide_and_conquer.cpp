#include <bits/stdc++.h>

using namespace std;

int const maxn = 101010;
int const maxk = 11;
int const inf = 0x3f3f3f3f;
    
int v[maxn], pref[maxn];
int dp[maxk][maxn];

int f(int i, int j) {
    return (pref[j]-pref[i-1]) * (j-i+1);
}

void solve(int k, int l, int r, int optl, int optr)
{
    if (l > r) return;

    int m = (l+r)/2;

    dp[k][m] = inf;
    int opt = m;

    int cost = 0;
    for (int i = m-1; i > optr; i--) cost += f(i, m);

    for (int i = min(optr, m); i >= optl; i--) {
        cost += f(i, m);
        if (cost + dp[k-1][i-1] < dp[k][m]) {
            dp[k][m] = cost + dp[k-1][i-1];
            opt = i;
        }
    }

    solve(k, l, m-1, optl, opt);
    solve(k, m+1, r, opt, optr);
}

int main()
{

}