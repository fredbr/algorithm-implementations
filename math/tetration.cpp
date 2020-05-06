#include <bits/stdc++.h>

using namespace std;

using ll = long long;

[[ gnu::target("abm,bmi,bmi2") ]]
inline int ilog2(ll x) {
    return x==0? 0: 63 - __builtin_clzll(x);
}

inline ll isqrt(ll x) {
    ll res = sqrtl(x);
    while (res*res < x) res++;
    return res;
}

inline ll mul(ll a, ll b, ll m) {
    return __int128(a)*b%m;

    // ll res = 0;
    // while (b) {
    //     if (b&1) b = (a+b)%m;
    //     b = (b+b)%2;
    //     b >>= 1;
    // }
    // return res;
}

ll phi(ll x) {
    ll res = x;
    
    while (x % 2 == 0) {
        res -= res/2;
        x /= 2;
    }

    for (ll i = 3; i*i <= x; i += 2) {
        while (x % i == 0) {
            res -= res/i;
            x /= i;
        }
    }

    return res;
}

ll power(ll a, ll b, ll m) {
    ll res = 1;
    while (b) {
        if (b&1) res = mul(res, a, m);
        a = mul(a, a, m);
        b >>= 1;
    }
    return res;
}

