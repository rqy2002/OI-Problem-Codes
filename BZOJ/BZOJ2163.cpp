/**************************************************************
 * Problem: BZOJ2163
 * Author: Rqy
 * Date: 2018 Feb 28
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 20050;
const int M = 400050;
const int INF = 1000000000;
int pre[N], to[M], nxt[M], ret[M], cnt;
inline void addEdge(int x, int y, int r) {
  nxt[cnt] = pre[x];
  ret[cnt] = r;
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  ret[cnt] = 0;
  to[pre[y] = cnt++] = x;
}
int dis[N], que[N];
bool bfs(int S, int T) {
  int hd = 0, tl = 0;
  memset(dis, -1, sizeof dis);
  dis[que[tl++] = S] = 0;
  while (hd < tl && dis[T] < 0) {
    int x = que[hd++];
    for (int i = pre[x]; ~i; i = nxt[i])
      if (ret[i] && dis[to[i]] < 0)
        dis[que[tl++] = to[i]] = dis[x] + 1;
  }
  return dis[T] >= 0;
}
int dfs(int x, int T, int maxf) {
  if (x == T) return maxf;
  int ans = 0;
  for (int i = pre[x]; ~i && ans < maxf; i = nxt[i])
    if (ret[i] && dis[to[i]] == dis[x] + 1) {
      int u = dfs(to[i], T, std::min(maxf - ans, ret[i]));
      ret[i] -= u;
      ret[i ^ 1] += u;
      ans += u;
    }
  if (ans < maxf) dis[x] = -1;
  return ans;
}
int solve(int S, int T) {
  int ans = 0;
  while (bfs(S, T)) ans += dfs(S, T, INF);
  return ans;
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  int S = 0, T = n * 2 + 1, ans = 0;
  memset(pre, -1, sizeof pre);
  for (int i = 1, x; i <= n; ++i) {
    scanf("%d", &x);
    addEdge(S, i, x);
    addEdge(n + i, T, x);
    ans += x;
  }
  while (m--) {
    int x, y, w;
    scanf("%d%d%d", &x, &y, &w);
    addEdge(x, n + y, w);
  }
  printf("%d\n", ans - solve(S, T));
  return 0;
}
