/**************************************************************
 * Problem: UOJ79
 * Author: Rqy
 * Date: 2017 Dec 21
 * Algorithm: 带花树
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 505;
const int M = 250050;
int n, m;
int pre[N], nxt[M], to[M], cnt;
void addEdge(int x, int y) {
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  to[pre[y] = cnt++] = x;
}
int que[N], head, tail;
int fa[N];
int Find(int x) {
  return fa[x] == x ? x : fa[x] = Find(fa[x]);
}
int mate[N], link[N], vis[N];
int LCA(int x, int y) {
  static int ss[N];
  static int time = 0;
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
bool match(int v) {
  head = tail = 0;
  for (int i = 1; i <= n; ++i) {
    fa[i] = i;
    vis[i] = 0;
  }
  vis[que[tail++] = v] = 2;
  while (head < tail) {
    int x = que[head++];
    for (int i = pre[x]; ~i; i = nxt[i]) {
      int u = to[i];
      if (!vis[u]) {
        vis[u] = 1;
        link[u] = x;
        if (mate[u])
          vis[que[tail++] = mate[u]] = 2;
        else {
          while (u) {
            int tmp = mate[link[u]];
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
  scanf("%d%d", &n, &m);
  std::fill(pre + 1, pre + n + 1, -1);
  int x, y;
  int ans = 0;
  while (m--) {
    scanf("%d%d", &x, &y);
    addEdge(x, y);
    if (!mate[x] && !mate[y]) {
      mate[mate[x] = y] = x;
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
