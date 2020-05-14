#include <tuple>

using namespace std;

template<typename T>
tuple<int, int> brent(T const& v) {
    int power = 1;
    int lam = 1;
    auto tortoise = v, hare = next(v);

    while (tortoise != hare) {
        if (power == lam) {
            tortoise = hare;
            power *= 2;
            lam = 0;
        }
        hare = next(hare);
        lam++;
    }

    int it = 0;
    tortoise = hare = v;
    for (int i = 0; i < lam; i++) {
        hare = next(hare);
    }
    // now hare has walked lambda distance

    int mu = 0;
    tortoise = v;
    while (tortoise != hare) {
        tortoise = next(tortoise);
        hare = next(hare);
        mu++;
    }
    // hare has walked lambda+mu and 
    // tortoise has walked mu
    // they meet at start of cycle

    // lenght outside of cycle and cycle lenght
    return {mu, lam};
}
