/**************************************************************
 * Problem: BZOJ3894
 * Author: Rqy
 * Date: 2018 Feb 27
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 30050;
const int M = 300050;
const int INF = 1000000000;
int pre[N], nxt[M], to[M], ret[M], cnt;
void addEdge(int x, int y, int c) {
  nxt[cnt] = pre[x];
  ret[cnt] = c;
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
  while (hd < tl) {
    int x = que[hd++];
    if (x == T) return true;
    for (int i = pre[x]; ~i; i = nxt[i])
      if (ret[i] && dis[to[i]] == -1)
        dis[que[tl++] = to[i]] = dis[x] + 1;
  }
  return false;
}
int dfs(int x, int T, int maxf) {
  if (x == T) return maxf;
  int ans = 0;
  for (int i = pre[x]; ~i && ans < maxf; i = nxt[i])
    if (ret[i] && dis[to[i]] == dis[x] + 1) {
      int flow = dfs(to[i], T, std::min(ret[i], maxf - ans));
      ans += flow;
      ret[i] -= flow;
      ret[i ^ 1] += flow;
    }
  if (ans < maxf) dis[x] = -1;
  return ans;
}
int solve(int S, int T) {
  int ans = 0;
  while (bfs(S, T))
    ans += dfs(S, T, INF);
  return ans;
}
const int dx[5] = {0, 1, -1, 0, 0};
const int dy[5] = {0, 0, 0, 1, -1};
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  memset(pre, -1, sizeof pre);
  int cnt2 = n * m;
  int S = cnt2++;
  int T = cnt2++;
  int sum = 0;
#define node(i, j) ((i) * m + (j))
  for (int i = 0, x; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      scanf("%d", &x);
      sum += x;
      addEdge(S, node(i, j), x);
    }
  for (int i = 0, x; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      scanf("%d", &x);
      sum += x;
      addEdge(node(i, j), T, x);
    }
  for (int i = 0, x; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      scanf("%d", &x);
      sum += x;
      int t = cnt2++;
      addEdge(S, t, x);
      for (int k = 0; k < 5; ++k) {
        int u = i + dx[k], v = j + dy[k];
        if (u >= 0 && u < n && v >= 0 && v < m)
          addEdge(t, node(u, v), INF);
      }
    }
  for (int i = 0, x; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      scanf("%d", &x);
      sum += x;
      int t = cnt2++;
      addEdge(t, T, x);
      for (int k = 0; k < 5; ++k) {
        int u = i + dx[k], v = j + dy[k];
        if (u >= 0 && u < n && v >= 0 && v < m)
          addEdge(node(u, v), t, INF);
      }
    }
  printf("%d\n", sum - solve(S, T));
  return 0;
}
