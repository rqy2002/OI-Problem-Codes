/************************************************************** 
 * Problem: Luogu P3317
 * Author: Rqy
 * Date: 2017 Dec 23
 * Algorithm: 矩阵树定理,高斯消元
**************************************************************/
#include <algorithm>
#include <cmath>
#include <cstdio>
const int N = 55;
const double eps = 1e-7;
double A[N][N];
double calc(int n) {
  for (int i = 0; i < n; ++i) {
    int c = i;
    for (int j = i + 1; j < n; ++j)
      if (fabs(A[j][i]) > fabs(A[c][i])) c = j;
    if (fabs(A[c][i]) < eps) return .0;
    for (int j = i; j < n; ++j)
      std::swap(A[i][j], A[c][j]);
    for (int j = i + 1; j < n; ++j)
      for (int k = n - 1; k >= i; --k)
        A[j][k] -= A[j][i] / A[i][i] * A[i][k];
  }
  double ans = 1.0;
  for (int i = 0; i < n; ++i)
    ans *= A[i][i];
  return ans;
}
int main() {
  int n;
  scanf("%d", &n);
  double t = 1.0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) {
      double x;
      scanf("%lf", &x);
      if (i != j) {
        if (fabs(x - 1.0) < eps) x = 1.0 - eps;
        if (fabs(x) < eps) x = eps;
        if (i < j) t *= 1 - x;
        x = x / (1 - x);
        A[i][i] -= (A[i][j] = x);
      }
    }
  printf("%lf\n", fabs(calc(n - 1) * t));
  return 0;
}

