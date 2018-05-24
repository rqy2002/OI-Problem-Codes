/**************************************************************
 * Problem: Luogu P3376
 * Author: Rqy
 * Date: 2018 Jan 25
 * Algorithm: 最大流（模板）
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 10050;
const int M = 200050;
int pre[N], nxt[M], to[M], ret[M], cnt;
inline void addEdge(int x, int y, int w) {
  nxt[cnt] = pre[x];
  ret[cnt] = w;
  to[pre[x] = cnt++] = y;
}
int dis[N], que[N];
bool bfs(int S, int T) {
  memset(dis, -1, sizeof dis);
  int hd = 0, tl = 0;
  dis[que[tl++] = S] = 0;
  while (hd < tl) {
    int x = que[hd++];
    if (x == T) return true;
    for (int i = pre[x]; ~i; i = nxt[i])
      if (ret[i] && !~dis[to[i]])
        dis[que[tl++] = to[i]] = dis[x] + 1;
  }
  return false;
}
int dfs(int x, int maxf, int T) {
  if (x == T) return maxf;
  int ans = 0;
  for (int i = pre[x]; ~i && ans < maxf; i = nxt[i])
    if (ret[i] && dis[to[i]] == dis[x] + 1) {
      int res = dfs(to[i], std::min(maxf - ans, ret[i]), T);
      ret[i] -= res;
      ret[i ^ 1] += res;
      ans += res;
    }
  if (ans < maxf) dis[x] = dis[T] + 1;
  return ans;
}
int MF(int S, int T) {
  int ans = 0;
  while (bfs(S, T)) ans += dfs(S, 1000000000, T);
  return ans;
}
int main() {
  int n, m, S, T;
  scanf("%d%d%d%d", &n, &m, &S, &T);
  int x, y, z;
  memset(pre, -1, sizeof pre);
  while (m--) {
    scanf("%d%d%d", &x, &y, &z);
    addEdge(x, y, z);
    addEdge(y, x, 0);
  }
  printf("%d\n", MF(S, T));
  return 0;
}

