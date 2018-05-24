/**************************************************************
 * Problem: BZOJ5117
 * Author: Rqy
 * Date: 2018 Feb 27
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 500050;
typedef long long LL;
const LL INF = 10000000000000000LL;
inline LL& chk(LL &a, LL b) { if (a < b) a = b; return a; }
int A[N];
struct M{
  LL a, b, c, d;
  M() : a(0), b(-INF), c(0), d(-INF) {}
  void add(int x) { chk(c, chk(a += x, -INF)); chk(d, chk(b += x, 0LL)); }
  void set(int x) { chk(c, a = -INF); chk(d, b = x); }
  void merge(const M &m) {
    chk(c, a + m.c);
    chk(chk(d, b + m.c), m.d);
    chk(a += m.a, -INF);
    chk(b += m.a, m.b);
  }
}m[N * 4];
void pushd(int o, int l, int r) {
  if (l == r) return;
  m[o << 1].merge(m[o]);
  m[o << 1 | 1].merge(m[o]);
  m[o] = M();
}
void add(int o, int l, int r, int L, int R, int x) {
  if (l > R || L > r) return;
  if (L <= l && r <= R) { m[o].add(x); return; }
  pushd(o, l, r);
  int mid = (l + r) / 2;
  add(o << 1, l, mid, L, R, x);
  add(o << 1 | 1, mid + 1, r, L, R, x);
}
void set(int o, int l, int r, int L, int R, int x) {
  if (l > R || L > r) return;
  if (L <= l && r <= R) { m[o].set(x); return; }
  pushd(o, l, r);
  int mid = (l + r) / 2;
  set(o << 1, l, mid, L, R, x);
  set(o << 1 | 1, mid + 1, r, L, R, x);
}
LL query1(int o, int l, int r, int x) {
  if (l == r) return std::max(m[o].a + A[x], m[o].b);
  pushd(o, l, r);
  int mid = (l + r) / 2;
  return x <= mid
    ? query1(o << 1, l, mid, x)
    : query1(o << 1 | 1, mid + 1, r, x);
}
LL query2(int o, int l, int r, int x) {
  if (l == r) return std::max(m[o].c + A[x], m[o].d);
  pushd(o, l, r);
  int mid = (l + r) / 2;
  return x <= mid
    ? query2(o << 1, l, mid, x)
    : query2(o << 1 | 1, mid + 1, r, x);
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) scanf("%d", &A[i]);
  while (m--) {
    int op;
    scanf("%d", &op);
    if (op <= 3) {
      int l, r, x;
      scanf("%d%d%d", &l, &r, &x);
      if (op == 1) add(1, 1, n, l, r, x);
      if (op == 2) add(1, 1, n, l, r, -x);
      if (op == 3) set(1, 1, n, l, r, x);
    } else {
      int x;
      scanf("%d", &x);
      printf("%lld\n", op == 4 ? query1(1, 1, n, x) : query2(1, 1, n, x));
    }
  }
  return 0;
}
