#include <iostream>
#include <vector>

#include <gmpxx.h>

template<typename T>
void divide_row(std::vector<T> &A, T ratio) {
    for (auto& num : A) {
        num /= ratio;
    }
}

template<typename T>
void equalize_row(std::vector<T> const& A, std::vector<T> &B, T ratio) {
    int32_t n = A.size();
    for (int32_t i = 0; i < n; i++) {
        B[i] += A[i]*ratio;
    }
}

template<typename T>
void print_matrix(std::vector<std::vector<T>> const& A) {
    for (auto const& row : A) {
        for (auto const& num : row) {
            std::cout << num << " ";
        }
        std::cout << "\n";
    }
}

template<typename T>
T determinant(std::vector<std::vector<T>> A) {
    T ans = 1;

    int32_t n = A.size();
    for (int32_t i = 0; i < n; i++) {
        int32_t best = i;

        for (int32_t j = i+1; j < n; j++) {
            if (abs(A[best][i]) < abs(A[j][i])) {
                best = j;
            }
        }

        if (best != i) {
            ans = -ans;
            std::swap(A[best], A[i]);
        }

        if (A[i][i] == T()) {
            return T();
        }

        ans *= T(A[i][i]);
        divide_row<T>(A[i], A[i][i]);

        for (int32_t j = i+1; j < n; j++) {
            equalize_row<T>(A[i], A[j], -A[j][i]);
        }
    }

    for (int32_t i = 0; i < n; i++) {
        ans *= A[i][i];
    }

    return ans;
}

int main() {
    using rational = mpq_class;

    int32_t n;
    std::cin >> n;

    auto M = std::vector<std::vector<rational>>(n, std::vector<rational>(n));
    for (auto& row : M) {
        for (auto& x : row) {
            std::cin >> x;
        }
    }

    auto x = determinant<rational>(M);

    std::cout << x << "\n";
}