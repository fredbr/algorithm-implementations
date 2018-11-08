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
        // merging inplace removes the need to sort after the computation
        inplace_merge(ans.begin(), ans.begin()+ini, ans.begin()+ini*2);
        ini *= 2;
    }

    return ans;
}

// solution in O(2^(n/2)) using meet-in-the-middle algorithm
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

    reverse(s1.begin(), s1.end());

    ll ans = 0;
    auto l = s2.begin(), r = s2.begin();
    for (ll i : s1) {
        // amount of numbers in range [a, b]
        // using two-pointers technique
        while (r != s2.end() and *r+i <= b) ++r;
        while (l != s2.end() and *l+i < a) ++l;
        ans += r-l;
               
    }

    // overall complexity O(2^(n/2)) ~ O(1.41^n)
    cout << ans << "\n";
}