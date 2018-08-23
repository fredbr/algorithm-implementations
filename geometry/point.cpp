#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

template <typename T>
struct Point
{
	T x, y;

	Point<T> operator+(Point<T> const& rhs)
	{
		return {x+rhs.x, y+rhs.y};
	}

	Point<T> operator-(Point<T> const& rhs)
	{
		return {x-rhs.x, y-rhs.y};
	}

	T operator*(Point<T> const& rhs)
	{
		return x*rhs.x + y*rhs.y;
	}

	T operator^(Point<T> const& rhs)
	{
		return x*rhs.y - y*rhs.x;
	}
};

int main()
{
	Point<ll> a, b;
	Point<double> aa, bb;	
}