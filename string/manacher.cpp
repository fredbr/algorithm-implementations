#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

template<typename Container>
std::pair<std::vector<int>, std::vector<int>> manacher(Container const& s) {
    int n = s.size();
    std::vector<int> d1(n), d2(n);

    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : std::min(d1[l+r-i], r-i+1);
        while (k <= i and i+k < n and s[i-k] == s[i+k]) {
            k++;
        }
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    } 

    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : std::min(d2[l+r-i+1], r-i+1);
        while (k+1 <= i and i+k < n and s[i-k-1] == s[i+k]) {
            k++;
        }
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }

    // d1 odd lenght palindromes center (i)
    // d2 even lenght palindromes center (i-1, i)
    return {d1, d2};
}

int main() {
    std::string s;
    std::cin >> s;

    auto [d1, d2] = manacher(s);

    for (auto i : d1) std::cout << i << " ";
    std::cout << "\n";

    for (auto i : d2) std::cout << i << " ";
    std::cout << "\n";
}   