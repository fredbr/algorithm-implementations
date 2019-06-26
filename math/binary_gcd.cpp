#include <bits/stdc++.h>

// important!
#pragma GCC target("bmi")

template<typename T>
T gcd(T a, T b) {
    auto ctz = [] (T const& x) { return __builtin_ctzll(x); };

    int shift = ctz(a|b);
    b >>= ctz(b);

    while (a) {
        a >>= ctz(a);
        if (a < b) std::swap(a, b);
        a -= b;
    }

    return b << shift;
}

int main() {
    using ll = uint64_t;
    
    ll a, b;
    std::cin >> a >> b;

    std::cout << gcd<ll>(a, b) << "\n";
}