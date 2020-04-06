#include <vector>

using std::vector;

// indexado do 1
struct Seg {
    struct Node {
        int v;

        Node& add(Node const& rhs) {
            this->v += rhs.v;
            return *this;
        }

        static Node join(Node const& lhs, Node const& rhs) {
            Node r = lhs;
            r.add(rhs);
            return r;
        }
    };

    int n;
    vector<Node> tree;

    Seg(vector<int> const& v) : n(v.size()), tree(n*3) {
        for (int i = 0; i < this->n; i++) {
            update(i+1, v[i]);
        }
    }

    inline Node query(int l, int r) {
        Node ans{};
        for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if(l&1) ans.add(tree[l++]);
            if(r&1) ans.add(tree[--r]);
        }
        return ans;
    }

    inline void update(int p, int val) {
        for(tree[p += n] = Node{val}; p > 1; p >>= 1) {
            tree[p >> 1] = Node::join(tree[p], tree[p^1]);
        }
    }

    inline Node get(int a, int b) {
        return query(a+1, b+1);
    }

    inline void clear(int pos, int val) {
        update(pos+1, val);
    }
};

int main() {

}