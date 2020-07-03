#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using namespace std;

int const K = 26;

struct Vertex {
    int next[K];
    int leaf = 0;
    int p = -1;
    char pch;
    int link = -1;
    int exit_link = -1;
    int go[K];
    int len = 0;

    Vertex(int p=-1, char ch='$') : p(p), pch(ch) {
        fill(all(next), -1);
        fill(all(go), -1);
    }
};

vector<Vertex> t(1);

void add_string(string const& s) {
    int v = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (t[v].next[c] == -1) {
            t[v].next[c] = t.size();
            t.emplace_back(v, ch);
        }
        v = t[v].next[c];
    }
    t[v].leaf++;
    t[v].len = s.size();
}

int go(int v, char ch);

int get_link(int v) {
    if (t[v].link == -1) {
        if (v == 0 || t[v].p == 0)
            t[v].link = 0;
        else
            t[v].link = go(get_link(t[v].p), t[v].pch);
    }
    return t[v].link;
}

int get_exit_link(int v) {
    if (t[v].exit_link == -1) {
        if (v == 0 or t[v].p == 0) {
            t[v].exit_link = 0;
        }
        else {
            int nxt = get_link(v);

            if (nxt == 0) {
                t[v].exit_link = 0;
            }
            else if (t[nxt].leaf) {
                t[v].exit_link = nxt;
            }
            else t[v].exit_link = get_exit_link(nxt);
        }
    }
    return t[v].exit_link;
}

int go(int v, char ch) {
    int c = ch - 'a';
    if (t[v].go[c] == -1) {
        if (t[v].next[c] != -1)
            t[v].go[c] = t[v].next[c];
        else
            t[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
    }
    return t[v].go[c];
}
