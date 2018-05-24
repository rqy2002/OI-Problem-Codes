/**************************************************************
 * Problem: BZOJ3208
 * Author: Rqy
 * Date: 2018 Feb 27
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 705;
int h[N][N];
bool mark[N][N];
int f[N][N];
int dfs(int i, int j) {
  if (mark[i][j]) return 0;
  if (f[i][j]) return f[i][j];
  f[i][j] = 1;
  if (h[i - 1][j] < h[i][j]) f[i][j] = std::max(f[i][j], 1 + dfs(i - 1, j));
  if (h[i + 1][j] < h[i][j]) f[i][j] = std::max(f[i][j], 1 + dfs(i + 1, j));
  if (h[i][j - 1] < h[i][j]) f[i][j] = std::max(f[i][j], 1 + dfs(i, j - 1));
  if (h[i][j + 1] < h[i][j]) f[i][j] = std::max(f[i][j], 1 + dfs(i, j + 1));
  return f[i][j];
}
int main() {
  int n, m;
  scanf("%d", &n);
  memset(h, 0x3f, sizeof h);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      scanf("%d", &h[i][j]);
  scanf("%d", &m);
  while (m--) {
    char s[2];
    scanf("%s", s);
    if (*s == 'Q') {
      memset(f, 0, sizeof f);
      int ans = 0;
      for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
          ans = std::max(ans, dfs(i, j));
      printf("%d\n", ans);
    } else if (*s == 'C') {
      int x, y;
      scanf("%d%d", &x, &y);
      scanf("%d", &h[x][y]);
    } else {
      int a, b, c, d;
      scanf("%d%d%d%d", &a, &b, &c, &d);
      for (int i = a; i <= c; ++i)
        for (int j = b; j <= d; ++j)
          mark[i][j] = (*s == 'S');
    }
  }
  return 0;
}
