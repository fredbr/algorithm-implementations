#include <bits/stdc++.h>
    
using namespace std;
    
using ll = long long;
    
int const maxn = 101010;
    
struct Rectangle {
    int x1, x2, y1, y2;
};
    
enum class Ev {
    ini = 1,
    fim = -1,
};
    
struct Event {
    int x;
    int y1, y2;
    Ev type;
    
    bool operator<(Event const& rhs) const {
        if (x == rhs.x) return type > rhs.type;
        return x < rhs.x;
    }
};
    
struct Seg {
    struct Node {
        int sum, cnt;
    };
    
    int n;
    vector<Node> tree;
    
    void join(int no, int l, int r) {
        if (l == r) {
            tree[no].sum = (tree[no].cnt >= 1);
        }
        else if (tree[no].cnt == 0) {
            tree[no].sum = tree[no*2+1].sum + tree[no*2+2].sum;
        }
        else {
            tree[no].sum = r-l+1;
        }
    }
    
    void upd(int no, int l, int r, int a, int b, Ev add) {
        if (a <= l and r <= b) {
            tree[no].cnt += static_cast<int>(add);
    
            join(no, l, r);
        }
        else {
            int m = (l+r)/2;
    
            if (b <= m) upd(no*2+1, l, m, a, b, add);
            else if (a > m) upd(no*2+2, m+1, r, a, b, add);
            else {
                upd(no*2+1, l, m, a, b, add);
                upd(no*2+2, m+1, r, a, b, add);
            }
    
            join(no, l, r);
        }
    }
    
    void upd(int a, int b, Ev add) {
        upd(0, 0, n, a, b, add);
    }
    
    int get() {
        return tree[0].sum;
    }
    
    Seg(int n) : n(n), tree(n*4) {};
    
    void clear() {
        fill(tree.begin(), tree.end(), Node{0, 0});
    }
};
    
    
ll sweep(Seg& seg, vector<Event> const& ev) {
    ll ans = 0;
    seg.clear();
    
    int last = ev.front().x;
    
    for (auto&& e : ev) {
        ans += ll(e.x - last) * (seg.get());
        seg.upd(e.y1, e.y2, e.type);
        last = e.x;
    }
    
    return ans;
}
    
ll rectangle_union(Seg& seg, vector<Rectangle> const& v) {
    vector<Event> r;
    
    for (auto&& rect : v) {
        r.push_back(Event{rect.x1, rect.y1, rect.y2, Ev::ini});
        r.push_back(Event{rect.x2 + 1, rect.y1, rect.y2, Ev::fim});
    }
    
    sort(r.begin(), r.end());
    
    return sweep(seg, r);
}
    
