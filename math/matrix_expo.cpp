#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

template<int N, int M>
struct Matrix {
    int v[N][M];

    static Matrix ones() {
        Matrix ans{};
        for (int i = 0; i < N; i++) ans.v[i][i] = 1;
        return ans;
    }
};

template<int N, int M, int P>
Matrix<N, P> operator*(Matrix<N, M> const& a, Matrix<M, P> const& b) {
    Matrix<N, P> ans{};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            for (int k = 0; k  < M; k++) {
                add(ans.v[i][j], (ll)a.v[i][k] * b.v[k][j] % mod);
            }
        }
    }

    return ans;
}

template<int N>
Matrix<N, N> fexp(Matrix<N, N> a, ll b) {
    auto ans = Matrix<N, N>::ones();
    while (b) {
        if (b&1) ans = ans*a;
        a = a*a;
        b /= 2;
    }
    return ans;
}

template<int N>
Matrix<N, N> coeff(vector<int> const& c) {
    Matrix<N, N> ans{};
    for (int i = 0; i < N-1; i++) {
        ans.v[i+1][i] = 1;
    }
    for (int i = 0; i < N; i++) {
        ans.v[0][i] = c[i];
    }
    return ans;
}
