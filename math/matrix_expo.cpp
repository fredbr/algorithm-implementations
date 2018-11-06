#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

template <int n, int m>
struct Matrix {
	ll v[n][m];

	static Matrix<n, m> ones() {
		Matrix<n, m> ans{};
		for (int i = 0; i < n; i++)
			ans.v[i][i] = 1;
		return ans;
	}
};

ll const mod = 1e9+7;

template <int n, int m, int p>
Matrix<n, p> operator*(Matrix<n, m> const& a, Matrix<m, p> const& b)
{
	auto ans = Matrix<n, p>{};
	for (int i = 0; i < n; i++)
		for (int j = 0; j < p; j++)
			for (int k = 0; k < m; k++)
				ans.v[i][j] = (ans.v[i][j] + a.v[i][k]*b.v[k][j])%mod;
	return ans;
}

template <int n>
Matrix<n, n> power(Matrix<n, n> a, ll b)
{
	auto ans = Matrix<n, n>::ones();
	while (b) {
		if (b&1) ans = ans*a;
		a = a*a;
		b /= 2;
	}
	return ans;
}

template <int n, int m>
ostream& operator<< (ostream& out, Matrix<n, m> const& mat)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			out << mat.v[i][j] << " ";
		out << "\n";
	}
	return out;
}

// Muro (OBI - 2018)
int main()
{
	Matrix<3, 1> base = {1, 1, 5};

	ll n;
	cin >> n;

	Matrix<3,3> exp = {0, 1, 0, 
	                   0, 0, 1,
	                   2, 4, 1};

	auto ans = power(exp, n)*base;

	cout << ans.v[0][0] << "\n";
}