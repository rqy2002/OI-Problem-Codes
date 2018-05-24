/**************************************************************
 * Problem: BZOJ1051
 * Author: Rqy
 * Date: 2018 Feb 25
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 10050;
const int M = 50050;
int pre[N], to[M], nxt[M], cnt;
inline void addEdge(int x, int y) {
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
}
int dfn[N], scc[N], sccnum, dfscnt, stack[N], top;
int tarjan(int x) {
  int lowx = dfn[x] = ++dfscnt;
  stack[top++] = x;
  for (int i = pre[x]; ~i; i = nxt[i]) {
    int u = to[i];
    if (!dfn[u]) lowx = std::min(lowx, tarjan(u));
    else if (!scc[u]) lowx = std::min(lowx, dfn[u]);
  }
  if (lowx == dfn[x]) {
    scc[x] = ++sccnum;
    while (stack[--top] != x) scc[stack[top]] = sccnum;
  }
  return lowx;
}
int out[N];
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  memset(pre, -1, sizeof pre);
  while (m--) {
    int x, y;
    scanf("%d%d", &x, &y);
    addEdge(x, y);
  }
  for (int i = 1; i <= n; ++i) if (!dfn[i]) tarjan(i);
  for (int i = 1; i <= n; ++i) {
    if (!scc[i]) while(1);
    for (int j = pre[i]; ~j; j = nxt[j])
      if (scc[to[j]] != scc[i]) ++out[scc[i]];
  }
  int r = 0;
  for (int i = 1; i <= sccnum; ++i)
    r += !out[i];
  if (r > 1) printf("0\n");
  else {
    int ans = 0;
    for (int i = 1; i <= n; ++i) ans += !out[scc[i]];
    printf("%d\n", ans);
  }
  return 0;
}
