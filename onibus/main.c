#include <stdio.h>
#include <stdint.h>

#define MOD 1000000

// Estrutura para matriz 2x2
typedef struct {
    uint64_t m[2][2];
} Matrix;

// Multiplicação de matrizes 2x2 com módulo
Matrix matrix_mult(Matrix a, Matrix b) {
    Matrix result;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result.m[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                result.m[i][j] = (result.m[i][j] + (a.m[i][k] * b.m[k][j]) % MOD) % MOD;
            }
        }
    }
    return result;
}

// Exponenciação de matriz
Matrix matrix_pow(Matrix base, uint64_t exp) {
    Matrix result = {{{1, 0}, {0, 1}}}; // Matriz identidade

    while (exp > 0) {
        if (exp & 1) {
            result = matrix_mult(result, base);
        }
        base = matrix_mult(base, base);
        exp >>= 1;
    }
    return result;
}

uint64_t solve(uint64_t N, uint64_t K, uint64_t L) {
    uint64_t n = N / 5;

    if (n == 0) return 1;
    if (n == 1) return K % MOD;

    // Matriz de transformação [[K, L], [1, 0]]
    Matrix trans;
    trans.m[0][0] = K % MOD;
    trans.m[0][1] = L % MOD;
    trans.m[1][0] = 1;
    trans.m[1][1] = 0;

    // Elevar a matriz à potência (n-1)
    Matrix result = matrix_pow(trans, n - 1);

    uint64_t ans = ((result.m[0][0] * (K % MOD)) % MOD + result.m[0][1]) % MOD;

    return ans;
}

int main() {
    uint64_t N, K, L;
    while (scanf("%lu %lu %lu", &N, &K, &L) == 3) {
        uint64_t result = solve(N, K, L);
        printf("%06lu\n", result);
    }
    return 0;
}
