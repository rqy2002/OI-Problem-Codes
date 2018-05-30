#include <algorithm>
#include <cstdio>
typedef long long LL;
const LL INF = 1000000000000000LL;
const int N = 105;
LL d[N][N], C[N][N];
int main() {
  int n, m;
  std::fill(d[0], d[N], INF);
  std::fill(C[0], C[N], 1);
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    d[i][i] = 0;
  while (m--) {
    int x, y;
    scanf("%d%d", &x, &y);
    scanf("%lld", &d[x][y]);
    d[y][x] = d[x][y];
  }
  for (int k = 1; k <= n; ++k)
    for (int i = 1; i <= n; ++i) if (i != k)
      for (int j = 1; j <= n; ++j) if (j != i && j != k) {
        if (d[i][j] > d[i][k] + d[k][j]) {
          d[i][j] = d[i][k] + d[k][j];
          C[i][j] = C[i][k] * C[k][j];
        } else if (d[i][j] == d[i][k] + d[k][j])
          C[i][j] += C[i][k] * C[k][j];
      }
  for (int v = 1; v <= n; ++v) {
    double I = .0;
    for (int i = 1; i <= n; ++i) if (v != i)
      for (int j = 1; j <= n; ++j) if (v != j)
        if (d[i][v] + d[v][j] == d[i][j])
          I += (double)(C[i][v] * C[v][j]) / C[i][j];
    printf("%.3lf\n", I);
  }
  return 0;
}
