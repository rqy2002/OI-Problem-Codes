/**************************************************************
 * Problem: BZOJ1224
 * Author: Rqy
 * Date: 2018 Feb 25
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int M = 105;
const double eps = 1e-10;
inline int sgn(double x) {
  if (x < -eps) return -1;
  if (x > eps) return 1;
  return 0;
}
int m;
double sum[M];
int dfs(int x, int n, double S) {
  if (sgn(S - (sum[x + n - 1] - sum[x - 1])) > 0) return 0;
  if (sgn(S - (sum[m] - sum[m - n])) < 0) return 0;
  if (!n) return 1;
  if (x > m) return 0;
  return dfs(x + 1, n, S) + dfs(x + 1, n - 1, S - 1.0 / x);
}
int main() {
  int n, x, y;
  scanf("%d%d%d%d", &n, &m, &x, &y);
  for (int i = 1; i <= 2 * m; ++i) sum[i] = sum[i - 1] + 1.0 / i;
  printf("%d\n", dfs(1, n, (double)x / y));
  return 0;
}
