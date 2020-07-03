#include <bits/stdc++.h>

using namespace std;

vector<int> prefix(string const& s) {
    int const n = s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j and s[i] != s[j]) j = pi[j-1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

vector<vector<int>> prefix_automata(string s) {
    s += '#';
    int const n = s.size();
    auto aut = vector<vector<int>>(n, vector<int>(26));
    auto pi = prefix(s);

    for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++) {
            int j = i;
            while (j and 'a' + c != s[j]) j = pi[j-1];
            if ('a' + c == s[j]) j++;
            aut[i][c] = j;
        }
    }
    return aut;
}