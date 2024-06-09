import numpy as np

# Function to generate randomized Halton sequence
#
# Algorithm taken from:
#      A. B. Owen. A randomized halton algorithm in r. Arxiv, 6 2017. URL http:
#      arxiv.org/abs/1706.02808.
def rhalton(N, dim, seed=12345, skip=0):
    np.random.seed(seed)
    primes = np.array((2, 3, 5, 7, 11, 13, 17, 19, 23, 29), dtype=np.int64)
    halton = np.zeros((N, dim), dtype=np.float64)

    for D in range(dim):
        b = primes[D]
        ind = np.arange(skip, skip + N, dtype=np.int64)
        b2r = 1 / b
        ans = np.zeros(ind.shape, dtype=np.float64)
        res = ind.copy()
        while (1.0 - b2r) < 1.0:
            dig = np.mod(res, b)
            perm = np.random.permutation(b)
            pdig = perm[dig]
            ans = ans + pdig.astype(np.float64) * b2r
            print(pdig)
            b2r = b2r / np.float64(b)
            res = ((res - dig) / b).astype(np.int64)
        halton[:, D] = ans

    return halton

if __name__ == "__main__":
    print(rhalton(5,2))