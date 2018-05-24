/**************************************************************
 * Problem: Luogu P1076
 * Author: Rqy
 * Date: 2018 Feb 09
 * Algorithm: NONE
**************************************************************/
#include <cstdio>
const int N = 10000;
const int M = 100;
const int mod = 20123;
bool B[N][M];
int x[N][M], g[N];
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i)
    for (int j = 0, y; j < m; ++j) {
      scanf("%d%d", &y, &x[i][j]);
      g[i] += B[i][j] = y;
    }
  int p, ans = 0;
  scanf("%d", &p);
  for (int i = 0; i < n; ++i) {
    ans = (ans + x[i][p]) % mod;
    for (int j = (x[i][p] - 1) % g[i] + 1; j;)
      if (j -= B[i][p]) (++p) %= m;
  }
  printf("%d\n", ans);
  return 0;
}
