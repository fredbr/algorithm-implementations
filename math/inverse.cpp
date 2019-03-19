#include <bits/stdc++.h>

template<typename T>
void equalize_row(std::vector<T> const& A, std::vector<T> &B, T ratio) {
    int32_t n = A.size();
    for (int32_t i = 0; i < n; i++) {
        B[i] += ratio*A[i];
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

    for (int32_t i = 0; i+1 < n; i++) {
        T cut_base = M[i][i];
        for (int32_t j = i+1; j < n; j++) {
            T ratio = - M[j][i] / cut_base;
            equalize_row(M[i], M[j], ratio);
            equalize_row(R[i], R[j], ratio);
        }
    }

    for (int32_t i = n-1; i > 0; i--) {
        T cut_base = M[i][i];
        for (int32_t j = i-1; j >= 0; j--) {
            T ratio = - M[j][i] / cut_base;
            equalize_row(M[i], M[j], ratio);
            equalize_row(R[i], R[j], ratio);
        }
    }

    print_matrix(M);
    for (int32_t i = 0; i < n; i++) {
        if (M[i][i] != T(1)) {
            T ratio = T(1) / M[i][i] - T(1);
            equalize_row(R[i], R[i], ratio);
            equalize_row(M[i], M[i], ratio);
        }
    }
    print_matrix(M);
    return R;
}

int main() {
    int32_t n;
    std::cin >> n;

    auto M = std::vector<std::vector<double>>(n, std::vector<double>(n));
    for (auto& row : M) {
        for (auto& x : row) {
            std::cin >> x;
        }
    }

    auto ans = inverse(M);

    print_matrix(ans);
}