#include <bits/stdc++.h>

using namespace std;

mt19937 rd{17};

template <typename T>
class Treap {
private:
	struct Node	{
		Node *l, *r;
		T val;
		uint32_t h, sz;

		Node() = default;

		~Node() {};

		Node(T const& x)
			: l(nullptr), r(nullptr), val(x), h(rd()), sz(1) {};

		friend ostream& operator<<(ostream& out, Node const& t)
		{
			if (t.l) out << *t.l;
			out << t.val << " ";
			if (t.r) out << *t.r;
			return out;
		}
	};


	void op(Node *t) {
		if (!t) return;
		t->sz = 1;
		if (t->l) t->sz += t->l->sz;
		if (t->r) t->sz += t->r->sz;	
	}

	void merge(Node *&t, Node *l, Node *r) {
		if (!l or !r)
			return void(t=l?l:r);
		if (l->h > r->h)
			merge(l->r, l->r, r), t = l;
		else
			merge(r->l, l, r->l), t = r;
		op(t);
	}

	void split(Node *t, Node *&l, Node *&r, int pos) {
		if (!t) return void(l=r=nullptr);

		int p = 1;
		if (t->l) p += t->l->sz;

		if (p < pos)
			split(t->r, t->r, r, pos-p), l = t;
		else 
			split(t->l, l, t->l, pos), r = t;
		op(l), op(r);
	}

	void insert(Node *&t, Node *aux, int pos) {
		if (!t) {
			t = aux;
			op(t);
			return;
		}

		int p = 1;
		if (t->l) p += t->l->sz;

		if (t->h < aux->h) split(t, aux->l, aux->r, pos), t = aux;
		else if (p >= pos) insert(t->l, aux, pos);
		else insert(t->r, aux, pos-p);

		op(t);
	}

	void erase(Node *&t, int pos) {
		if (!t) return;
		
		int p = 1;
		if (t->l) p += t->l->sz;

		if (p == pos) merge(t, t->l, t->r);
		else if (p < pos) erase(t->r, pos-p);
		else erase(t->l, pos);

		op(t);
	}

	Node& kth(Node *t, int pos)
	{
		int p = 1;
		if (t->l) p += t->l->sz;

		if (p == pos) return *t;
		if (pos > p) return kth(t->r, pos-p);
		else return kth(t->l, pos);
	}

	Node *root = nullptr;
	vector<Node> aux_new;
	int idx = 0;

	Node* _get_ptr(T const& val) {
		return ::new (static_cast<void*>(&aux_new[idx++])) Node(val);
	}

public:
	class Iterator {
	public:
		stack<Node*> bt;
		Iterator()  = default;
		Iterator(Iterator&& t) : bt(move(t.bt)) {};
		Iterator(Iterator const& t) : bt(t.bt) {};

		Iterator& operator=(Iterator&& t) {
			return Iterator(move(t));
		}

		Iterator& operator=(Iterator const& t) {
			return Iterator(t);
		}

		Iterator& operator++() {
			Node* t = bt.top();

			if (!t->r) {
				bt.pop();
				return *this;
			}

			t = t->r;
			bt.pop();
			bt.push(t);

			while (t->l) {
				t = t->l;
				bt.push(t);
			}

			return *this;
		}

		Node& operator*() {
			return *bt.top();
		}

		Node* operator->() {
			return bt.top();
		}

		bool operator==(Iterator const& t) const {
			return bt == t.bt;
		}

		bool operator!=(Iterator const& t) const {
			return !(bt == t.bt);
		}
	};

	Iterator begin() {
		Iterator it;
		Node* t = root;

		while (t and t->l) {
			it.bt.push(t);
			t = t->l;
		}
		if (t) it.bt.push(t);

		return it;
	}

	Iterator end() {
		return Iterator();
	}

	void insert(int pos, T const& val)
	{
		Node *l = nullptr, *r = nullptr, *aux = _get_ptr(val);
		insert(root, aux, pos+1);
	}

	void erase(int pos)
	{
		erase(root, pos+1);
	}

	Node& kth(int pos)
	{
		return kth(root, pos+1);
	}

	friend ostream& operator<<(ostream& out, Treap const& tp)
	{
		if (!tp.root) return out;
		out << *tp.root;
		return out;
	}

	Treap()
	{
		aux_new.resize(1'000'000);
		root = nullptr;
	}
};

class Timer {
public:
    Timer(const std::string& name) : name_(name) {
        start_ = std::chrono::steady_clock::now();
    }

    Timer() : Timer("") {}

    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
    Timer(Timer&&) = delete;
    Timer& operator=(Timer&&) = delete;

    ~Timer() {
        auto dif = std::chrono::steady_clock::now() - start_;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dif);
        if (!name_.empty()) {
            std::cerr << "[" << name_ << "] ";
        }
        std::cerr << ms.count() << " ms\n";
    }

private:
    std::string name_;
    std::chrono::steady_clock::time_point start_;
};

struct Query {
	enum class Op{
		INSERT,
		ERASE,
		QUERY,
	} opt;
	// Op opt;
	int pos, val;
};

vector<Query> gen_bench(int n, int p_insert, int p_erase, int p_query) {
	vector<Query> v(n);

	mt19937 rg{13};

	uniform_int_distribution<int> roll(0, 99);

	int num = 0;

	auto f = [&num, p_insert, p_erase, p_query] (int p) {
		if (num == 0 or p < p_insert) {
			num++;
			return Query::Op::INSERT;
		}
		else if (p < p_insert+p_erase) {
			num--;
			return Query::Op::ERASE;
		}
		else return Query::Op::QUERY;
	};

	for (auto& qr : v) {
		int p = roll(rg);

		int pos = uniform_int_distribution<int>(0, num)(rg);
		int val = rg();
		qr = {f(p), pos, val};
	}

	return v;
}

int64_t run_bench(vector<Query> const& qrs, Treap<int>& tp) {
	Timer timer{"total"};
	int64_t total = 0;
	for (auto const& qr : qrs) {
		if (qr.opt == Query::Op::INSERT) tp.insert(qr.pos, qr.val);
		else if (qr.opt == Query::Op::ERASE) tp.erase(qr.pos);
		else total += tp.kth(qr.pos).val;
	}
	return total;
}

int main()
{
	Treap<int> tp;

	tp.insert(0,3);
	tp.insert(1,1);
	tp.insert(2,2);
	tp.insert(3,5);
	tp.insert(4,7);
	tp.insert(5,6);

	for (auto it : tp) cout << it.val << "\n";

	auto ans = run_bench(gen_bench(1'000'000, 60, 20, 20), tp);

	cout << ans << "\n";
}