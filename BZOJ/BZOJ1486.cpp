#include <algorithm>
#include <cstdio>
const int N = 3050;
const int M = 10050;
const double INF = 1e12;
double _F[2][N], Fn[N], w[M], maxv[N];
int u[M], v[M];
int main() {
  int n, m, i, j;
  scanf("%d%d", &n, &m);
  for (i = 0; i < m; ++i)
    scanf("%d%d%lf", &u[i], &v[i], &w[i]);
  double *F = _F[0], *G = _F[1];
  for (i = 1; i <= n; ++i)
    G[i] = 0;
  for (i = 0; i < n; ++i, std::swap(F, G)) {
    for (j = 1; j <= n; ++j) F[j] = INF;
    for (j = 0; j < m; ++j)
      F[v[j]] = std::min(F[v[j]], G[u[j]] + w[j]);
  }
  for (i = 1; i <= n; ++i) Fn[i] = G[i];
  double ans = 1e7;
  for (i = 1; i <= n; ++i)
    maxv[i] = Fn[i] / n, G[i] = 0;
  for (i = 0; i < n; ++i, std::swap(F, G)) {
    for (j = 1; j <= n; ++j) F[j] = INF;
    for (j = 0; j < m; ++j)
      F[v[j]] = std::min(F[v[j]], G[u[j]] + w[j]);
    for (j = 1; j <= n; ++j) maxv[j] = std::max(maxv[j], (Fn[j] - F[j]) / (n - i - 1));
  }
  for (i = 1; i <= n; ++i) if (Fn[i] < 1e11) ans = std::min(ans, maxv[i]);
  printf("%.8lf\n", ans);
  return 0;
}
