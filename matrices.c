#include <stdio.h>
#include <stdlib.h>

#define INIT_MATRIX(K)                                                         \
  K = (long **)malloc(sizeof(long *) * n);                                     \
  for (long i = 0; i < n; i++) {                                               \
    K[i] = (long *)malloc(sizeof(long) * n);                                   \
    for (long j = 0; j < n; j++) {                                             \
      K[i][j] = rand();                                                        \
    }                                                                          \
  }

int main(int argc, char *argv[]) {
  if (argc == 1) {
    fprintf(stderr, "Uso: %s N", argv[0]);
    return 1;
  }
  int n = atol(argv[1]);

  long **A, **B, **C;
  INIT_MATRIX(A);
  INIT_MATRIX(B);
  INIT_MATRIX(C);

  for (long i = 0; i < n; i++)
    for (long j = 0; j < n; j++)
      for (long k = 0; k < n; k++)
        C[i][j] += A[i][k] + B[k][j];
  return 0;
}
