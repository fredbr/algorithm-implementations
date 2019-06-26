#include <bits/stdc++.h>

#include <bits/stdc++.h>

using namespace std;

using u128 = __uint128_t;
using s128 = __int128_t;
using u64 = uint64_t;

inline u128 mul(u128 x, u128 y, u128 c)
{
    u128 ans = 0;
    static const u64 shift = 25;
    while (y) {
        ans += x*(y&((1<<shift)-1));
        x = (x<<shift)%c;
        y >>= shift;
    }
    return ans % c;
}

u128 HI(u128 x) { return x>>64; };    
u128 LO(u128 x) { return u64(x); };
    
namespace Prime {

    int const num_tries = 20;

    u128 power(u128 a, u128 b, u128 c) {
        u128 ans = 1;
        while (b) {

            if (b&1) ans = mul(ans, a, c);
            a = mul(a, a, c);
            b >>= 1;
        }
        return ans;
    }

    bool witness(u128 base, u128 s, u128 d, u128 n) {
        u128 x = power(base, d, n);
        u128 y;
        while (s--) {

            y = mul(x, x, n);
            if (y == 1 and x != 1 and x != n-1) return false;
            x = y;
        }
        if (x != 1) return false;
        return true;
    }

    mt19937_64 rd;

    bool is_prime(u128 x) {
        if (x == 2 or x == 3 or x == 1) return true;
        if (x % 2 == 0 or x % 3 == 0) return false;

        u128 s = 1, d = x>>1;
        while (!(d&1)) s++, d>>= 1;

        uniform_int_distribution<u64> rng(2, HI(x)? u64(-1ull): (u64(x)-1));

        for (int i = 0; i < num_tries; i++) {
            u64 p = rng(rd);
            if (!witness(p, s, d, x)) return false;
        }
        return true;
    }
} //end namespace Prime

namespace Factor {

    int const num_tries = 10;

    u128 n, niv_n;
    void setn(u128 n_) {
        // calculates multiplicative inverse of n mod 2^128
        // to use in modular reduction (how?)
        n = n_;
        niv_n = 1;
        u128 x = n;
        for (int i = 1; i <= 126; i++)
        {
            niv_n*=x;
            x*=x; 
        } 
    }
  
    struct u256 {
        u128 hi, lo;
        
        static u256 mul128(u128 x,u128 y) {
            u128 t1 = LO(x)*LO(y);
            u128 t2 = HI(x)*LO(y) + HI(y)*LO(x) + HI(t1);
            return { HI(x)*HI(y) + HI(t2) , (t2<<64) + LO(t1) };
        }
    };

    u128 mmul(u128 x,u128 y) {   
        u256 m = u256::mul128(x,y);
        // some kind of montgomery reduction?
        u128 ans = m.hi - u256::mul128(m.lo*niv_n, n).hi;
        if (s128(ans) < 0) ans += n;
        return ans;
    }

    inline u128 f(u128 x, u128 inc) {
        return mmul(x, x) + inc;
    }

    inline u128 gcd(u128 a, u128 b) {
        auto ctz = [] (u128 x) {
            if (!HI(x)) return __builtin_ctzll(x);
            return 64 + __builtin_ctzll(x>>64);
        };

        int shift = ctz(a|b);
        b >>= ctz(b);
        while (a) {
            a >>= ctz(a);
            if (a < b) swap(a, b);
            a -= b;
        }
        return b << shift;
    }

    inline u128 rho(u128 seed, u128 n, u64 inc) {
        static const int step=1<<9;
        
        setn(n);

        auto sub = [&] (u128 x, u128 y) { return x>y ? x-y:y-x; };

        u128 y = f(seed, inc);

        for (int l=1;; l<<=1)
        {
            u128 x = y;
            for (int i = 1; i <= l; i++) y = f(y, inc);
            for (int k = 0; k < l; k += step)
            {
                int d = min(step, l-k);
                u128 g = seed, y0 = y;

                for (int i = 1; i <= d; i++) {
                    y = f(y, inc);
                    g = mmul(g, sub(x,y));
                }
                
                g = gcd(g,n);
                
                if (g==1) continue;
                if (g!=n) return g;
                
                u128 y = y0;
                
                while (gcd(sub(x,y), n) == 1) y = f(y, inc);
                
                return gcd(sub(x,y), n) % n;
            }
        }
        return 0;
    }

    mt19937_64 rd;

    u128 rho(u128 x) {  
        if (x <= 3) return 0;
        if (x%2 == 0) return 2;
        if (x%3 == 0) return 3;

        uniform_int_distribution<u64> rng(2, HI(x)? u64(-1ull): (u64(x)-1));

        for (u128 i = 2; i < num_tries; i++) {
            u128 ans = rho(rng(rd), x, i);
            if (ans != 0 and ans != x) return ans;
        }
        return 0;
    }

    void factor(u128 x, vector<u128>& primes) {

        if (Prime::is_prime(x)) primes.push_back(x);
        else {
            u128 fac = rho(x);
            factor(fac, primes);
            factor(x/fac, primes);
        }
    }

    vector<u128> factor(u128 x) {
        vector<u128> v;
        factor(x, v);
        sort(v.begin(), v.end());
        return v;
    }

    vector<pair<u128,u128>> factor_pairs(u128 x) {
        auto v = factor(x);
        vector<pair<u128, u128>> res;
        
        for (int i = 0; i < (int)v.size(); i++) {
            if (i == 0 or res.back().first != v[i])
                res.emplace_back(v[i], 1);
            else
                res.back().second++;
        }
        return res;
    }
} // end namespace Factor

template <typename T> 
void read(T &x)
{
    #define gc (c=getchar())

    char c;
    while(gc < '0');
    x = c - '0';
    while(gc >= '0') x = x*10 + c - '0';

    #undef gc
}

template <typename T> 
void write(T x, char c = '\n')
{
    static char st[40];
    int top=0;
    do {st[++top] = '0' + x%10;} while (x /=10);
    do {putchar(st[top]);} while (--top);
    if (c != 0) putchar(c);
}

template<typename T>
T gcd(T a, T b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

template<typename T>
T lcm(T a, T b) {
    return a/gcd(a, b)*b;
}

template<typename T>
T power(T a, T b) {
    T ans = 1;
    while (b) {
        if (b&1) ans *= a;
        a *= a;
        b >>= 1;
    }
    return ans;
}

template<typename T>
T carmichael(pair<T, T> const& x) {
    T ans = power(x.first, x.second-1) * (x.first-1);
    return ans;
}
template<typename T>
T carmichael(T x) {
    auto factors = Factor::factor_pairs(x);
    T ans = 1;

    for (auto const& i : factors) {
        ans = lcm(ans, carmichael(i));
    }

    return ans;
}

int main() {
    u128 x;
    read(x);

    write(carmichael(x));
}