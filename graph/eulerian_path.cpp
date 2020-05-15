#include <algorithm>
#include <vector>

using namespace std;

int const maxn = 101010;

struct Edge {
    int u;
    bool vis;
};

vector<Edge> v[maxn];

void dfs(int x, vector<int>& r) {
    for (auto& e : v[x]) {
        if (e.vis) continue;

        e.vis = true;
        dfs(e.u, r);
    }
    r.push_back(x);
}

int main() {

}