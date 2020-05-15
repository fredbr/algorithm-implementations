#include <algorithm>
#include <vector>

using namespace std;

int const maxn = 101010;

vector<int> v[maxn];
int at[maxn];

void dfs(int x, vector<int>& r) {
    while (at[x] < (int)v[x].size()) {
        int u = v[x][at[x]];
        at[x]++;

        dfs(u, r);
    }
    r.push_back(x);
}

int main() {

}