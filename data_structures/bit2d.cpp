#include <bits/stdc++.h>

using namespace std;

template <typename T, int size>
struct Bit2d
{
	T b[size][size];

	void add(int x, int y, T d)
	{
		for (int i = x; i < size; i += i&-i) {
			for (int j = y; j < size; j += j&-j)
				b[i][j] += d;
		}
	}

	T get(int x, int y)
	{
		T ans = 0;
		for (int i = x; i; i -= i&-i) {
			for (int j = y; j; j -= j&-j) {
				ans += b[i][j];
			}
		}
	}
};

int main()
{

}