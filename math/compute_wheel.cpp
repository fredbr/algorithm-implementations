#include <bits/stdc++.h>

using namespace std;

vector<int> compute_wheel(vector<int> const& v) {
    int sz = 1;
    for (auto x : v) sz *= x;

    vector<int> primes;

    vector<char> s(sz+1);
    for (auto i : v)
        for (int j = i; j <= sz; j += i)
            s[j] = 1;

    for (int i = v.back(); i <= sz; i++)
        if (!s[i])
            primes.push_back(i);

    primes.push_back(sz+1);
    primes.push_back(primes.front()+sz);
    vector<int> inc(primes.size()-1);

    for (int i = 0; i < int(inc.size()); i++)
        inc[i] = primes[i+1]-primes[i];

    return inc;
}

int main() {
    auto x = compute_wheel({2, 3, 5});
        
    cout << "{ ";
    for (auto i : x) cout << i << ", ";
    cout << "}\n";
}