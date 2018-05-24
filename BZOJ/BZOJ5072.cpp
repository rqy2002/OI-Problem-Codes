/**************************************************************
 * Problem: BZOJ5072
 * Author: Rqy
 * Date: 2018 Feb 28
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 5050;
int f[N][N], g[N][N], siz[N], b[N];
int f1[N], g1[N];
int pre[N], to[N * 2], nxt[N * 2], cnt;
inline void addEdge(int x, int y) {
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  to[pre[y] = cnt++] = x;
}
int tmp[N];
void dfs(int x, int fa) {
  memset(f[x], 0x3f, sizeof f[x]);
  memset(g[x], 0, sizeof g[x]);
  siz[x] = 1;
  f[x][0] = g[x][0] = 0;
  f[x][1] = g[x][1] = b[x];
  for (int e = pre[x]; ~e; e = nxt[e]) if (to[e] != fa) {
    int u = to[e];
    dfs(u, x);
    for (int i = 0; i <= siz[x] + siz[u]; ++i) tmp[i] = f[x][i];
    for (int i = 1; i <= siz[x]; ++i)
      for (int j = 1; j <= siz[u]; ++j)
        tmp[i + j] = std::min(tmp[i + j], f[x][i] + f[u][j]);
    for (int i = 0; i <= siz[x] + siz[u]; ++i) f[x][i] = tmp[i];
    for (int i = 0; i <= siz[x] + siz[u]; ++i) tmp[i] = g[x][i];
    for (int i = 1; i <= siz[x]; ++i)
      for (int j = 1; j <= siz[u]; ++j)
        tmp[i + j] = std::max(tmp[i + j], g[x][i] + g[u][j]);
    for (int i = 0; i <= siz[x] + siz[u]; ++i) g[x][i] = tmp[i];
    siz[x] += siz[u];
  }
  for (int i = 0; i <= siz[x]; ++i) {
    f1[i] = std::min(f1[i], f[x][i]);
    g1[i] = std::max(g1[i], g[x][i]);
  }
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, q;
    scanf("%d%d", &n, &q);
    memset(pre, -1, sizeof pre);
    cnt = 0;
    for (int i = 1, x, y; i < n; ++i) {
      scanf("%d%d", &x, &y);
      addEdge(x, y);
    }
    for (int i = 1; i <= n; ++i) scanf("%d", &b[i]);
    memset(f1, 0x3f, sizeof f1);
    memset(g1, 0, sizeof g1);
    dfs(1, 0);
    for (int i = 0, x, y; i < q; ++i) {
      scanf("%d%d", &x, &y);
      puts(y <= g1[x] && y >= f1[x] ? "YES" : "NO");
    }
    puts("");
  }
  return 0;
}
