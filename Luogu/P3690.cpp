/**************************************************************
 * Problem: Luogu P3690
 * Author: Rqy
 * Date: 2017 Dec 28
 * Algorithm: LCT
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 500050;
int A[N];
namespace LCT{
  int fa[N], ch[N][2], sx[N], st[N];
  bool rev[N];
#define lc ch[o][0]
#define rc ch[o][1]
  inline void pushd(int o) {
    if (rev[o]) { std::swap(lc, rc); rev[lc] ^= 1; rev[rc] ^= 1; rev[o] = 0; }
  }
  inline void upd(int o) { sx[o] = A[o] ^ sx[lc] ^ sx[rc]; }
  inline int dir(int o) { return ch[fa[o]][0] == o ? 0 :
                                  ch[fa[o]][1] == o ? 1 : -1; }
  inline void rotate(int o) {
    int f = fa[o], d = dir(o);
    fa[o] = fa[f];
    if (~dir(f)) ch[fa[f]][dir(f)] = o;
    if ((ch[f][d] = ch[o][d ^ 1])) fa[ch[f][d]] = f;
    upd(ch[o][d ^ 1] = f);
    upd(fa[f] = o);
  }
  void splay(int o) {
    int x = o, top = 0;
    while (~dir(x)) st[top++] = x = fa[x];
    while (top--) pushd(st[top]);
    pushd(o);
    for (; ~dir(o); rotate(o)) if (~dir(fa[o]))
      rotate(dir(o) == dir(fa[o]) ? fa[o] : o);
  }
  void access(int o) {
    splay(o);
    ch[o][1] = 0;
    upd(o);
    int f;
    while ((f = fa[o])) {
      splay(f);
      ch[f][1] = o;
      upd(o = f);
    }
  }
  inline void mkroot(int o) {
    access(o);
    splay(o);
    rev[o] ^= 1;
  }
  void link(int x, int y) {
    access(y);
    splay(y);
    access(x);
    splay(x);
    if (!fa[y]) fa[y] = x;
  }
  void cut(int x, int y) {
    mkroot(x);
    access(y);
    splay(y);
    if (ch[y][0] == x && !ch[x][1]) {
      fa[x] = 0;
      ch[y][0] = 0;
      upd(y);
    }
  }
  int query(int x, int y) {
    mkroot(x);
    access(y);
    splay(y);
    return sx[y];
  }
  void modify(int x, int y) {
    splay(x);
    A[x] = y;
    upd(x);
  }
};
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &A[i]);
    LCT::sx[i] = A[i];
  }
  int t, x, y;
  while (m--) {
    scanf("%d%d%d", &t, &x, &y);
    if (t == 0) printf("%d\n", LCT::query(x, y));
    else if (t == 1) LCT::link(x, y);
    else if (t == 2) LCT::cut(x, y);
    else LCT::modify(x, y);
  }
  return 0;
}
