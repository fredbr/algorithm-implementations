#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll isqrt(ll x) {
    ll l = 0, r = 1e9;
    while (r-l > 1) {
        ll m = (l+r)/2;
        if (m*m <= x) l = m;
        else r = m;
    }
    return l;
}

ll icbrt(ll x) {
    ll l = 0, r = 1e6;
    while (r-l > 1) {
        ll m = (l+r)/2;
        if (m*m*m <= x) l = m;
        else r = m;
    }
    return l;
}

vector<int> sieve(int n) {
    vector<bool> b(n+1);
    for (int i = 3; i*i <= n; i += 2) {
        if (b[i] == 0) {
            for (int j = i*i; j <= n; j += 2*i) {
                b[j] = 1;
            }
        }
    }

    vector<int> primes = {2};
    for (int i = 3; i <= n; i += 2) {
        if (b[i] == 0) primes.push_back(i);
    } 
    return primes;
}

// at least sqrt(n) for pi(n)
// bigger values may be faster
// for values up to 1e12 the fastest is around 1e8
// for values up to 1e11 the fastest is around 3e7
int const sqrt_limit = 30000000;

auto primes = sieve(sqrt_limit);

using ii = pair<ll, ll>;

// at least pi(sqrt(sqrt(n)))
unordered_map<ll, ll> phi_cache[200];

ll phi(ll x, int a) {
    if (a == 1) {
        return (x+1)/2;
    }

    if (phi_cache[a].count(x)) {
        return phi_cache[a][x];
    }

    ll res = phi(x, a-1) - phi(x / primes[a-1], a-1);
    phi_cache[a][x] = res;

    return res;
}

unordered_map<ll, ll> pi_cache;

ll pi(ll x) {
    if (pi_cache.count(x)) return pi_cache[x];

    if (x < sqrt_limit) {
        return upper_bound(primes.begin(), primes.end(), x) - primes.begin();
    }

    ll a = pi(isqrt(isqrt(x)));
    ll b = pi(isqrt(x));
    ll c = pi(icbrt(x));

    ll res = phi(x, a) + (b+a-2)*(b-a+1)/2;

    for (ll i = a+1; i <= b; i++) {
        ll w = x / primes[i-1];
        ll b_i = pi(isqrt(w));
        res -= pi(w);

        if (i <= c) {
            for (ll j = i; j <= b_i; j++) {
                res -= pi(w / primes[j-1]) - j + 1;
            }
        }
    }

    pi_cache[x] = res;
    return res;
}

int main() {
    ll n;
    cin >> n;

    cout << pi(n) << "\n";
}