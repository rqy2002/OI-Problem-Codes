/**************************************************************
 * Problem: Luogu P3384
 * Author: Rqy
 * Date: 2018 Mar 08
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 100050;
typedef long long LL;
LL p;
int pre[N], nxt[N * 2], to[N * 2], cnt;
inline void addEdge(int x, int y) {
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  to[pre[y] = cnt++] = x;
}
int siz[N], top[N], fa[N], dep[N], pos[N], end[N], cnt2;
int n, v[N];
LL A[N], B[N];
void add(LL *A, int x, int i) { for (; i <= n; i += i & -i) (A[i] += x) %= p; }
LL query(LL *A, int i) { LL x = 0; for (; i; i &= i - 1) (x += A[i]) %= p; return x; }
void add2(int L, int R, int v) {
  add(A, L, v);
  add(A, R + 1, -v);
  add(B, L, -(L - 1) * v);
  add(B, R + 1, R * v);
}
LL query2(int x) { return (query(A, x) * x + query(B, x) + 2 * p) % p; }
int dfs0(int x, int f) {
  dep[x] = dep[fa[x] = f] + 1;
  siz[x] = 1;
  for (int i = pre[x]; ~i; i = nxt[i])
    if (to[i] != f) siz[x] += dfs0(to[i], x);
  return siz[x];
}
void dfs(int x, int tp) {
  top[x] = tp;
  pos[x] = ++cnt2;
  add2(pos[x], pos[x], v[x]);
  int j = 0;
  for (int i = pre[x]; ~i; i = nxt[i])
    if (to[i] != fa[x] && siz[to[i]] > siz[j]) j = to[i];
  if (j) dfs0(j, tp);
  for (int i = pre[x]; ~i; i = nxt[i])
    if (to[i] != fa[x] && to[i] != j) dfs(to[i], to[i]);
  end[x] = cnt2;
}
void add(int x, int y, int v) {
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
    add2(pos[top[x]], pos[x], v);
    x = fa[top[x]];
  }
  if (dep[x] > dep[y]) std::swap(x, y);
  add2(pos[x], pos[y], v);
}
LL query(int x, int y) {
  LL ans = 0;
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
    (ans += query2(pos[x]) - query2(pos[top[x]] - 1) + p) %= p;
    x = fa[top[x]];
  }
  if (dep[x] > dep[y]) std::swap(x, y);
  return (ans + query2(pos[y]) - query2(pos[x] - 1) + p) % p;
}
int main() {
  int m, r;
  scanf("%d%d%d%lld", &n, &m, &r, &p);
}
