/**************************************************************
 * Problem: BZOJ1036
 * Author: Rqy
 * Date: 2018 Feb 25
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 30050;
int maxv[N * 4], sumv[N * 4];
inline void upd(int o, int l, int r) {
  if (l == r) return;
  maxv[o] = std::max(maxv[o << 1], maxv[o << 1 | 1]);
  sumv[o] = sumv[o << 1] + sumv[o << 1 | 1];
}
int queryS(int o, int l, int r, int L, int R) {
  if (L > r || l > R) return 0;
  if (L <= l && r <= R) return sumv[o];
  int mid = (l + r) / 2;
  return queryS(o << 1, l, mid, L, R)
    + queryS(o << 1 | 1, mid + 1, r, L, R);
}
int queryM(int o, int l, int r, int L, int R) {
  if (L > r || l > R) return -100000;
  if (L <= l && r <= R) return maxv[o];
  int mid = (l + r) / 2;
  return std::max(queryM(o << 1, l, mid, L, R),
    queryM(o << 1 | 1, mid + 1, r, L, R));
}
void modify(int o, int l, int r, int x, int y) {
  if (l == r) { sumv[o] = maxv[o] = y; return; }
  int mid = (l + r) / 2;
  if (x <= mid) modify(o << 1, l, mid, x, y);
  else modify(o << 1 | 1, mid + 1, r, x, y);
  upd(o, l, r);
}
int n, pre[N], nxt[N * 2], to[N * 2], cnt;
inline void addEdge(int x, int y) {
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  to[pre[y] = cnt++] = x;
}
int A[N], pos[N], belong[N], top[N], fa[N], dep[N], siz[N], cnt2, cnt3;
int dfs(int x) {
  siz[x] = 1;
  dep[x] = dep[fa[x]] + 1;
  for (int i = pre[x]; ~i; i = nxt[i])
    if (to[i] != fa[x]) {
      fa[to[i]] = x;
      siz[x] += dfs(to[i]);
    }
  return siz[x];
}
void dfs1(int x, bool t = false) {
  modify(1, 1, n, pos[x] = ++cnt2, A[x]);
  top[x] = t ? x : top[fa[x]];
  belong[x] = t ? cnt3++ : belong[fa[x]];
  int y = 0;
  for (int i = pre[x]; ~i; i = nxt[i])
    if (to[i] != fa[x] && siz[to[i]] > siz[y]) y = to[i];
  if (y) dfs1(y);
  for (int i = pre[x]; ~i; i = nxt[i])
    if (to[i] != fa[x] && to[i] != y) dfs1(to[i], true);
}
int queryS(int x, int y) {
  int ans = 0;
  while (belong[x] != belong[y]) {
    if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
    ans += queryS(1, 1, n, pos[top[x]], pos[x]);
    x = fa[top[x]];
  }
  if (pos[x] > pos[y]) std::swap(x, y);
  return ans + queryS(1, 1, n, pos[x], pos[y]);
}
int queryM(int x, int y) {
  int ans = -100000;
  while (belong[x] != belong[y]) {
    if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
    ans = std::max(ans, queryM(1, 1, n, pos[top[x]], pos[x]));
    x = fa[top[x]];
  }
  if (pos[x] > pos[y]) std::swap(x, y);
  return std::max(ans, queryM(1, 1, n, pos[x], pos[y]));
}
int main() {
  int m, x, y;
  std::fill(maxv, maxv + N * 4, -100000);
  memset(pre, -1, sizeof pre);
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    scanf("%d%d", &x, &y);
    addEdge(x, y);
  }
  for (int i = 1; i <= n; ++i) scanf("%d", &A[i]);
  dfs(1);
  dfs1(1, true);
  scanf("%d", &m);
  char s[10];
  while (m--) {
    scanf("%s%d%d", s, &x, &y);
    if (*s == 'C') modify(1, 1, n, pos[x], y);
    else if (s[1] == 'S') printf("%d\n", queryS(x, y));
    else printf("%d\n", queryM(x, y));
  }
  return 0;
}
