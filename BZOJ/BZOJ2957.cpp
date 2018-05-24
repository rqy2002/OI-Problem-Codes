/**************************************************************
 * Problem: BZOJ2957
 * Author: Rqy
 * Date: 2018 Feb 23
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 100050;
typedef long long LL;
struct Frac{
  int x, y;
  Frac(int x = 1, int y = 0) : x(x), y(y) {}
  bool operator<(const Frac &f) const {
    return (LL)y * f.x < (LL)f.y * x;
  }
}maxv[N * 4];
int lenv[N * 4], Y[N];
int query(int o, int l, int r, Frac x) {
  if (!(x < maxv[o])) return 0;
  if (l == r) return 1;
  int mid = (l + r) / 2;
  return maxv[o << 1] < x
    ? query(o << 1 | 1, mid + 1, r, x)
    : query(o << 1, l, mid, x) + lenv[o] - lenv[o << 1];
}
void upd(int o, int l, int r) {
  if (l == r) {
    lenv[o] = 1;
    maxv[o] = Frac(l, Y[l]);
  } else {
    int lc = o << 1, rc = o << 1 | 1, mid = (l + r) / 2;
    maxv[o] = std::max(maxv[lc], maxv[rc]);
    lenv[o] = lenv[lc] + query(rc, mid + 1, r, maxv[lc]);
  }
}
void modify(int o, int l, int r, int x, int y) {
  if (l > x || r < x) return;
  if (l == r)
    Y[x] = y;
  else {
    int mid = (l + r) / 2;
    modify(o << 1, l, mid, x, y);
    modify(o << 1 | 1, mid + 1, r, x, y);
  }
  upd(o, l, r);
}
void build(int o, int l, int r) {
  maxv[o] = Frac(l, 0); lenv[o] = 1;
  if (l != r) {
    int mid = (l + r) / 2;
    build(o << 1, l, mid);
    build(o << 1 | 1, mid + 1, r);
  }
}
int main() {
  int n, m, x, y;
  scanf("%d%d", &n, &m);
  build(1, 1, n);
  while (m--) {
    scanf("%d%d", &x, &y);
    modify(1, 1, n, x, y);
    printf("%d\n", query(1, 1, n, Frac()));
  }
  return 0;
}
