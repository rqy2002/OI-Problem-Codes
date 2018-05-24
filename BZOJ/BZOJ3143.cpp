/**************************************************************
 * Problem: BZOJ3143
 * Author: Rqy
 * Date: 2018 Feb 23
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 505;
const int M = 250050;
int n, deg[N], x[M], y[M];
bool map[N][N];
double A[N][N];
double abs(double x) { return x < 0 ? -x : x; }
void solve() {
  for (int i = 1; i <= n; ++i) {
    int j = i;
    for (int k = i + 1; k <= n; ++k) if (abs(A[k][i]) > abs(A[j][i])) j = k;
    for (int k = i; k <= n + 1; ++k) std::swap(A[i][k], A[j][k]);
    for (int j = i + 1; j <= n; ++j)
      for (int k = n + 1; k >= i; --k)
        A[j][k] -= A[i][k] * A[j][i] / A[i][i];
  }
  for (int i = n; i; --i) {
    A[i][n + 1] /= A[i][i];
    for (int j = i - 1; j; --j)
      A[j][n + 1] -= A[i][n + 1] * A[j][i];
  }
}
double p[M];
int main() {
  int m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &x[i], &y[i]);
    map[x[i]][y[i]] = map[y[i]][x[i]] = true;
    ++deg[x[i]]; ++deg[y[i]];
  }
  for (int i = 1; i <= n; ++i) {
    A[i][i] = 1.0;
    if (i != n)
      for (int j = 1; j <= n; ++j) if (i != j && map[i][j])
        A[i][j] = -1.0 / deg[j];
    if (i == 1)
      A[i][n + 1] = 1.0;
  }
  solve();
  for (int i = 0; i < m; ++i)
    p[i] = A[x[i]][n + 1] / deg[x[i]] + A[y[i]][n + 1] / deg[y[i]];
  std::sort(p, p + m);
  double ans = .0;
  for (int i = 0; i < m; ++i)
    ans += p[i] * (m - i);
  printf("%.3lf\n", ans);
  return 0;
}
