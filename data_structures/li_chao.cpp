#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int const maxn = 101010;
ll const maxm = 1e9;

struct Fc {
    ll a, b;

    ll eval(ll x) {
        return a*x + b;
    }
};

struct Node {
    Fc fn;
    Node *l = nullptr, *r = nullptr;
};

void upd(Node *t, ll l, ll r, Fc fn) {
    ll m = (l+r)/2;
    
    bool bleft = fn.eval(l) < t->fn.eval(l);
    bool bmid  = fn.eval(m) < t->fn.eval(m);
    
    if (bmid) swap(t->fn, fn);
    if (l >= r) return;

    if (bleft != bmid) {
        if (!t->l) t->l = new Node{fn};
        else upd(t->l, l, m, fn);
    }
    else {
        if (!t->r) t->r = new Node{fn};
        else upd(t->r, m+1, r, fn);
    }
}

ll get(Node *t, ll l, ll r, ll x) {
    ll m = (l+r)/2;
    if (l == r and l == x) return t->fn.eval(x);

    if (x <= m and t->l)
        return min(t->fn.eval(x), get(t->l, l, m, x));
    else if (x > m and t->r)
        return min(t->fn.eval(x), get(t->r, m+1, r, x));

    return t->fn.eval(x);
}

ll a[maxn], b[maxn], dp[maxn];

int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    Node *root = new Node{{b[1], 0}};
    dp[1] = b[1];

    for (int i = 2; i <= n; i++) {
        dp[i] = get(root, 0, maxm, a[i]);
        upd(root, 0, maxm, {b[i], dp[i]});
    }

    cout << dp[n] << "\n";
}