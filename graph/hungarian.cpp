#include <bits/stdc++.h>

using namespace std;

constexpr int inf = numeric_limits<int>::max();

struct Hungarian {
    Hungarian(int n_, int m_) :
            n(n_), m(m_), at(1), u(n_+1), v(m_+1), p(m_+1), way(m_+1) {}

    Hungarian(vector<vector<int>> const& v) :
            n((int)v.size() - 1), m((int)v[0].size() - 1), at(1),
            u(n+1), v(m+1), p(m+1), way(m+1) 
    {
        for (int i = 1; i <= n; i++) {
            add_row(v[i]);
        }
    }

    void add_row(vector<int> const& a) {
        p[0] = at++;
        int j0 = 0;
        vector<int> minv (m+1, inf);
        vector<char> used (m+1, false);

        do {
            used[j0] = true;
            int i0 = p[j0],  delta = inf,  j1;
            for (int j = 1; j <= m; j++) {
                if (!used[j]) {
                    int cur = a[j] - u[i0] - v[j];
                    if (cur < minv[j])
                        minv[j] = cur,  way[j] = j0;
                    if (minv[j] < delta)
                        delta = minv[j],  j1 = j;
                }
            }
            for (int j = 0; j <= m; j++) {
                if (used[j])
                    u[p[j]] += delta,  v[j] -= delta;
                else
                    minv[j] -= delta;
            }
            j0 = j1;
        } while (p[j0] != 0);
        
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    vector<int> get_ans() {
        vector<int> ans (at);
        for (int j=1; j <= m; j++) {
            ans[p[j]] = j;
        }
        return ans;
    }

private:
    int n, m, at;
    vector<int> u, v, p, way;
};

int main() {
    int n = 3, m = 4;

    Hungarian h(n, m);

    auto print_ans = [] (auto& h) {
        auto res = h.get_ans();
        for (int i = 1; i < (int)res.size(); i++) {
            cout << res[i] << " ";
        }
        cout << "\n";
    };

    h.add_row({0, 1, 2, 3, 1});
    print_ans(h);
    
    h.add_row({0, 1, 2, 3, 1});
    print_ans(h);
    
    h.add_row({0, 1, 2, 3, 0});
    print_ans(h);
}