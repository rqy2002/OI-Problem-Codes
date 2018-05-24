/**************************************************************
 * Problem: Luogo P2774
 * Author: Rqy
 * Date: 2017 Dec 22
 * Algorithm: Dinic
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 10050;
const int M = 60050;
const int INF = 100000000;
int pre[N], nxt[M], ret[M], to[M], cnt;
inline void addEdge_(int x, int y, int c) {
  nxt[cnt] = pre[x];
  ret[cnt] = c;
  to[pre[x] = cnt++] = y;
}
inline void addEdge(int x, int y, int c) {
  addEdge_(x, y, c); addEdge_(y, x, 0);
}
int que[N], head, tail;
int dis[N];
bool BFS(int S, int T) {
  head = tail = 0;
  memset(dis, -1, sizeof dis);
  dis[que[tail++] = S] = 0;
  while (head != tail) {
    int x = que[head++];
    if (x == T) return true;
    for (int i = pre[x]; ~i; i = nxt[i])
      if (ret[i] && dis[to[i]] == -1)
        dis[que[tail++] = to[i]] = dis[x] + 1;
  }
  return false;
}
int cur[N];
int DFS(int x, int t, int flow) {
  if (x == t) return flow;
  int ans = 0;
  while (~cur[x]) {
    int u = cur[x];
    if (dis[to[u]] != dis[x] + 1) {
      cur[x] = nxt[u];
      continue;
    }
    int ss = DFS(to[u], t, std::min(flow - ans, ret[u]));
    ans += ss;
    ret[u] -= ss;
    ret[u ^ 1] += ss;
    if (ans == flow) break;
    cur[x] = nxt[u];
  }
  return ans;
}
int dinic(int S, int T) {
  int ans = 0;
  while (BFS(S, T)) {
    memcpy(cur, pre, sizeof cur);
    ans += DFS(S, T, INF);
  }
  return ans;
}
int main() {
  int n, m, x;
  scanf("%d%d", &n, &m);
  int S = n * m, T = S + 1, ans = 0;
  memset(pre, -1, sizeof pre);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      scanf("%d", &x);
      ans += x;
      if ((i ^ j) & 1) {
        addEdge(i * m + j, T, x);
        if (i) addEdge((i - 1) * m + j, i * m + j, INF);
        if (i < n - 1) addEdge((i + 1) * m + j, i * m + j, INF);
        if (j) addEdge(i * m + j - 1, i * m + j, INF);
        if (j < m - 1) addEdge(i * m + j + 1, i * m + j, INF);
      } else
        addEdge(S, i * m + j, x);
    }
  printf("%d\n", ans - dinic(S, T));
  return 0;
}
