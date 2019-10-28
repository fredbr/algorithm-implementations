#include <bits/stdc++.h>

using namespace std;

template<typename T, typename Comp = less<T>>
class Splay {
private:
    struct Node {
        Node *p;
        Node *l, *r;

        T val;

        Node(T const& v) : p(nullptr), l(nullptr), r(nullptr), val(v) {};
    };

    Node *root;
    int64_t sz;
    Comp comp;
    
    void lrot(Node *x) {
        Node *y = x->r;
        if (y) {
            x->r = y->l;
            if (y->l) y->l->p = x;
            y->p = x->p;
        }
        if (!x->p) root = y;
        else if (x->p->l == x) x->p->l = y;
        else if (x->p->r == x) x->p->r = y;
        if (y) y->l = x;
        x->p = y;
    }

    void rrot(Node *x) {
        Node *y = x->l;
        if (y) {
            x->l = y->r;
            if (y->r) y->r->p = x;
            y->p = x->p;
        }
        if (!x->p) root = y;
        else if (x->p->l == x) x->p->l = y;
        else if (x->p->r == x) x->p->r = y;
        if (y) y->r = x;
        x->p = y;
    }

    void splay(Node *x) {
        while (x->p) {
            if (!x->p->p) {
                if (x->p->l == x) rrot(x->p);
                else lrot(x->p);
            }
            else if (x->p->l == x and x->p->p->l == x->p) {
                rrot(x->p->p);
                rrot(x->p);
            }
            else if (x->p->r == x and x->p->p->r == x->p) {
                lrot(x->p->p);
                lrot(x->p);
            }
            else if (x->p->l == x and x->p->p->r == x->p) {
                rrot(x->p);
                lrot(x->p);
            }
            else {
                lrot(x->p);
                rrot(x->p);
            }
        }
    }

    void replace(Node *x, Node *y) {
        if (!x->p) root = y;
        else if (x == x->p->l) x->p->l = y;
        else x->p->r = y;
        if (y) y->p = x->p;
    }

    void insert(Node *&x, Node *y, Node *p) {
        if (!x) {
            x = y;
            y->p = p;
            splay(y);
        }
        else if (comp(y->val, x->val)) insert(x->l, y, x);
        else insert(x->r, y, x);
    }

    Node* find(Node *t, T const& v) {
        if (!t) return nullptr;
        else if (t->val == v) {
            splay(t);
            return root;
        }
        else if (comp(v, t->val)) return find(t->l, v);
        else return find(t->r, v);
    }

    void print(Node *t) {
        if (!t) return;
        print(t->l);
        cout << t->val << " ";
        print(t->r);
    }

    Node* find_min(Node *t) {
        if (!t) return nullptr;
        else if (t->l) return find_min(t->l);
        else return t;
    }

    Node* find_max(Node *t) {
        if (!t) return nullptr;
        else if (t->r) return find_max(t->r);
        else return t;
    }

    Node* join(Node *l, Node *r) {
        l = find_max(l), r = find_min(r);
        splay(l);
        splay(r);
        l->r = r;
        r->p = l;

        return l;
    }

public:
    Splay() : root(nullptr), sz(0), comp() {};

    void insert(T const& v) {
        Node *t = new Node(v);
        insert(root, t, nullptr);
        sz++;
    }

    Node const* find(T const& v) {
        return find(root, v);
    }

    void erase(T const& v) {
        Node *t = find(root, v);
        if (!t) return;

        sz--;

        if (!t->l) replace(t, t->r);
        else if (!t->r) replace(t, t->l);
        else {
            replace(t, join(t->l, t->r));
            delete t;
        }
    }

    int64_t size() const {
        return sz;
    }

    void print() {
        print(root);
        cout << "\n";
    }
};

int main() {
    Splay<int> st;

    st.insert(2);
    st.insert(4);
    st.insert(3);
    st.insert(5);

    assert(!st.find(1));
    assert(st.find(2));
    assert(st.find(3));
    assert(st.find(4));
    assert(st.find(5));
    assert(!st.find(6));

    st.print();

    st.erase(2);
    st.erase(4);

    assert(!st.find(1));
    assert(!st.find(2));
    assert(st.find(3));
    assert(!st.find(4));
    assert(st.find(5));
    assert(!st.find(6));

    st.print();
}