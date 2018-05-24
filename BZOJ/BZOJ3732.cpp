/**************************************************************
 * Problem: BZOJ3732
 * Author: Rqy
 * Date: 2018 Feb 27
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 15050;
const int M = 30050;
struct Edge{
  int x, y, d;
  bool operator<(const Edge &e) const {
    return d < e.d;
  }
}e[M];
int f1[N], t[N], h[N], dep[N];
int find(int x) { return f1[x] ? find(f1[x]) : x; }
int fa[N][20], maxv[N][20];
void build(int x) {
  if (!x || dep[x]) return;
  build(fa[x][0] = f1[x]);
  maxv[x][0] = t[x];
  dep[x] = dep[fa[x][0]] + 1;
  for (int i = 0; fa[x][i]; ++i) {
    fa[x][i + 1] = fa[fa[x][i]][i];
    maxv[x][i + 1] = std::max(maxv[x][i], maxv[fa[x][i]][i]);
  }
}
int query(int x, int y) {
  int ans = 0;
  if (dep[x] < dep[y]) std::swap(x, y);
  for (int i = 19; ~i; --i)
    if (dep[fa[x][i]] >= dep[y]) {
      ans = std::max(ans, maxv[x][i]);
      x = fa[x][i];
    }
  for (int i = 19; ~i; --i)
    if (fa[x][i] != fa[y][i]) {
      ans = std::max(ans, std::max(maxv[x][i], maxv[y][i]));
      x = fa[x][i];
      y = fa[y][i];
    }
  if (x != y) ans = std::max(ans, std::max(t[x], t[y]));
  return ans;
}
int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < m; ++i)
    scanf("%d%d%d", &e[i].x, &e[i].y, &e[i].d);
  std::sort(e, e + m);
  for (int i = 0; i < m; ++i) {
    int x = find(e[i].x), y = find(e[i].y);
    if (x == y) continue;
    if (h[x] < h[y]) std::swap(x, y);
    f1[y] = x; t[y] = e[i].d; h[x] = std::max(h[x], h[y] + 1);
  }
  for (int i = 1; i <= n; ++i) build(i);
  while (k--) {
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n", query(a, b));
  }
  return 0;
};
