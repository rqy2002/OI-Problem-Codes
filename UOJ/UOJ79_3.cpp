/**************************************************************
 * Problem: UOJ79
 * Author: Rqy
 * Date: 2017 Dec 21
 * Algorithm: See UOJ79.cpp
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 550;
const int M = 250050;
int pre[N], nxt[M], to[M], cnt, n;
int vis[N], fa[N], link[N], mate[N];
int que[N], head, tail;
int ss[N], time;
inline void addEdge(int x, int y) {
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
}
int Find(int x) { return fa[x] == x ? x : fa[x] = Find(fa[x]); }
int LCA(int x, int y) {
  ++time;
  while (ss[x] != time) {
    if (x) {
      ss[x] = time;
      x = Find(link[mate[x]]);
    }
    std::swap(x, y);
  }
  return x;
}
void flower(int x, int y, int p) {
  while (Find(x) != p) {
    link[x] = y;
    fa[y = mate[x]] = fa[x] = p;
    if (vis[y] == 1)
      vis[que[tail++] = y] = 2;
    x = link[y];
  }
}
bool match(int x) {
  head = tail = 0;
  for (int i = 1; i <= n; ++i)
    vis[fa[i] = i] = 0;
  vis[que[tail++] = x] = 2;
  while (head != tail) {
    x = que[head++];
    for (int i = pre[x]; ~i; i = nxt[i]) {
      int u = to[i];
      if (!vis[u]) {
        vis[u] = 1;
        link[u] = x;
        if (mate[u])
          vis[que[tail++] = mate[u]] = 2;
        else {
          while (u) {
            x = mate[link[u]];
            mate[mate[u] = link[u]] = u;
            u = x;
          }
          return true;
        }
      } else if (vis[u] == 2 && Find(u) != Find(x)) {
        int p = LCA(x, u);
        flower(x, u, p);
        flower(u, x, p);
      }
    }
  }
  return false;
}
int main() {
  int m, x, y, ans = 0;
  scanf("%d%d", &n ,&m);
  std::fill(pre + 1, pre + n + 1, -1);
  while (m--) {
    scanf("%d%d", &x, &y);
    addEdge(x, y);
    addEdge(y, x);
    if (!mate[x] && !mate[y])
      mate[mate[x] = y] = x, ++ans;
  }
  for (int i = 1; i <= n; ++i)
    if (!mate[i] && match(i))
      ++ans;
  printf("%d\n", ans);
  for (int i = 1; i <= n; ++i)
    printf("%d ", mate[i]);
  return 0;
}
