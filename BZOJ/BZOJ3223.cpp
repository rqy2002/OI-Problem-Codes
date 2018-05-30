#include <algorithm>
#include <cstdio>
const int N = 100050;
int fa[N], son[N][2];
bool rev[N];
int siz[N];
inline int dir(int x) { return son[fa[x]][1] == x; }
inline void pd(int x) {
  if (rev[x]) {
    std::swap(son[x][0], son[x][1]);
    rev[son[x][0]] ^= 1;
    rev[son[x][1]] ^= 1;
  }
  rev[x] = 0;
}
inline void upd(int x) { siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1; }
void rotate(int x) {
  int f = fa[x], d = dir(x);
  if (fa[x] = fa[f]) son[fa[x]][dir(f)] = x;
  if (son[f][d] = son[x][d ^ 1]) fa[son[f][d]] = f;
  fa[son[x][d ^ 1] = f] = x;
  upd(f);
  upd(x);
}
int st[N];
void splay(int x, int g = 0) {
  int top = 0;
  for (int i = x; fa[i]; i = fa[i])
    st[top++] = fa[i];
  while (top--) pd(st[top]);
  pd(x);
  for (; fa[x] != g; rotate(x))
    if (fa[fa[x]] != g) rotate(dir(fa[x]) == dir(x) ? fa[x] : x);
}
int kth(int k, int t) {
  int o = t;
  while (1) {
    pd(o);
    if (siz[son[o][0]] == k - 1) break;
    else if (siz[son[o][0]] >= k) o = son[o][0];
    else {
      k -= siz[son[o][0]] + 1;
      o = son[o][1];
    }
  }
  splay(o, fa[t]);
  return o;
}
int n;
void reverse(int l, int r) {
  splay(1);
  int y = kth(r + 1, 1);
  int x = son[y][0];
  kth(l - 1, x);
  rev[son[son[y][0]][1]] ^= 1;
}
void put(int o) {
  pd(o);
  if (!o) return;
  put(son[o][0]);
  if (o != 1 && o != n + 2) printf("%d ", o - 1);
  put(son[o][1]);
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n + 2; ++i) {
    if (fa[i] = i - 1) son[i - 1][1] = i;
    siz[i] = n - i + 3;
    rev[i] = 0;
  }
  int m, l, r;
  scanf("%d", &m);
  while (m--) {
    scanf("%d%d", &l, &r);
    reverse(l + 1, r + 1);
  }
  splay(1);
  put(1);
}
