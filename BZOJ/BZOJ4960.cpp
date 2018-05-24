/**************************************************************
 * Problem: BZOJ4960
 * Author: Rqy
 * Date: 2017 Dec 22
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 125;
const int M = N * N;

struct Edge{
  int from, to, w, nxt;
  bool operator<(const Edge &t) {
    return w < t.w;
  }
}e[M];

int n, m;
int pre[N], end[N];
int mate[N], fa[N], link[N], vis[N];
int que[N], head, tail;
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
int st[N], time;

int LCA(int x, int y) {
  ++time;
  while (st[x] != time) {
    if (x) {
      st[x] = time;
      x = find(link[mate[x]]);
    }
    std::swap(x, y);
  }
  return x;
}

void flower(int x, int y, int p) {
  while (find(x) != p) {
    link[x] = y;
    fa[y = mate[x]] = fa[x] = p;
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
    for (int i = pre[x]; ~i; i = e[i].nxt) {
      int u = e[i].to;
      if (!vis[u]) {
        link[u] = x;
        vis[u] = 1;
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
      } else if (vis[u] == 2 && find(u) != find(x)) {
        int p = LCA(u, x);
        flower(x, u, p);
        flower(u, x, p);
      }
    }
  }
  return false;
}

inline void addEdge_(int t) { e[end[e[t].from]].nxt = t; }

int tmp[N];

bool addEdge(int t) {
  int x = e[t].from, y = e[t].to;
  if (pre[x] == -1) pre[x] = end[x] = t;
  else {
    e[end[x]].nxt = t;
    end[x] = t;
  }
  if (pre[y] == -1) pre[y] = end[y] = t ^ 1;
  else {
    e[end[y]].nxt = t ^ 1;
    end[y] = t ^ 1;
  }
  if (!mate[x] && !mate[y]) {
    mate[mate[x] = y] = x;
    return true;
  }
  for (int i = 1; i <= n; ++i) tmp[i] = mate[i];
  int u = mate[x], v = mate[y];
  mate[mate[x] = y] = x;
  mate[u] = mate[v] = 0;
  if (!u || !v) {
    u |= v;
    return match(u);
  } else {
    mate[v] = n + 1;
    if (match(u)) {
      mate[v] = 0;
      return match(v);
    } else {
      mate[v] = 0;
      if (!match(v))
        for (int i = 1; i <= n; ++i) mate[i] = tmp[i];
      return false;
    }
  }
}

bool rmEdge(int t) {
  int x = e[t].from, y = e[t].to;
  pre[x] = e[t].nxt;
  pre[y] = e[t ^ 1].nxt;
  if (mate[x] != y) return true;
  else {
    mate[x] = mate[y] = 0;
    return match(x) || match(y);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  std::fill(pre + 1, pre + n + 2, -1);
  int x, y, w;
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d", &x, &y, &w);
    e[i << 1] = (Edge){x, y, w, pre[x]};
    pre[x] = i << 1;
    e[i << 1 | 1] = (Edge){y, x, w, pre[y]};
    pre[y] = i << 1 | 1;
  }
  int ans1 = 0;
  for (int i = 1; i <= n; ++i)
    if (!mate[i] && match(i))
      ++ans1;
  printf("%d\n", ans1);
  std::sort(e, e + 2 * m);
  for (int i = 0; i < m * 2; ++i) e[i].nxt = -1;
  for (int i = 1; i <= n; ++i) {
    pre[i] = -1;
    mate[i] = 0;
  }
  int anss = 0, ans2 = e[2 * m - 1].w - e[0].w;
  int j = 0;
  while (anss != ans1) anss += addEdge(j), j += 2;
  ans2 = e[j - 1].w - e[0].w;
  for (int i = 1; i < m; ++i) {
    anss -= !rmEdge(2 * (i - 1));
    while (anss != ans1 && j < 2 * m) anss += addEdge(j), j += 2;
    if (anss != ans1) break;
    ans2 = std::min(ans2, e[j - 1].w - e[i].w);
  }
  printf("%d\n", ans2);
  return 0;
}
