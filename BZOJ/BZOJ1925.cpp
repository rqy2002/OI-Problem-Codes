#include <cstdio>
typedef long long LL;
const int N = 5000;
int n, p;
int A[N], B[N];
int C[N];
int main() {
  scanf("%d%d", &n, &p);
  C[0] = 1;
  A[0] = A[1] = 1;
  B[0] = 1;
  B[1] = 0;
  for (int i = 2; i <= n; ++i) {
    A[i] = B[i] = 0;
    for (int j = i - 2; j >= 0; --j)
      B[i] = (B[i] + (LL)B[j] * A[i - j - 1] % p * (j ? C[j] = (C[j] + C[j - 1]) % p : 1)) % p;
    for (int j = i - 2; j; --j)
      A[i] = (A[i] + (LL)A[j] * A[i - j - 1] % p * C[j] % p) % p;
    C[i - 1] = 1;
  }
  printf("%d\n", 2 * (A[n] + B[n]) % p);
}
