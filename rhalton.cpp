#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>

// Function to generate randomized Halton sequence
//
// Algorithm taken from:
//      A. B. Owen. A randomized halton algorithm in r. Arxiv, 6 2017. URL http:
//      arxiv.org/abs/1706.02808.
//
// Results are not idential to Python implementation - the permutation process produces different
// results. My guess is this is due to differences in rng/shuffle implementation.
std::vector<std::vector<double>> rhalton(int N, int dim, unsigned int seed = 12345, int skip = 0) {
    std::vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    std::vector<std::vector<double>> halton(N, std::vector<double>(dim, 0.0));

    std::mt19937 rng(seed);

    for (int D = 0; D < dim; ++D) {
        int b = primes[D];
        std::vector<int> ind(N);
        std::iota(ind.begin(), ind.end(), skip);
        double b2r = 1.0 / b;
        std::vector<double> ans(N, 0.0);
        std::vector<int> res(ind);

        while ((1.0 - b2r) < 1.0) {
            std::vector<int> dig(N);
            // randomaly permute a sequence from skip to skip+N
            std::vector<int> perm(b);
            std::iota(perm.begin(), perm.end(), 0);
            std::shuffle(perm.begin(), perm.end(), rng);

            // compute element wise remainder of division (mod)
            for (int i = 0; i < N; ++i) {
                dig[i] = res[i] % b;
            }

            for (int i = 0; i < N; ++i) {
                ans[i] += perm[dig[i]] * b2r;
                std::cout << perm[dig[i]] << " ";
            }
            std::cout << std::endl;

            b2r /= b;
            for (int i = 0; i < N; ++i) {
                res[i] = (res[i] - dig[i]) / b;
            }
        }

        for (int i = 0; i < N; ++i) {
            halton[i][D] = ans[i];
        }
    }

    return halton;
}

int main() {
    int N = 5; // Number of points
    int dim = 2;  // Number of dimensions
    unsigned int seed = 12345; // Seed for random number generation
    int skip = 0; // Skip initial points

    // Generate the Halton sequence
    std::vector<std::vector<double>> halton = rhalton(N, dim, seed, skip);

    // Print the sequence
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < dim; ++j) {
            std::cout << halton[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
