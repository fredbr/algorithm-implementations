#include <bits/stdc++.h>

#define ff first
#define ss second

#define pb push_back
#define eb emplace_back
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define clr(x, c) memset((x), (c), sizeof((x)))

using namespace std;

template<class T> void DBG(T&& x) { cerr << x << " "; }
template<class T, class...Args> void DBG(T&& x, Args&&... args) { DBG(x); DBG(args...); }
#define DBG(...) cerr << "[" << #__VA_ARGS__ << "]: "; DBG(__VA_ARGS__); cerr << endl 


using ll = long long;
using ii = pair<int, int>;

int const inf = 0x3f3f3f3f;
ll const linf = 0x3f3f3f3f3f3f3f3f;

int const mod = 1e9 + 7;

seed_seq seq {
    (uint64_t) chrono::duration_cast<chrono::nanoseconds>(
    	chrono::high_resolution_clock::now().
    	time_since_epoch()).count(),
    (uint64_t) __builtin_ia32_rdtsc(),
    (uint64_t) random_device{}(),
    (uint64_t) 17
};

mt19937 rd{seq};

namespace Treap {
	struct Node
	{
		int v;
		int h, sz = 1;
        ll cheese = 0, sauce = 0;
        ll sum_cheese = 0, sum_sauce = 0;
        ll lazy_sauce = 0;
		Node *l = nullptr, *r = nullptr, *pai = nullptr;

		Node(int x)
			: v(x), h(rd()) {};
    };

    using treap = Node*;

    int sz(treap t) {
        return t? t->sz : 0;
    }

    void push(treap t) {
        if (!t) return;
        t->sauce += t->lazy_sauce;
        t->sum_sauce += t->lazy_sauce * sz(t);
        if (t->l) t->l->lazy_sauce += t->lazy_sauce;
        if (t->r) t->r->lazy_sauce += t->lazy_sauce;
        t->lazy_sauce = 0;
    }

    void reset(treap t) {
        if (!t) return;
        t->sum_sauce = t->sauce;
        t->sum_cheese = t->cheese;
    }

	void op(treap t) {
		if (!t) return;
		t->sz = 1 + sz(t->l) + sz(t->r);

        reset(t);
        push(t->l);
        push(t->r);

        if (t->l) {
            t->l->pai = t;
            t->sum_cheese += t->l->sum_cheese;
            t->sum_sauce += t->l->sum_sauce;
        }

        if (t->r) {
            t->r->pai = t;
            t->sum_cheese += t->r->sum_cheese;
            t->sum_sauce += t->r->sum_sauce;
        }
	}

	void merge(treap &t, treap l, treap r) {
        push(l), push(r); op(l), op(r);
		if (!l or !r)
		    (t=l?l:r);
		else if (l->h > r->h)
			merge(l->r, l->r, r), t = l;
		else
			merge(r->l, l, r->l), t = r;
		op(t);
	}

	void split(treap t, treap &l, treap &r, int pos) {
        push(t); op(t);
		if (!t) return void(l=r=nullptr);
        int p = sz(t->l) + 1;

		if (pos > p)
			split(t->r, t->r, r, pos - p), l = t;
		else 
			split(t->l, l, t->l, pos), r = t;

		op(l), op(r);
	}

    int pos(treap t) {
        if (!t) return 0;
        if (!t->pai) return sz(t->l) + 1;
        return (t == t->pai->r? sz(t->l) + 1 : -sz(t->r)-1) + pos(t->pai);
    }
}

using namespace Treap;

int const maxn = 303030;

int n;
vector<int> g[maxn];
treap t = nullptr;
vector<int> v[maxn];
int gin[maxn];
treap ed[maxn][2];

namespace ET {
    void dfs(int u) {
        auto tu = new Node(u);
        ed[u][0] = tu;
        merge(t, t, tu);

        for (int v : g[u]) dfs(v);

        tu = new Node(u);
        ed[u][1] = tu;
        merge(t, t, tu);
    }

