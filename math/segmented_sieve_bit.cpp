#include <bits/stdc++.h>

#pragma GCC optimize("O3","unroll-loops")

using namespace std;

uint32_t const sieve_size = 1<<20;

vector<uint64_t> solve(uint64_t l, uint64_t r) {
	static const int64_t unset_bit[16] = {
	  ~(1 << 0), ~(1 << 0),
	  ~(1 << 1), ~(1 << 1),
	  ~(1 << 2), ~(1 << 2),
	  ~(1 << 3), ~(1 << 3),
	  ~(1 << 4), ~(1 << 4),
	  ~(1 << 5), ~(1 << 5),
	  ~(1 << 6), ~(1 << 6),
	  ~(1 << 7), ~(1 << 7)
	};

	uint64_t i = 3, s = 3, n = std::max(l|1, 3ul);
	uint64_t sqt = std::sqrt(r);

	vector<char> sieve(sieve_size), is_prime(sqt+1, true);
	vector<uint64_t> primes, mult;

	vector<uint64_t> result;

	if (l <= 2 and r > 2) result.push_back(2);

	for (; i*i < l; i += 2)
		if (is_prime[i])
			for (uint64_t j = i*i; j < sqt; j += 2*i)
				is_prime[j] = false;

	for (; s*s < l; s += 2) {
		if (is_prime[s]) {
			primes.push_back(s);
			uint64_t nxt = ((l-1)/s+1)*s;
			if (nxt == s) nxt += s;
			if (nxt%2 == 0) nxt += s;
			mult.push_back(nxt-l);
		}
	}

	for (uint64_t low = l; low < r; low += sieve_size) {
		fill(sieve.begin(), sieve.end(), 0xff);
		uint64_t high = min(r, low+sieve_size);

		for (; i*i < high; i += 2)
			if (is_prime[i])
				for (uint64_t j = i*i; j < sqt; j += 2*i)
					is_prime[j] = false;

		for (; s*s < high; s += 2) {
			if (is_prime[s]) {
				primes.push_back(s);
				mult.push_back(s*s - low);
			}
		}

		for (size_t j = 0; j < primes.size(); j++) {
			uint64_t k = mult[j];
			for (uint64_t prime = primes[j]*2; k < sieve_size; k += prime)
				sieve[k>>4] &= unset_bit[k&15];
			mult[j] = k-sieve_size;
		}

		for (; n < high; n += 2)
			if (sieve[(n-low)>>4]&~unset_bit[(n-low)&15])
				result.push_back(n);
	}

	return result;
}

int main() {
	uint64_t l, r;
	cin >> l >> r;

	auto ans = solve(l, r+1);

	for (auto p : ans) cout << p << "\n";
}
