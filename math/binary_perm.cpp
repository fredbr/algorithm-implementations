#include <bits/stdc++.h>

using namespace std;

// generates next integer w with popcount(w) == popcount(v)
uint32_t next_perm(uint32_t v) {
    uint32_t t = (v | ( v - 1)) + 1;
    uint32_t w = t | ((((t & -t) / (v & -v)) >> 1) - 1);
    return w;
}

int main() {
    int n;
    cin >> n;
        
    // loop throught all the permutations with 1, 2, 3... bits set
    for (int i = 1; i < n; i++) {
        for (int x = (1<<i)-1; x < (1<<n); x = next_perm(x)) {
            cout << bitset<8>(x) << "\n";
        }
    }
}
