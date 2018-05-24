/**************************************************************
 * Problem: BZOJ1758
 * Author: Rqy
 * Date: 2017 Dec 11
 * Algorithm: 点分治
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 1000050;
typedef long long LL;
const LL INF = 1e18;
int n, L, U;
struct Edge{
  Edge *nxt;
  int to;
  LL v;
}es[N * 2], *cnt = es, *pre[N];
int vis[N];
LL f[N], g[N];
int depMax;
LL mid;
int time;
int fa[N];
void dfs1(int x, int f, int dep, LL vv) {
  if (dep > U) return;
  depMax = std::max(depMax, dep);
  g[dep] = std::max(g[dep], vv);
  for (Edge *i = pre[x]; i != NULL; i = i->nxt)
    if (i->to != f && vis[i->to] < time)
      dfs1(i->to, x, dep + 1, vv + i->v - mid);
}
int siz[N];
int dfs2(int x, int f) {
  fa[x] = f;
  siz[x] = 1;
  for (Edge *i = pre[x]; i != NULL; i = i->nxt)
    if (i->to != f && vis[i->to] < time)
      siz[x] += dfs2(i->to, x);
  return siz[x];
}
int queue[N], qh, qt;
inline void push(int t) {
  while (qh < qt && f[queue[qt - 1]] < f[t]) --qt;
  queue[qt++] = t;
}
inline void pop(int t) {
  if (queue[qh] == t) ++qh;
}
inline LL maxf() {
  return f[queue[qh]];
}
int aaaaa = 0;
long long bbbbb = 0;
int P[N], to[N], Pcnt = 0;
void find(int x) {
  int fff = x;
  int tot = siz[x];
  int ff = -1;
  for (Edge *i = pre[x]; i != NULL; i = i->nxt) {
      while (i->to != ff && !vis[i->to] && siz[i->to] > tot - siz[i->to]) {
        ff = x;
        x = i->to;
        i = pre[x];
        continue;
      }
  }
  to[P[Pcnt++] = x] = tot;
  vis[x] = 1;
  if (x != fff) {
    for (int i = fa[x]; i && !vis[i]; i = fa[i])
      siz[i] -= siz[x];
    find(fff);
  }
  for (Edge *i = pre[x]; i != NULL; i = i->nxt)
    if (!vis[i->to] && i->to != fa[x])
      find(i->to);
}
LL work(int x) {
  f[0] = g[0] = 0;
  for (int i = 1; i < to[x]; ++i) f[i] = g[i] = -INF;
  int maxMax = 0;
  for (Edge *i = pre[x]; i != NULL; i = i->nxt)
    if (vis[i->to] < time) {
      depMax = 0;
      dfs1(i->to, x, 1, i->v - mid);
      qh = qt = 0;
      for (int i = std::max(L - depMax, 0); i < U - depMax && i <= maxMax; ++i)
        push(i);
      for (int i = depMax; i; --i) {
        push(U - i);
        if (maxf() + g[i] >= 0) return (maxf() + g[i]) / (queue[qh] + i);
        pop(L - i);
      }
      maxMax = std::max(maxMax, depMax);
      for (int i = 1; i <= depMax; ++i) {
        f[i] = std::max(f[i], g[i]);
        g[i] = -INF;
      }
    }
  vis[x] = time;
  return -1;
}
inline void addEdge(int x, int y, LL vv) {
  cnt->nxt = pre[x];
  cnt->v = vv;
  (pre[x] = cnt++)->to = y;
}
int main() {
  scanf("%d%d%d", &n, &L, &U);
  int x, y, vv;
  std::fill(pre + 1, pre + n + 1, (Edge*)NULL);
  LL l = 0, r = 0;
  for (int i = 1; i < n; ++i) {
    scanf("%d%d%d", &x, &y, &vv);
    r = std::max(r, vv * 2000LL);
    addEdge(x, y, vv * 2000LL);
    addEdge(y, x, vv * 2000LL);
  }
  std::fill(vis + 1, vis + n + 1, 0);
  time = 1;
  dfs2(1, -1);
  find(1);
  while (l < r) {
    mid = r + (l - r) / 2;
    ++time;
    LL ok = -1;
    for (int i = 0; i < Pcnt && !~ok; ++i)
      ok = work(P[i]);
    if (~ok) l = mid + ok;
    else r = mid - 1;
  }
  printf("%.3lf\n", (double)l / 2000.0 + 1e-5);
  return 0;
}
