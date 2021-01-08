#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INIT_MATRIX(K, init)                                                   \
  K = (long **)malloc(sizeof(long *) * n);                                     \
  for (long i = 0; i < n; i++) {                                               \
    K[i] = (long *)malloc(sizeof(long) * n);                                   \
    for (long j = 0; j < n; j++) {                                             \
      K[i][j] = init;                                                          \
    }                                                                          \
  }

bool isPow2(long n) { return (n & (n - 1)) == 0; }

long getNextPow2(long n) {
  for (ulong power = 1; power > 0; power <<= 1) {
    if (power > n)
      return power;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    fprintf(stderr, "Uso: %s N", argv[0]);
    return 1;
  }
  int n = atol(argv[1]);

  long **A, **B, **C;
#ifdef IMPLEMENT_1
  // Estándar
  INIT_MATRIX(A, rand());
  INIT_MATRIX(B, rand());
  INIT_MATRIX(C, 0);

  for (long i = 0; i < n; i++)
    for (long j = 0; j < n; j++)
      for (long k = 0; k < n; k++)
        C[i][j] += A[i][k] + B[k][j];
#elif defined IMPLEMENT_2
  // Strassen
  int n2 = n;
  if (!isPow2(n))
    n2 = getNextPow2(n);
  INIT_MATRIX(A, (j > n || i > n) ? rand() : 0);
  INIT_MATRIX(B, (j > n || i > n) ? rand() : 0);
  INIT_MATRIX(C, (j > n || i > n) ? rand() : 0);
#else
#endif
  return 0;
}
