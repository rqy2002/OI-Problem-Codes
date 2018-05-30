#include <cstdio>
#include <cstring>
int n, m, kk;
int fail[30];
int p[30];
void getfail() {
  fail[0] = fail[1] = 0;
  int i, j;
  for (i = 1; i < m; ++i) {
    j = fail[i];
    while (j && p[i] != p[j]) j = fail[j];
    fail[i + 1] = p[i] == p[j] ? j + 1 : 0;
  }
}
typedef int matrix[100][100];
matrix d;
void mul(matrix a, matrix b, matrix c, int siz) {
  memset(d, 0, sizeof d);
  for (int i = 0; i < siz; ++i)
    for (int k = 0; k < siz; ++k)
      for (int j = 0; j < siz; ++j)
        d[i][j] = (d[i][j] + a[i][k] * b[k][j]) % kk;
  memcpy(c, d, sizeof d);
}
matrix A, B;
int main() {
  // freopen("bzoj_1009.in", "r", stdin);
  // freopen("bzoj_1009.out", "w", stdout);
  scanf("%d%d%d", &n, &m, &kk);
  for (int i = 0; i < m; ++i) scanf("%1d", &p[i]);
  getfail();
  memset(A, 0, sizeof A);
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < 10; ++j) {
      int k = i;
      while (k && p[k] != j) k = fail[k];
      ++A[i][p[k] == j ? k + 1 : k];
    }
  if (!n) {
    printf("1");
    return 0;
  }
  memcpy(B, A, sizeof A);
  for (--n; n; n >>= 1, mul(A, A, A, m))
    if (n & 1) mul(A, B, B, m);
  int ans = 0;
  for (int i = 0; i < m; ++i) ans = (ans + B[0][i]) % kk;
  printf("%d", ans);
  return 0;
}
