/**************************************************************
 * Problem: BZOJ4405
 * Author: Rqy
 * Date: 2018 Feb 27
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 700;
const int M = N * N * 2;
int pre[N], nxt[M], to[M], n, cnt;
int mate[N], link[N], vis[N], fa[N];
int que[N], hd, tl;
void addEdge(int x, int y) {
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  to[pre[y] = cnt++] = x;
}
int Find(int x) { return fa[x] == x ? x : fa[x] = Find(fa[x]); }
int LCA(int x, int y) {
  static int ss[N], tim;
  ++tim;
  while (ss[x] != tim) {
    if (x) { ss[x] = tim; x = Find(link[mate[x]]); }
    std::swap(x, y);
  }
  return x;
}
void Flower(int x, int y, int p) {
  while (Find(x) != p) {
    link[x] = y;
    fa[y = mate[x]] = fa[x] = p;
    if (vis[y] == 1) vis[que[tl++] = y] = 2;
    x = link[y];
  }
}
bool match(int x) {
  hd = tl = 0;
  for (int i = 1; i <= n; ++i) vis[fa[i] = i] = 0;
  vis[que[tl++] = x] = 2;
  while (hd < tl) {
    x = que[hd++];
    for (int i = pre[x]; ~i; i = nxt[i]) {
      int u = to[i];
      if (!vis[u]) {
        vis[u] = 1;
        link[u] = x;
        if (!mate[u]) {
          while (x) {
            x = mate[link[u]];
            mate[mate[u] = link[u]] = u;
            u = x;
          }
          return true;
        } else
          vis[que[tl++] = mate[u]] = 2;
      } else if (vis[u] == 2 && Find(u) != Find(x)) {
        int p = LCA(x, u);
        Flower(x, u, p);
        Flower(u, x, p);
      }
    }
  }
  return false;
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    memset(mate, 0, sizeof mate);
    memset(pre, -1, sizeof pre);
    cnt = 0;
    int n, m, e;
    scanf("%d%d%d", &n, &m, &e);
    ::n = n + 3 * m;
    while (e--) {
      int x, y;
      scanf("%d%d", &x, &y);
      addEdge(x, n + y);
      addEdge(x, n + m + y);
      addEdge(x, n + m + m + y);
    }
    for (int y = 1; y <= m; ++y) {
      addEdge(n + y, n + m + y);
      addEdge(n + y, n + m + m + y);
      addEdge(n + m + y, n + m + m + y);
    }
    int ans = 0;
    for (int i = 1; i <= ::n; ++i)
      if (!mate[i]) ans += match(i);
    printf("%d\n", ans - n);
//    for (int i = 1; i <= n; ++i) {
//      printf("%d ", (mate[i] - n - 1) % m + 1);
//    }
//    printf("\n");
  }
  return 0;
}
