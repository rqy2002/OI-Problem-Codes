/**************************************************************
 * Problem: BZOJ3996
 * Author: Rqy
 * Date: 2018 Feb 22
 * Algorithm: 最小割
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 500;
const int NN = 500000;
const int M = 3000050;
int pre[NN], nxt[M], to[M], ret[M], cnt;
int dis[NN], que[NN];
bool BFS(int S, int T) {
  int hd = 0, tl = 0;
  memset(dis, -1, sizeof dis);
  for (dis[que[tl++] = S] = 0; hd < tl; ++hd)
    for (int i = pre[que[hd]]; ~i; i = nxt[i])
      if (ret[i] && !~dis[to[i]]) dis[que[tl++] = to[i]] = dis[que[hd]] + 1;
  return dis[T] != -1;
}
int DFS(int x, int T, int maxf) {
  if (!maxf) return 0;
  if (x == T) return maxf;
  int ans = 0;
  for (int i = pre[x]; ~i; i = nxt[i])
    if (ret[i] && dis[to[i]] == dis[x] + 1) {
      int t = DFS(to[i], T, std::min(maxf - ans, ret[i]));
      ret[i] -= t; ret[i ^ 1] += t;
      ans += t;
    }
  if (ans < maxf) dis[x] = -1;
  return ans;
}
int solve(int S, int T) {
  int ans = 0;
  while (BFS(S, T)) ans += DFS(S, T, 1000000000);
  return ans;
}
inline void addEdge(int x, int y, int c) {
  nxt[cnt] = pre[x];
  ret[cnt] = c;
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  ret[cnt] = 0;
  to[pre[y] = cnt++] = x;
}
int main() {
  int n;
  scanf("%d", &n);
  memset(pre, -1, sizeof pre);
  int S = n * (n + 1), T = S + 1;
  int ans = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0, v; j < n; ++j) {
      scanf("%d", &v);
      ans += v;
      int t = (i + 1) * n + j;
      addEdge(t, T, v);
      addEdge(i, t, 1000000000);
      addEdge(j, t, 1000000000);
    }
  for (int i = 0, v; i < n; ++i) {
    scanf("%d", &v);
    addEdge(S, i, v);
  }
  printf("%d\n", ans - solve(S, T));
  return 0;
}