    void create() {
        for (int i = 1; i <= n; i++) {
            if (gin[i] == 0) {
                dfs(i);
            }
        }
        t->pai = nullptr;
    }

    treap get_subtree(int u, bool include = true) {
        int pos_u[2] = {pos(ed[u][0]) - include + 1, pos(ed[u][1]) + include};

        treap lu = nullptr, ru = nullptr;
        split(t, t, ru, pos_u[1]);
        split(t, lu, t, pos_u[0]);

        treap aux = t;

        merge(t, lu, ru);

        if (t) t->pai = nullptr;
        if (aux) aux->pai = nullptr;

        return aux;
    }

    tuple<treap, treap, treap> get_subtrees(int u) {
        int pos_u[2] = {pos(ed[u][0]), pos(ed[u][1]) + 1};

        treap lu = nullptr, ru = nullptr;
        split(t, t, ru, pos_u[1]);
        split(t, lu, t, pos_u[0]);

        if (t) t->pai = nullptr;
        if (lu) lu->pai = nullptr;
        if (ru) ru->pai = nullptr;

        return {lu, t, ru};
    }

    void merge_subtrees(treap l, treap sub, treap r) {
        merge(t, l, sub);
        merge(t, t, r);
        t->pai = nullptr;
    }

    void insert_subtree(int u, treap v) {
        int pos_u[2] = {pos(ed[u][0]) + 1, pos(ed[u][1])};

        treap aux = nullptr;

        split(t, t, aux, pos_u[0]);

        merge(t, t, v);
        merge(t, t, aux);

        t->pai = nullptr;
    }

    bool inside_subtree(int u, int v) {
        int pos_u[2] = {pos(ed[u][0]), pos(ed[u][1])};
        int pos_v = pos(ed[v][0]);

        return pos_u[0] <= pos_v and pos_v <= pos_u[1];
    }
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
    
    int m, q;

    cin >> n >> m >> q;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        gin[v]++;
        g[u].pb(v);
    }

    ET::create();

    while (q--) {
        string op;
        cin >> op; 

        if (op == "swap") {
            int u, v;
            cin >> u >> v;

            if (ET::inside_subtree(u, v) or ET::inside_subtree(v, u)) {
                continue;
            }

            auto sub_u = ET::get_subtree(u, false);
            auto sub_v = ET::get_subtree(v, false);

            ET::insert_subtree(u, sub_v);
            ET::insert_subtree(v, sub_u);
        }
        else if (op == "append") {
            int u, v;
            cin >> u >> v;

            if (ET::inside_subtree(v, u)) {
                continue;
            }

            auto sub_v = ET::get_subtree(v);

            ET::insert_subtree(u, sub_v);
        }
        else if (op == "sauce") {
            int u, y;
            cin >> u >> y;

            auto [lu, sub_u, ru]  = ET::get_subtrees(u);

            sub_u->lazy_sauce += y;
            push(sub_u);

            ET::merge_subtrees(lu, sub_u, ru);

        }
        else if (op == "cheese") {
            int u, y;
            cin >> u >> y;

            auto [lu, sub_u, ru] = ET::get_subtrees(u);
            treap t = nullptr;

            int p = pos(ed[u][1]);
            split(sub_u, sub_u, t, p);
            t->cheese += y;
            merge(sub_u, sub_u, t);            
            sub_u->pai = nullptr;

            split(sub_u, t, sub_u, 2);
            t->cheese += y;
            merge(sub_u, t, sub_u);
            sub_u->pai = nullptr;

            ET::merge_subtrees(lu, sub_u, ru);
        }
        else if (op == "querySauce") {
            int u;
            cin >> u;

            auto [lu, sub_u, ru] = ET::get_subtrees(u);
            cout << sub_u->sum_sauce / 2 << '\n';

            ET::merge_subtrees(lu, sub_u, ru);
        }
        else if (op == "queryCheese") {
            int u;
            cin >> u;

            auto [lu, sub_u, ru] = ET::get_subtrees(u);
            cout << sub_u->sum_cheese / 2 << '\n';

            ET::merge_subtrees(lu, sub_u, ru);
        }
    }
}
