/**************************************************************
 * Problem: BZOJ5020
 * Author: Rqy
 * Date: 2018 Feb 27
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cmath>
#include <cassert>
#include <cstdio>
const int N = 100050;
const int K = 20;
struct Func{
  double A[K];
  Func() {}
  Func(int tp, double a, double b) {
    if (tp == 1) {
      double f = sin(b);
      for (int i = 0; i < K; i += 2, f *= -a * a)
        A[i] = f;
      f = a * cos(b);
      for (int i = 1; i < K; i += 2, f *= -a * a)
        A[i] = f;
    } else if (tp == 2) {
      double f = exp(b);
      for (int i = 0; i < K; ++i, f *= a)
        A[i] = f;
    } else {
      A[0] = b; A[1] = a;
      for (int i = 2; i < K; ++i) A[i] = 0;
    }
  }
  friend Func operator+(const Func &a, const Func &b) {
    Func ans;
    for (int i = 0; i < K; ++i) ans.A[i] = a.A[i] + b.A[i];
    return ans;
  }
  double operator()(double x) const {
    double ans = 0, f = 1.0;
    for (int i = 0; i < K; f *= x / (++i)) ans += A[i] * f;
    return ans;
  }
}fc[N], sv[N];
int fa[N], ch[N][2];
bool rev[N];
inline void upd(int o) { sv[o] = sv[ch[o][0]] + sv[ch[o][1]] + fc[o]; }
inline void pushd(int o) {
  if (rev[o]) {
    rev[ch[o][0]] ^= 1;
    rev[ch[o][1]] ^= 1;
    std::swap(ch[o][0], ch[o][1]);
    rev[o] = 0;
  }
}
inline int dir(int o) {
  return ch[fa[o]][0] == o ? 0 : ch[fa[o]][1] == o ? 1 : -1;
}
void rotate(int x) {
  int d = dir(x), f = fa[x];
  fa[x] = fa[f];
  if (~dir(f)) ch[fa[f]][dir(f)] = x;
  if ((ch[f][d] = ch[x][d ^ 1])) fa[ch[f][d]] = f;
  upd(ch[x][d ^ 1] = f);
  upd(fa[f] = x);
}
void splay(int x) {
  static int stack[N];
  int top = 0;
  for (int y = x; ~dir(y); y = fa[y]) stack[top++] = fa[y];
  while (top--) pushd(stack[top]);
  pushd(x);
  for (; ~dir(x); rotate(x))
    if (~dir(fa[x])) rotate(dir(x) == dir(fa[x]) ? fa[x] : x);
}
void access(int x) {
  splay(x); ch[x][1] = 0; upd(x); int f;
  while ((f = fa[x])) { splay(f); ch[f][1] = x; upd(x = f); }
}
inline void mkroot(int x) { access(x); splay(x); rev[x] ^= 1; }
inline void link(int x, int y) { mkroot(x); fa[x] = y; }
inline void cut(int x, int y) {
  mkroot(x); access(y); splay(y); fa[x] = ch[y][0] = 0; upd(y);
}
inline void modify(int x, int tp, double a, double b) {
  splay(x); fc[x] = Func(tp, a, b); upd(x);
}
int main() {
  int n, m;
  scanf("%d%d%*s", &n, &m);
  for (int i = 1; i <= n; ++i) {
    int tp;
    double x, y;
    scanf("%d%lf%lf", &tp, &x, &y);
    sv[i] = fc[i] = Func(tp, x, y);
  }
  char s[20];
  while (m--) {
    int x, y;
    scanf("%s%d%d", s, &x, &y);
    if (*s == 'a') link(x + 1, y + 1);
    else if (*s == 'd') cut(x + 1, y + 1);
    else if (*s == 'm') {
      double a, b;
      scanf("%lf%lf", &a, &b);
      modify(x + 1, y, a, b);
    } else {
      double x0;
      scanf("%lf", &x0);
      ++x; ++y;
      mkroot(x); access(y); splay(y);
      if (!fa[x] && x != y) puts("unreachable");
      else printf("%.8le\n", sv[y](x0));
    }
  }
  return 0;
}
