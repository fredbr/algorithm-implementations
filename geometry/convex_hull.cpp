#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

template <typename T>
struct Point
{
	T x, y;

	Point<T> operator+(Point<T> const& rhs) const
	{
		return {x+rhs.x, y+rhs.y};
	}

	Point<T> operator-(Point<T> const& rhs) const
	{
		return {x-rhs.x, y-rhs.y};
	}

	T operator*(Point<T> const& rhs) const
	{
		return x*rhs.x + y*rhs.y;
	}

	T operator^(Point<T> const& rhs) const
	{
		return x*rhs.y - y*rhs.x;
	}

	bool operator<(Point<T> const& rhs) const
	{
		if (x == rhs.x) return y < rhs.y;
		return x < rhs.x;
	}
};

vector<Point<ll>> points;

int main()
{
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		ll x, y;
		cin >> x >> y;

		points.push_back({x, y});
	}

	sort(points.begin(), points.end());

	vector<Point<ll>> up, down;

	for (Point<ll> pt : points) {
		while (up.size() >= 2 and
			  ((pt-up.back())^(*(up.end()-2)-up.back())) > 0)
			up.pop_back();
		while (down.size() >= 2 and
			  ((pt-down.back())^(*(down.end()-2)-down.back())) < 0)
			down.pop_back();
		up.push_back(pt);
		down.push_back(pt);
	}

	cout << "Up hull\n";
	for (Point<ll> const& pt : up)
		cout << pt.x << " " << pt.y << "\n";

	cout << "Down hull\n";
	for (Point<ll> const& pt : down)
		cout << pt.x << " " << pt.y << "\n";
}
