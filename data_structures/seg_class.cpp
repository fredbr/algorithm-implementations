#include <bits/stdc++.h>

template <typename T>
class Seg {
private:
	using op_t = std::function<T(T const&, T const&)>;

	int n;
	op_t const op;
	std::vector<T> tree;

	T const& build(int no, int l, int r, std::vector<T> const& v)
	{
		if (l == r)
			return tree[no] = v[l];

		int m = (l+r)/2;

		build(no*2+1, l, m, v);
		build(no*2+2, m+1, r, v);

		tree[no] = op(build(no*2+1, l, m, v),
		              build(no*2+2, m+1, r, v));

		return tree[no];
	}

	void upd(int no, int l, int r, int pos, T val)
	{
		if (l == r) {
			tree[no] = val;
			return;
		}

		int m = (l+r)/2;

		if (pos <= m) upd(no*2+1, l, m, pos, val);
		else upd(no*2+2, m+1, r, pos, val);

		tree[no] = op(tree[no*2+1], tree[no*2+2]);
	}

	T get(int no, int l, int r, int a, int b)
	{
		if (a <= l and r <= b) return tree[no];

		int m = (l+r)/2;
		
		if (b <= m) return get(no*2+1, l, m, a, b);
		if (a > m) return get(no*2+2, m+1, r, a, b);

		return op(get(no*2+1, l, m, a, b),
		          get(no*2+2, m+1, r, a, b));
	}

public:
	Seg(int n_, op_t op_) :
		op(op_), n(n_)
	{
		tree.resize(n*4);
	}

	Seg(std::vector<T> const& v, op_t op_) :
		op(op_), n(v.size())
	{
		tree.resize(n*4);
		build(0, 0, n-1, v);
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

Seg<int> sg(101010,
			[] (int const& a, int const& b) -> int
                { return std::max(a, b); });

int main()
{
	int n;
	std::cin >> n;

	std::vector<int> v(n);
	for (int i = 0; i < n; i++)
		std::cin >> v[i];

	auto seg = std::make_unique<Seg<int>>
	                            (v, [] (int const& a, int const& b) -> int
		                            { return std::max(a, b); });

	std::cout << seg->get(0, n-1) << "\n";
	std::cout << seg->get(0, 4) << "\n";

	auto seg2 = Seg<int>(v, [] (int const& a, int const& b) -> int
		                            { return std::max(a, b); });
}