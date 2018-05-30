#include <algorithm>
#include <cstdio>
using std::min;
const int INF = 100000000;
const int N = 6050, M = 30050;
int f[2][M];
int main() {
  int n, m, t1, t2, t3;
  scanf("%d", &n);
  m = 0;
  int *x = f[0], *y = f[1];
  for (int i = 0; i < n; ++i, std::swap(x, y)) {
    scanf("%d%d%d", &t1, &t2, &t3);
    std::fill(y, y + M, INF);
    for (int j = 0; j <= m; ++j) {
      if (t1) y[j + t1] = min(y[j + t1], x[j]);
      if (t2) y[j] = min(y[j], x[j] + t2);
      if (t3) y[j + t3] = min(y[j + t3], x[j] + t3);
    }
    m += std::max(t1, t3);
  }
  int ans = INF;
  for (int i = 0; i <= m; ++i)
    ans = min(ans, std::max(x[i], i));
  printf("%d\n", ans);
  return 0;
}
