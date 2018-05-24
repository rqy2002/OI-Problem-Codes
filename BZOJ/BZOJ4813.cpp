/**************************************************************
 * Problem: BZOJ4813
 * Author: Rqy
 * Date: 2018 Feb 27
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <vector>
const int N = 105;
typedef std::vector<int> VI;
int f[N][N], g[N][N];
int n, m;
VI to[N];
void dfs(int x, int fa) {
  for (int i = 0; i <= m; ++i) f[x][i] = g[x][i] = 1;
  for (VI::iterator it = to[x].begin(); it != to[x].end(); ++it) {
    int u = *it;
    if (u == fa) continue;
    dfs(u, x);
    for (int i = m; ~i; --i)
      for (int j = 0; j < i; ++j) {
        f[x][i] = std::max(f[x][i], g[x][j] + f[u][i - j - 1]);
        if (i - j > 1) {
          f[x][i] = std::max(f[x][i], f[x][j] + g[u][i - j - 2]);
          g[x][i] = std::max(g[x][i], g[x][j] + g[u][i - j - 2]);
        }
      }
  }
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, x, y; i < n; ++i) {
    scanf("%d%d", &x, &y);
    to[x].push_back(y);
    to[y].push_back(x);
  }
  dfs(0, -1);
  printf("%d\n", f[0][m]);
  return 0;
}
