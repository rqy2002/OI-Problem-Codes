/**************************************************************
 * Problem: JCYZOJ 1015
 * Author: Rqy
 * Date: 2018 Feb 13
 * Algorithm: Persistence Union-Find-Set
**************************************************************/
#include <cstdio>
const int N = 200050;
const int NN = 7000050;
int n, m;
int tim[NN], lc[NN], rc[NN], fa[NN], hei[NN], cnt;
int root[N], cur;
int get(int o, int l, int r, int *A, int i) {
  if (l == r) return A[o];
  int mid = (l + r) >> 1;
  if (i <= mid) return get(lc[o], l, mid, A, i);
  else return get(rc[o], mid + 1, r, A, i);
}
void set(int &o, int l, int r, int *A, int i, int x) {
  if (tim[o] < cur) {
    lc[cnt] = lc[o]; rc[cnt] = rc[o]; fa[cnt] = fa[o]; hei[cnt] = hei[o];
    tim[o = cnt++] = cur;
  }
  if (l == r) {
    A[o] = x; return;
  }
  int mid = (l + r) >> 1;
  if (i <= mid) set(lc[o], l, mid, A, i, x);
  else set(rc[o], mid + 1, r, A, i, x);
}
int get(int *A, int i) { return get(root[cur], 1, n, A, i); }
void set(int *A, int i, int x) { set(root[cur], 1, n, A, i, x); }
int Find(int x) {
  int f = get(fa, x);
  return f ? Find(f) : x;
}
void Union(int x, int y) {
  x = Find(x); y = Find(y);
  if (x == y) return;
  int hx = get(hei, x), hy = get(hei, y);
  if (hx <= hy)
    set(fa, x, y);
  else 
    set(fa, y, x);
  if (hx == hy)
    set(hei, y, hx + 1);
}
int main() {
  scanf("%d%d", &n, &m);
  cnt = 1;
  root[0] = lc[0] = rc[0] = fa[0] = hei[0] = 0;
  int opt, x, y, la = 0;
  for (cur = 1; cur <= m; ++cur) {
    root[cur] = root[cur - 1];
    scanf("%d%d", &opt, &x);
    if (opt == 1) {
      scanf("%d", &y);
      Union(x ^ la, y ^ la);
    } else if (opt == 2)
      root[cur] = root[x ^ la];
    else {
      scanf("%d", &y);
      printf("%d\n", la = (Find(x ^ la) == Find(y ^ la)));
    }
  }
  return 0;
}
