/**************************************************************
 * Problem: Luogu P3199
 * Author: Rqy
 * Date: 2017 Dec 23
 * Algorithm: 最小权值回路
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 3050;
const int M = 10050;
const double INF = 1e12;
double F[N][N], w[M];
int u[M], v[M];
int main() {
  int n, m, i, j;
  scanf("%d%d", &n, &m);
  for (i = 0; i < m; ++i)
    scanf("%d%d%lf", &u[i], &v[i], &w[i]);
  for (i = 0; i <= n; ++i)
    for (j = 1; j <= n; ++j)
      F[i][j] = i ? INF : 0;
  for (i = 0; i < n; ++i)
    for (j = 0; j < m; ++j)
      F[i + 1][v[j]] = std::min(F[i + 1][v[j]], F[i][u[j]] + w[j]);
  double ans = 1e7, ans1;
  for (i = 1; i <= n; ++i) if (F[n][i] < 1e11) {
    ans1 = -INF;
    for (j = 0; j < n; ++j)
      ans1 = std::max(ans1, (F[n][i] - F[j][i]) / (n - j));
    ans = std::min(ans, ans1);
  }
  printf("%.8lf\n", ans);
  return 0;
}
