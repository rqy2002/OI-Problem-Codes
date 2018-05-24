/**************************************************************
 * Problem: BZOJ5073
 * Author: Rqy
 * Date: 2018 Feb 28
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 100050;
const int K = 105;
int f[K][N], g[K][N];
char s[N], p[N];
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m, x;
    scanf("%d%d%d", &n, &m, &x);
    scanf("%s%s", s + 1, p);
    ++n;
    s[0] = '\0';
    for (int i = 0; i <= x; ++i)
      for (int j = 0; j < n; ++j)
        f[i][j] = -1, g[i][j] = 0;
    for (int i = 0; i <= x; ++i)
      for (int j = 0; j < n; ++j) {
        g[i][j + 1] = std::max(g[i][j + 1], g[i][j]);
        if (p[g[i][j]] == s[j + 1])
          f[i + 1][j + 1] = std::max(f[i + 1][j + 1], g[i][j] + 1);
        g[i][j + 1] = std::max(g[i][j + 1], f[i][j]);
        if (f[i][j] >= 0 && p[f[i][j]] == s[j + 1])
          f[i][j + 1] = std::max(f[i][j + 1], f[i][j] + 1);
      }
    puts(g[x][n] >= m ? "YES" : "NO");
  }
  return 0;
}
