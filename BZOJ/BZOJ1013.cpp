#include <algorithm>
#include <cstdio>
const int N = 15;
double A[N][N];
void gauss(int n) {
  for (int i = 0; i < n; ++i) {
    int k = i;
    for (int j = i + 1; j < n; ++j) 
      if (A[j][i] > A[k][i])
        k = j;
    for (int j = i; j <= n; ++j)
      std::swap(A[i][j], A[k][j]);
    for (k = i + 1; k < n; ++k)
      for (int j = n; j >= i; --j)
        A[k][j] -= A[i][j] * A[k][i] / A[i][i];
  }
  for (int i = n - 1; ~i; --i) {
    A[i][n] /= A[i][i];
    for (int j = i - 1; ~j; --j)
      A[j][n] -= A[i][n] * A[j][i];
  }
}
double P0[N];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%lf", &P0[i]);
  double x;
  for (int i = 0; i < n; ++i) {
    A[i][n] = .0;
    for (int j = 0; j < n; ++j) {
      scanf("%lf", &x);
      A[i][j] = 2 * (x - P0[j]);
      A[i][n] += x * x - P0[j] * P0[j];
    }
  }
  gauss(n);
  printf("%.3lf", A[0][n]);
  for (int i = 1; i < n; ++i)
    printf(" %.3lf", A[i][n]);
  printf("\n");
  return 0;
}
