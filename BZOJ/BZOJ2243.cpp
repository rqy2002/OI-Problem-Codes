/**************************************************************
 * Problem: BZOJ2243
 * Author: Rqy
 * Date: 2018 Feb 28
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 100050;
int pre[N], nxt[N * 2], to[N * 2], cnt;
inline void addEdge(int x, int y) {
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  to[pre[y] = cnt++] = x;
}
int n, fa[N], siz[N], dep[N], color[N];
int top[N], pos[N], id[N], cnt2;
int dfs0(int x, int f) {
  dep[x] = dep[fa[x] = f] + 1;
  siz[x] = 1;
  for (int i = pre[x]; ~i; i = nxt[i])
    if (to[i] != f) siz[x] += dfs0(to[i], x);
  return siz[x];
}
void dfs1(int x, int tp) {
  top[x] = tp;
  id[pos[x] = ++cnt2] = x;
  int s = 0;
  for (int i = pre[x]; ~i; i = nxt[i])
    if (to[i] != fa[x] && siz[to[i]] > siz[s]) s = to[i];
  if (s) dfs1(s, tp);
  for (int i = pre[x]; ~i; i = nxt[i])
    if (to[i] != fa[x] && to[i] != s) dfs1(to[i], to[i]);
}
struct Msg{
  int l, r, s;
  Msg() {}
  Msg(int x) : l(x), r(x), s(1) {}
  Msg(int l, int r, int s) : l(l), r(r), s(s) {}
  friend Msg operator+(const Msg &x, const Msg &y) {
    return Msg(x.l, y.r, x.s + y.s - (x.r == y.l));
  }
}msgv[N * 4];
int setv[N * 4];
inline void pushd(int o, int l, int r) {
  if (~setv[o]) {
    if (l == r) color[id[l]] = setv[o];
    else setv[o << 1] = setv[o << 1 | 1] = setv[o];
    setv[o] = -1;
  }
}
inline void upd(int o, int l, int r) {
  if (~setv[o]) msgv[o] = Msg(setv[o]);
  else if (l == r) msgv[o] = Msg(color[id[l]]);
  else msgv[o] = msgv[o << 1] + msgv[o << 1 | 1];
}
void build(int o, int l, int r) {
  if (l != r) {
    int mid = (l + r) / 2;
    build(o << 1, l, mid);
    build(o << 1 | 1, mid + 1, r);
  }
  setv[o] = -1;
  upd(o, l, r);
}
void set(int o, int l, int r, int L, int R, int x) {
  upd(o, l, r);
  if (L <= l && r <= R)
    setv[o] = x;
  else if (l <= R && L <= r) {
    pushd(o, l, r);
    int mid = (l + r) / 2;
    set(o << 1, l, mid, L, R, x);
    set(o << 1 | 1, mid + 1, r, L, R, x);
  }
  upd(o, l, r);
}
int get(int o, int l, int r, int x) {
  if (~setv[o]) return setv[o];
  if (l == r) return color[id[l]];
  int mid = (l + r) / 2;
  if (mid < x) return get(o << 1 | 1, mid + 1, r, x);
  else return get(o << 1, l, mid, x);
}
int query(int o, int l, int r, int L, int R) {
  if (L <= l && r <= R) return msgv[o].s;
  if (~setv[o]) return 1;
  int mid = (l + r) / 2;
  if (mid < L) return query(o << 1 | 1, mid + 1, r, L, R);
  else if (mid >= R) return query(o << 1, l, mid, L, R);
  else
    return query(o << 1, l, mid, L, R) + query(o << 1 | 1, mid + 1, r, L, R)
      - (msgv[o << 1].r == msgv[o << 1 | 1].l);
}
void modify(int x, int y, int c) {
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
    set(1, 1, n, pos[top[x]], pos[x], c);
    x = fa[top[x]];
  }
  if (dep[x] > dep[y]) std::swap(x, y);
  set(1, 1, n, pos[x], pos[y], c);
}
int query(int x, int y) {
  int ans = 0;
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
    ans += query(1, 1, n, pos[top[x]], pos[x]);
    ans -= (get(1, 1, n, pos[top[x]]) == get(1, 1, n, pos[fa[top[x]]]));
    x = fa[top[x]];
  }
  if (dep[x] > dep[y]) std::swap(x, y);
  ans += query(1, 1, n, pos[x], pos[y]);
  return std::max(ans, 1);
}
int main() {
  int m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) scanf("%d", &color[i]);
  memset(pre, -1, sizeof pre);
  for (int i = 1, x, y; i < n; ++i) {
    scanf("%d%d", &x, &y);
    addEdge(x, y);
  }
  dfs0(1, 0);
  dfs1(1, 1);
  build(1, 1, n);
  while (m--) {
    char s[5];
    int x, y, z;
    scanf("%s%d%d", s, &x, &y);
    if (*s == 'C') {
      scanf("%d", &z);
      modify(x, y, z);
    } else
      printf("%d\n", query(x, y));
  }
  return 0;
}
