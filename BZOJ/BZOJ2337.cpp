/**************************************************************
 * Problem: BZOJ2337
 * Author: Rqy
 * Date: 2018 Feb 22
 * Algorithm: 高消
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 105;
const int M = 10005;
double A[N][N];
int n;
inline double abs(double x) { return x < 0 ? -x : x; }
double solve() {
  for (int i = 1; i <= n; ++i) {
    int j = i;
    for (int k = i + 1; k <= n; ++k) if (abs(A[k][i]) > abs(A[j][i])) j = k;
    for (int k = i; k <= n + 1; ++k) std::swap(A[i][k], A[j][k]);
    for (int k = n + 1; k >= i; --k)
      A[i][k] /= A[i][i];
    for (int j = i + 1; j <= n; ++j)
      for (int k = n + 1; k >= i; --k)
        A[j][k] -= A[i][k] * A[j][i];
  }
  for (int i = n; i; --i)
    for (int j = i - 1; j; --j)
      A[j][n + 1] -= A[j][i] * A[i][n + 1];
  return A[1][n + 1];
}
int u[M], v[M], w[M], deg[N];
int main() {
  int m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d", &u[i], &v[i], &w[i]);
    ++deg[u[i]];
    if (u[i] != v[i]) ++deg[v[i]];
  }
  double ans = .0;
  for (int i = 0; i < 16; ++i) {
    std::fill(A[0], A[n], .0);
    for (int j = 1; j <= n; ++j) A[j][j] = 1.0;
    for (int j = 0; j < m; ++j) {
      if ((w[j] >> i) & 1) {
        // f[u] += (1 - f[v]) / d[u]
        A[u[j]][v[j]] += 1.0 / deg[u[j]];
        A[u[j]][n + 1] += 1.0 / deg[u[j]];
        if (u[j] != v[j]) {
          A[v[j]][u[j]] += 1.0 / deg[v[j]];
          A[v[j]][n + 1] += 1.0 / deg[v[j]];
        }
      } else {
        // f[u] += f[v] / d[u]
        A[u[j]][v[j]] -= 1.0 / deg[u[j]];
        if (u[j] != v[j]) A[v[j]][u[j]] -= 1.0 / deg[v[j]];
      }
    }
    std::fill(A[n], A[n + 1], .0);
    A[n][n] = 1.0;
    ans += solve() * (1 << i);
  }
  printf("%.3lf\n", ans);
  return 0;
}
