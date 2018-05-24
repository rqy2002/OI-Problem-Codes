/**************************************************************
 * Problem: BZOJ4196
 * Author: Rqy
 * Date: 2018 Feb 28
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 100050;
int fa[N], pre[N], nxt[N];
int top[N], dep[N], cnt, left[N], right[N], siz[N];
void addSon(int x, int y) { nxt[y] = pre[x]; pre[x] = y; }
int dfs0(int x) {
  siz[x] = 1;
  for (int u = pre[x]; u; u = nxt[u]) dep[u] = dep[x] + 1, siz[x] += dfs0(u);
  return siz[x];
}
void dfs1(int x, int tp) {
  left[x] = ++cnt;
  top[x] = tp;
  int i = pre[x];
  for (int j = pre[x]; j; j = nxt[j]) if (siz[j] > siz[i]) i = j;
  if (i) dfs1(i, tp);
  for (int j = pre[x]; j; j = nxt[j]) if (i != j) dfs1(j, j);
  right[x] = cnt;
}
int setv[N * 4], sumv[N * 4];
inline void upd(int o, int l, int r) {
  if (~setv[o]) sumv[o] = setv[o] * (r - l + 1);
  else sumv[o] = sumv[o << 1] + sumv[o << 1 | 1];
}
inline void pushd(int o, int l, int r) {
  if (~setv[o] && l != r) {
    setv[o << 1] = setv[o << 1 | 1] = setv[o];
    setv[o] = -1;
  }
}
void set(int o, int l, int r, int L, int R, int x) {
  upd(o, l, r);
  if (l > R || L > r) return;
  if (L <= l && r <= R) setv[o] = x;
  else {
    int mid = (l + r) / 2;
    pushd(o, l, r);
    set(o << 1, l, mid, L, R, x);
    set(o << 1 | 1, mid + 1, r, L, R, x);
  }
  upd(o, l, r);
}
int query(int o, int l, int r, int L, int R) {
  upd(o, l, r);
  if (l > R || L > r) return 0;
  if (L <= l && r <= R) return sumv[o];
  else {
    int mid = (l + r) / 2;
    pushd(o, l, r);
    return query(o << 1, l, mid, L, R)
        + query(o << 1 | 1, mid + 1, r, L, R);
  }
}
int n;
int install(int x) {
  int ans = dep[x] + 1;
  while (~x) {
    ans -= query(1, 1, n, left[top[x]], left[x]);
    set(1, 1, n, left[top[x]], left[x], 1);
    x = fa[top[x]];
  }
  return ans;
}
int uninstall(int x) {
  int ans = query(1, 1, n, left[x], right[x]);
  set(1, 1, n, left[x], right[x], 0);
  return ans;
}
int main() {
  scanf("%d", &n);
  fa[0] = -1;
  for (int i = 1; i < n; ++i) {
    scanf("%d", &fa[i]);
    addSon(fa[i], i);
  }
  dfs0(0);
  dfs1(0, 0);
  int q;
  scanf("%d", &q);
  char s[15];
  while (q--) {
    int x;
    scanf("%s%d", s, &x);
    printf("%d\n", (*s == 'i' ? install : uninstall)(x));
  }
  return 0;
}
