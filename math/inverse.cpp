#include <iostream>
#include <vector>

#include <gmpxx.h>

template<typename T>
void equalize_row(std::vector<T> const& A, std::vector<T> &B, T ratio) {
    int32_t n = A.size();
    for (int32_t i = 0; i < n; i++) {
        B[i] += ratio*A[i];
    }
}

template<typename T>
void divide_row(std::vector<T> &A, T ratio) {
    for (T& num : A) {
        num /= ratio;
    }
}

template<typename T>
void print_matrix(std::vector<T> const& A) {
    for (auto& row : A) {
        for (auto& x : row) {
            std::cout << x << " ";
        }
        std::cout << "\n";
    }
}

template<typename T>
std::vector<std::vector<T>> inverse(std::vector<std::vector<T>> M) {
    int32_t n = M.size();
    
    auto R = std::vector<std::vector<T>>(n, std::vector<T>(n));
    for (int32_t i = 0; i < n; i++) {
        R[i][i] = T(1);
    }

    for (int32_t i = 0; i < n; i++) {
        int32_t best = i;
        for (int32_t j = i+1; j < n; j++) {
            if (abs(M[best][i]) < abs(M[j][i])) {
                best = j;
            }
        }
        if (best != i) {
            std::swap(M[i], M[best]);
            std::swap(R[i], R[best]);
        }

        divide_row<T>(R[i], M[i][i]);
        divide_row<T>(M[i], M[i][i]);

        for (int32_t j = i+1; j < n; j++) {
            T ratio = -M[j][i];
            equalize_row<T>(M[i], M[j], ratio);
            equalize_row<T>(R[i], R[j], ratio);
        }
    }

    for (int32_t i = n-1; i > 0; i--) {
        for (int32_t j = i-1; j >= 0; j--) {
            equalize_row<T>(R[i], R[j], -M[j][i]);
            equalize_row<T>(M[i], M[j], -M[j][i]);
        }
    }

    return R;
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

    auto A = inverse<rational>(M);

    print_matrix(A);
}