/**************************************************************
 * Problem: P3806
 * Author: Rqy
 * Date: 2017 Dec 23
 * Algorithm: 点分治
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 10050;
int vis[N];
int pre[N], nxt[N * 2], to[N * 2], w[N * 2], cnt;
inline void addEdge(int x, int y, int z) {
  nxt[cnt] = pre[x];
  w[cnt] = z;
  to[pre[x] = cnt++] = y;
}
void dfs(int x, int fa, int dep, int* &p) {
  *(p++) = dep;
  for (int i = pre[x]; ~i; i = nxt[i])
    if (!vis[to[i]] && to[i] != fa)
      dfs(to[i], x, dep + w[i], p);
}
int getCentre(int x, int fa, int siz, int &ct) {
  int res = 1;
  bool ok = true;
  for (int i = pre[x]; ~i; i = nxt[i])
    if (!vis[to[i]] && to[i] != fa) {
      int ss = getCentre(to[i], x, siz, ct);
      if (ss * 2 > siz) ok = false;
      res += ss;
    }
  if (ok && res * 2 >= siz) ct = x;
  return res;
}
int tmp[N], a[N], b[N];
int target;
bool solve(int x) {
  getCentre(x, 0, getCentre(x, 0, 10000000, x), x);
  vis[x] = 1;
  int *c = a, *d, *j, *k, *l;
  *(c++) = 0;
  for (int i = pre[x]; ~i; i = nxt[i]) if (!vis[to[i]]) {
    d = b;
    dfs(to[i], x, w[i], d);
    std::sort(b, d);
    for (j = b, k = c - 1; j < d; ++j) {
      while (k > a && *k + *j > target) --k;
      if (*k + *j == target) return true;
    }
    j = a, k = b, l = tmp;
    while (j < c && k < d)
      *(l++) = *((*j > *k ? k : j)++);
    while (j < c) *(l++) = *(j++);
    while (k < d) *(l++) = *(k++);
    c = a, k = tmp;
    while (k < l) *(c++) = *(k++);
  }
  for (int i = pre[x]; ~i; i = nxt[i]) if (!vis[to[i]])
    if (solve(to[i])) return true;
  return false;
}
int main() {
  int n, m, x, y, z;
  scanf("%d%d", &n, &m);
  std::fill(pre + 1, pre + n + 1, -1);
  for (int i = 1; i < n; ++i) {
    scanf("%d%d%d", &x, &y, &z);
    addEdge(x, y, z);
    addEdge(y, x, z);
  }
  while (m--) {
    scanf("%d", &target);
    std::fill(vis + 1, vis + n + 1, 0);
    puts(solve(1) ? "AYE" : "NAY");
  }
  return 0;
}
