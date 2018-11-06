#include <bits/stdc++.h>

using namespace std;

using ll = long long;

vector<ll> all_sums(vector<ll> const& v)
{   
    vector<ll> ans(1<<v.size());

    int ini = 1;
    for (ll i : v) {
        // very fast loop optimization to ~ 2^(v.size()+1)-2 memory lookups
        for (int j = 0; j < ini; j++)
            ans[j+ini] = ans[j];
        for (int j = ini; j < ini*2; j++)
            ans[j] += i;
        ini *= 2;
    }

    return ans;
}

// solution in O(n*2^(n/2)) using meet-in-the-middle algorithm
int main()
{
    int n;
    ll a, b;
    cin >> n >> a >> b;

    vector<ll> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];

    int mid = n/2;
    vector<ll> v1(v.begin(), v.begin()+mid);
    vector<ll> v2(v.begin()+mid, v.end());

    auto s1 = all_sums(v1), s2 = all_sums(v2);

    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());

    ll ans = 0;
    for (ll i : s1) {
        // amount of numbers in range [a, b]
        ans += upper_bound(s2.begin(), s2.end(), b-i) -
               lower_bound(s2.begin(), s2.end(), a-i);
    }

    cout << ans << "\n";
}