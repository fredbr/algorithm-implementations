#include <bits/stdc++.h>

template <typename T>
class Seg {
private:
	using join_t = std::function<T(T const&, T const&)>;
	using fix_t = std::function<void(T &, T const&)>;

	int n;
	join_t const join;
	fix_t const fix = [] (T& a, T const& b) { a = b;};

	std::vector<T> tree;

	template<typename Iter>
	T const& build(int no, int l, int r, Iter const& v)
	{
		if (l == r)
			return tree[no] = v[l];

		int m = (l+r)/2;

		build(no*2+1, l, m, v);
		build(no*2+2, m+1, r, v);

		tree[no] = join(build(no*2+1, l, m, v),
		                build(no*2+2, m+1, r, v));

		return tree[no];
	}

	void upd(int no, int l, int r, int pos, T val)
	{
		if (l == r) {
			fix(tree[no], val);
			return;
		}

		int m = (l+r)/2;

		if (pos <= m) upd(no*2+1, l, m, pos, val);
		else upd(no*2+2, m+1, r, pos, val);

		tree[no] = join(tree[no*2+1], tree[no*2+2]);
	}

	T get(int no, int l, int r, int a, int b)
	{
		if (a <= l and r <= b) return tree[no];

		int m = (l+r)/2;
		
		if (b <= m) return get(no*2+1, l, m, a, b);
		if (a > m) return get(no*2+2, m+1, r, a, b);

		return join(get(no*2+1, l, m, a, b),
		            get(no*2+2, m+1, r, a, b));
	}

public:
	Seg(int n_, join_t op_) :
		join(op_), n(n_), tree(n*4) {};

	Seg(int n_,	join_t op_,	fix_t fix_) :
		join(op_), n(n_), fix(fix_), tree(n*4) {};

	Seg(std::vector<T> const& v, join_t op_) :
		join(op_), n(v.size()), tree(v.size()*4)
	{
		build(0, 0, n-1, v.data());
	}

	Seg(std::vector<T> const& v, join_t op_, fix_t fix_) :
		join(op_), n(v.size()), fix(fix_), tree(v.size()*4)
	{
		build(0, 0, n-1, v.data());
	}

	template<typename Iter>
	Seg(Iter const& begin, Iter const& end, join_t op_) :
		join(op_), n(end-begin), tree(4*(end-begin))
	{
		build(0, 0, n-1, begin);
	}

	template<typename Iter>
	Seg(Iter const& begin, Iter const& end, join_t op_, fix_t fix_) :
		join(op_), n(end-begin), fix(fix_), tree(4*(end-begin))
	{
		build(0, 0, n-1, begin);
	}

	void upd(int pos, T val)
	{
		upd(0, 0, n-1, pos, val);
	}

	T get(int l, int r)
	{
		return get(0, 0, n-1, l, r);
	}
};

// example (Baldes - OBI2018)
namespace Problem
{
	struct Node
	{
		int mini, maxi, ans;
	};

	Node join(Node const& a, Node const& b)
	{
		Node ans;
		ans.mini = std::min(a.mini, b.mini);
		ans.maxi = std::max(a.maxi, b.maxi);
		ans.ans = std::max({a.ans, b.ans,
		                    abs(a.maxi-b.mini),
		                    abs(b.maxi-a.mini)});
		return ans;
	}

	void fix(Node& a, Node const& b)
	{
		a.mini = std::min(a.mini, b.mini);
		a.maxi = std::max(a.maxi, b.maxi);
	}
}

int main()
{
	int n, q;
	std::cin >> n >> q;

	std::vector<Problem::Node> v(n);
	for (int i = 0; i < n; i++)
		std::cin >> v[i].mini, v[i].maxi = v[i].mini;

	auto sg = Seg<Problem::Node>(v.begin(), v.end(), Problem::join, Problem::fix);

	while (q--) {

		int op;
		std::cin >> op;

		if (op == 1) {
			int val, pos;
			std::cin >> val >> pos;

			sg.upd(pos-1, {val, val, 0});
		}
		else {
			int l, r;
			std::cin >> l >> r;

			std::cout << sg.get(l-1, r-1).ans << "\n"; 
		}
	}
}