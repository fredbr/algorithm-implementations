#include <bits/stdc++.h>

using namespace std;

int const maxn = 101010;

vector<int> v[maxn];
int val[maxn];

struct Seg {
    Seg(int n) : n(n), tree(n*4) {};

    void upd(int pos, int val) {
        upd(1, 0, n-1, pos, val);
    }

    int get(int a, int b) {
        return get(1, 0, n-1, a, b);
    }

private:
    int n;
    vector<int> tree;

    void upd(int no, int l, int r, int pos, int val) {
        if (l == r) {
            tree[no] = val;
            return;
        }

        int m = (l+r)/2;

        if (pos <= m) upd(no*2, l, m, pos, val);
        else upd(no*2+1, m+1, r, pos, val);

        tree[no] = max(tree[no*2], tree[no*2+1]);
    }

    int get(int no, int l, int r, int a, int b) {
        if (a <= l and r <= b) {
            return tree[no];
        }
        int m = (l+r)/2;

        if (b <= m) return get(no*2, l, m, a, b);
        if (a > m) return get(no*2+1, m+1, r, a, b);

        return max(
            get(no*2, l, m, a, b),
            get(no*2+1, m+1, r, a, b)
        );
    }
};

struct HLD {
    HLD(int n) : seg(n), par(n), d(n), heav(n, -1), head(n), pos(n), cur_pos(0) {
        dfs(0);
        decompose(0, 0);
    }

    int lca(int a, int b) {
        for (; head[a] != head[b]; b = par[head[b]]) {
            if (d[head[a]] > d[head[b]]) {
                swap(a, b);
            }
        }
        if (d[a] > d[b]) {
            return b;
        }
        else return a;
    }

    int max_path(int a, int b) {
        int res = 0;
        for (; head[a] != head[b]; b = par[head[b]]) {
            if (d[head[a]] > d[head[b]]) {
                swap(a, b);
            }

            res = max(res, seg.get(pos[head[b]], pos[b]));
        }
        if (d[a] > d[b]) {
            swap(a, b);
        }
        res = max(res, seg.get(pos[a], pos[b]));
        return res;
    }

    void upd(int x, int val) {
        seg.upd(pos[x], val);
    }

private:
    Seg seg;
    vector<int> par, d, heav, head, pos;
    int cur_pos;

    int dfs(int x, int p = -1) {
        int sz = 1;
        int max_c_size = 0;

        for (int u : v[x]) {
            if (u == p) continue;

            par[u] = x;
            d[u] = d[x] + 1;
            
            int c_size = dfs(u, x);
            sz += c_size;

            if (c_size > max_c_size) {
                max_c_size = c_size;
                heav[x] = u;
            }
        }

        return sz;
    } 

    void decompose(int x, int h) {
        head[x] = h;
        pos[x] = cur_pos++;

        seg.upd(pos[x], val[x]);

        if (heav[x] != -1) {
            decompose(heav[x], h);
        }

        for (int u : v[x]) {
            if (u == par[x] or u == heav[x]) continue;
            decompose(u, u);
        }
    }
};
