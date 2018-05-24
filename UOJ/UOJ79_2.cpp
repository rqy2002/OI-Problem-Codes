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
int pre[N], to[M], nxt[M], n, cnt;
int mate[N], link[N], fa[N], vis[N], ss[N], time;
int que[N], head, tail;
inline void addEdge(int x, int y) {
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  to[pre[y] = cnt++] = x;
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
    y = mate[x];
    fa[x] = fa[y] = p;
    if (vis[y] == 1)
      vis[que[tail++] = y] = 2;
    x = link[y];
  }
}
bool match(int x) {
  for (int i = 1; i <= n; ++i) {
    fa[i] = i;
    vis[i] = 0;
  }
  head = tail = 0;
  vis[que[tail++] = x] = 2;
  while (head != tail) {
    x = que[head++];
    for (int i = pre[x]; ~i; i = nxt[i]) {
      int u = to[i];
      if (!vis[u]) {
        link[u] = x;
        vis[u] = 1;
        if (mate[u])
          vis[que[tail++] = mate[u]] = 2;
        else {
          while (u) {
            int tmp = mate[x = link[u]];
            mate[mate[u] = link[u]] = u;
            u = tmp;
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
  scanf("%d%d", &n, &m);
  std::fill(pre + 1, pre + n + 1, -1);
  while (m--) {
    scanf("%d%d", &x, &y);
    addEdge(x, y);
    if (!mate[x] && !mate[y]) {
      mate[mate[y] = x] = y;
      ++ans;
    }
  }
  for (int i = 1; i <= n; ++i)
    if (!mate[i] && match(i))
      ++ans;
  printf("%d\n", ans);
  for (int i = 1; i <= n; ++i)
    printf("%d ", mate[i]);
  return 0;
}
