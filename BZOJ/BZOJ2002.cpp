/**************************************************************
 * Problem: BZOJ2002
 * Author: Rqy
 * Date: 2017 Dec 21
 * Algorithm: LCT
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 200050;
namespace LCT{
  int fa[N], ch[N][2], siz[N];
  bool rev[N];

  void init(int n) {
    for (int i = 0; i <= n; ++i) {
      ch[i][0] = ch[i][1] = fa[i] = 0;
      siz[i] = (i != 0);
      rev[i] = false;
    }
  }

  inline void pushd(int x) {
    if (rev[x]) {
      rev[x] = 0;
      rev[ch[x][0]] ^= 1;
      rev[ch[x][1]] ^= 1;
      std::swap(ch[x][0], ch[x][1]);
    }
  }

  inline void upd(int x) { siz[x] = 1 + siz[ch[x][0]] + siz[ch[x][1]]; }

  inline int dir(int x) {
    return ch[fa[x]][0] == x ? 0 : ch[fa[x]][1] == x ? 1 : -1;
  }

  inline void rotate(int x) {
    int f = fa[x], d = dir(x);
    fa[x] = fa[f];
    if (~dir(f)) ch[fa[x]][dir(f)] = x;
    if ((ch[f][d] = ch[x][d ^ 1])) fa[ch[f][d]] = f;
    upd(ch[x][d ^ 1] = f);
    upd(fa[f] = x);
  }

  int stack[N];
  void splay(int x) {
    int top = 0;
    for (int i = x; ~dir(i); i = fa[i]) stack[top++] = i;
    while (top--) pushd(fa[stack[top]]);
    pushd(x);
    for (; ~dir(x); rotate(x))
      if (~dir(fa[x])) rotate(dir(x) == dir(fa[x]) ? fa[x] : x);
  }

  void access(int x) {
    splay(x);
    ch[x][1] = 0;
    upd(x);
    int y;
    while ((y = fa[x])) {
      splay(y);
      ch[y][1] = x;
      upd(x = y);
    }
  }

  inline void mkroot(int x) {
    access(x);
    splay(x);
    rev[x] ^= 1;
  }

  inline void link(int x, int y) {
    access(x);
    splay(x);
    fa[x] = y;
  }

  inline void cut(int x, int y) {
    mkroot(x);
    access(y);
    splay(y);
    fa[ch[y][0]] = 0;
    ch[y][0] = 0;
    upd(y);
  }

  inline int query(int x, int y) {
    mkroot(y);
    access(x);
    splay(x);
    return siz[x];
  }
};

int k[N];
int main() {
  freopen("bzoj_2002.in", "r", stdin);
  freopen("bzoj_2002.out", "w", stdout);
  int n, m;
  scanf("%d", &n);
  LCT::init(n + 1);

  for (int i = 1; i <= n; ++i) {
    scanf("%d", &k[i]);
    LCT::link(i, k[i] = std::min(k[i] + i, n + 1));
  }

  scanf("%d", &m);

  int op, x, y;
  while (m--) {
    scanf("%d%d", &op, &x);
    ++x;
    if (op == 1) printf("%d\n", LCT::query(x, n + 1) - 1);
    else {
      scanf("%d", &y);
      LCT::cut(x, k[x]);
      LCT::link(x, k[x] = std::min(y + x, n + 1));
    }
  }
  return 0;
}
