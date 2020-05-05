#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int const maxn = 101010;
ll const inf = 0x3f3f3f3;

template<typename Op = less<ll>>
struct LiChao {
private:
    struct Fc {
        ll a, b;

        ll eval(ll x) {
            return a*x + b;
        }
    };

    struct Node {
        Fc fn;
        unique_ptr<Node> l, r;

        Node(Fc fn) : fn(fn) {}
    };

    unique_ptr<Node> root;

    void upd(unique_ptr<Node> &t, ll l, ll r, Fc fn, Op op = Op{}) {
        ll m = (l+r)/2;
        
        bool bleft = op(fn.eval(l), t->fn.eval(l));
        bool bmid  = op(fn.eval(m), t->fn.eval(m));
        
        if (bmid) swap(t->fn, fn);
        if (l >= r) return;

        if (bleft != bmid) {
            if (!t->l) t->l = make_unique<Node>(fn);
            else upd(t->l, l, m, fn);
        }
        else {
            if (!t->r) t->r = make_unique<Node>(fn);
            else upd(t->r, m+1, r, fn);
        }
    }


    ll get(unique_ptr<Node> &t, ll x, ll l, ll r) {
        ll m = (l+r)/2;
        if (l == r and l == x) return t->fn.eval(x);

        if (x <= m and t->l)
            return min(t->fn.eval(x), get(t->l, x, l, m));
        else if (x > m and t->r)
            return min(t->fn.eval(x), get(t->r, x, m+1, r));

        return t->fn.eval(x);
    }
public:
    LiChao() : root(nullptr) {}

    void upd(ll a, ll b, ll l = -inf, ll r = inf) {
        if (!root) {
            root = make_unique<Node>(Fc{a, b});
            return;
        }
        upd(root, l, r, {a, b});
    }

    ll get(ll x, ll l = -inf, ll r = inf) {
        return get(root, x, l, r);
    }
};

ll a[maxn], b[maxn], dp[maxn];

int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    LiChao<less<ll>> l;

    l.upd(b[1], 0);

    dp[1] = b[1];

    for (int i = 2; i <= n; i++) {
        dp[i] = l.get(a[i]);
        l.upd(b[i], dp[i]);
    }

    cout << dp[n] << "\n";
}