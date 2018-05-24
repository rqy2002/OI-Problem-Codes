/**************************************************************
 * Problem: Luogu P2766
 * Author: Rqy
 * Date: 2017 Dec 22
 * Algorithm: Dinic
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 1050;
const int M = N * 50;
const int INF = 1000000000;
int pre[N], nxt[M], to[M], ret[M], cnt;
int d[N];
int que[N], head, tail;
inline void addEdge(int x, int y, int c) {
  nxt[cnt] = pre[x];
  ret[cnt] = c;
  to[pre[x] = cnt++] = y;
}
bool BFS(int s, int t) {
  memset(d, -1, sizeof d);
  head = tail = 0;
  d[que[tail++] = s] = 0;
  while (head != tail) {
    int x = que[head++];
    if (x == t) return true;
    for (int i = pre[x]; ~i; i = nxt[i])
      if (ret[i] && d[to[i]] == -1)
        d[que[tail++] = to[i]] = d[x] + 1;
  }
  return false;
}
int cur[N];
int dfs(int x, int t, int flow) {
  if (x == t) return flow;
  int ans = 0;
  for (int i = cur[x]; ~i; i = nxt[i]) if (ret[i] && d[to[i]] == d[x] + 1) {
    int ss = dfs(to[i], t, std::min(flow - ans, ret[i]));
    ans += ss;
    ret[i] -= ss;
    ret[i ^ 1] += ss;
    if (ans == flow) {
      cur[x] = i;
      break;
    }
  }
  return ans;
}
int Dinic(int s, int t) {
  int ans = 0;
  while (BFS(s, t)) {
    memcpy(cur, pre, sizeof cur);
    ans += dfs(s, t, INF);
  }
  return ans;
}
int main() {
  int n, k, x, sum = 0;
  scanf("%d%d", &k, &n);
  int S = k + n, T = S + 1;
  memset(pre, -1, sizeof pre);
  for (int i = 0; i < k; ++i) {
    scanf("%d", &x);
    sum += x;
    addEdge(i, T, x);
    addEdge(T, i, 0);
  }
  for (int i = 0; i < n; ++i) {
    int l;
    scanf("%d", &l);
    addEdge(S, i + k, 1);
    addEdge(i + k, S, 0);
    while (l--) {
      scanf("%d", &x);
      addEdge(i + k, x - 1, 1);
      addEdge(x - 1, i + k, 0);
    }
  }
  if (Dinic(S, T) != sum) puts("No Solution!");
  else {
    for (int i = 0; i < k; ++i) {
      printf("%d:", i + 1);
      for (int j = pre[i]; ~j; j = nxt[j])
        if (ret[j])
          printf(" %d", to[j] - k + 1);
      printf("\n");
    }
  }
  return 0;
}
