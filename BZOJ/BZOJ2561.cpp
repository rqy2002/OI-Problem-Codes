/**************************************************************
 * Problem: BZOJ2561
 * Author: Rqy
 * Date: 2018 Feb 28
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 20050;
const int M = 400050;
int pre[N], nxt[M], to[M], ret[M], cnt;
void addEdge(int x, int y) {
  nxt[cnt] = pre[x];
  ret[cnt] = 1;
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  ret[cnt] = 1;
  to[pre[y] = cnt++] = x;
}
int dis[N], que[N];
bool bfs(int S, int T) {
  memset(dis, -1, sizeof dis);
  int hd = 0, tl = 0;
  dis[que[tl++] = S] = 0;
  while (hd < tl)
    for (int x = que[hd++], i = pre[x]; ~i; i = nxt[i])
      if (ret[i] && dis[to[i]] == -1) dis[que[tl++] = to[i]] = dis[x] + 1;
  return dis[T] >= 0;
}
int dfs(int x, int T, int maxf) {
  if (x == T) return maxf;
  int ans = 0;
  for (int i = pre[x]; ~i && ans < maxf; i = nxt[i])
    if (ret[i] && dis[to[i]] == dis[x] + 1) {
      int u = dfs(to[i], T, std::min(maxf - ans, ret[i]));
      ret[i] -= u; ret[i ^ 1] += u; ans += u;
    }
  if (ans < maxf) dis[x] = -1;
  return ans;
}
int a[M], b[M], c[M];
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) scanf("%d%d%d", &a[i], &b[i], &c[i]);
  int u, v, L;
  scanf("%d%d%d", &u, &v, &L);
  int ans = 0;
  memset(pre, -1, sizeof pre); cnt = 0;
  for (int i = 0; i < m; ++i) if (c[i] < L) addEdge(a[i], b[i]);
  while (bfs(u, v)) ans += dfs(u, v, 10000000);
  memset(pre, -1, sizeof pre); cnt = 0;
  for (int i = 0; i < m; ++i) if (c[i] > L) addEdge(a[i], b[i]);
  while (bfs(u, v)) ans += dfs(u, v, 10000000);
  printf("%d\n", ans);
  return 0;
}
