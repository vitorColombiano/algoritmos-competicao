import sys

MOD = 10**6

def mat_mult(A, B):
    return [
        [(A[0][0]*B[0][0] + A[0][1]*B[1][0]) % MOD,
         (A[0][0]*B[0][1] + A[0][1]*B[1][1]) % MOD],

        [(A[1][0]*B[0][0] + A[1][1]*B[1][0]) % MOD,
         (A[1][0]*B[0][1] + A[1][1]*B[1][1]) % MOD]
    ]

def mat_pow(M, e):
    R = [[1,0],[0,1]]  # identidade
    while e > 0:
        if e & 1:
            R = mat_mult(R, M)
        M = mat_mult(M, M)
        e >>= 1
    return R

def solve(N, K, L):
    n = N // 5
    K %= MOD
    L %= MOD

    if n == 0:
        return 1
    if n == 1:
        return K

    M = [[K, L],
         [1, 0]]

    P = mat_pow(M, n-1)

    f1 = K
    f0 = 1

    fn = (P[0][0] * f1 + P[0][1] * f0) % MOD
    return fn

for line in sys.stdin:
    if not line.strip():
        continue
    N, K, L = map(int, line.split())
    print(f"{solve(N, K, L):06d}")
