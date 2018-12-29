#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

using ll = uint64_t;

template <typename T, int sz>
int tam(T(&)[sz]) {
    return sz;
}

vector<ll> factor(ll x) {
    static const int primes[] = {2, 3, 5};
    static const int inc[] = { 4, 2, 4, 2, 4, 6, 2, 6 };
    // see compute_wheel.cpp to compute the wheel efficiently

    vector<ll> factors;

    for (auto p : primes) 
        while (x%p == 0) x /= p, factors.push_back(p);

    ll k = 7, i = 0;

    while (k*k <= x) {
        while (x%k == 0)
            x /= k, factors.push_back(k);
        k += inc[i++];
        if (i == tam(inc)) i = 0;
    }

    factors.push_back(x);
    sort(factors.begin(), factors.end());
    return factors;
}

int main() {
    ll x;
    cin >> x;

    auto ans = factor(x);

    for (auto p : ans) cout << p << " ";
    cout << "\n";
}