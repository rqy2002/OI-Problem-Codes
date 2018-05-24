/**************************************************************
 * Problem: BZOJ3626
 * Author: Rqy
 * Date: 2018 Feb 22
 * Algorithm: 分块
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
const int N = 50050;
const int B = 300;
const int mod = 201314;
int ls[N], rb[N], pos[N], minv[20][N * 2], min2[N * 2];
int fa[N], n, cnt = 0;
void dfs0(int x, int d) {
  minv[0][pos[x] = cnt++] = d;
  for (int i = ls[x]; i; i = rb[i]) {
    dfs0(i, d + 1);
    if (rb[i]) minv[0][cnt++] = d;
  }
}
void work() {
  for (int i = 0, k = 1; k < cnt; ++i, k <<= 1) {
    for (int j = 0; j + k <= cnt; ++j)
      minv[i + 1][j] = std::min(minv[i][j], minv[i][j + k]);
    for (int j = k; j < (k << 1); ++j) min2[j] = i;
  }
}
int d(int x, int y) {
  x = pos[x]; y = pos[y];
  if (x > y) std::swap(x, y);
  int k = min2[y - x + 1];
  return std::min(minv[k][x], minv[k][y - (1 << k) + 1]);
}
int siz[N];
int dfs1(int x, int b) {
  siz[x] = (x / B == b);
  for (int i = ls[x]; i; i = rb[i]) siz[x] += dfs1(i, b);
  return siz[x];
}
int ans[N / B + 2][N];
void dfs2(int x, int b, int v) {
  ans[b][x] = ((v += siz[x]) %= mod) + (b ? ans[b - 1][x] : 0);
  if (ans[b][x] > mod) ans[b][x] -= mod;
  for (int i = ls[x]; i; i = rb[i]) dfs2(i, b, v);
}
int main() {
  int q;
  scanf("%d%d", &n, &q);
  memset(fa, -1, sizeof fa);
  for (int i = 1; i < n; ++i) {
    scanf("%d", &fa[i]);
    rb[i] = ls[fa[i]]; ls[fa[i]] = i;
  }
  dfs0(0, 1);
  work();
  for (int b = 0; b * B < n; ++b) { dfs1(0, b); dfs2(0, b, 0); }
  for (int l, r, x; q; --q) {
    scanf("%d%d%d", &l, &r, &x);
    int lb = (l + B - 1) / B, rb = r / B;
    long long ansv = 0;
    if (lb <= rb) {
      ansv = (ans[rb - 1][x] - (lb ? ans[lb - 1][x] : 0) + mod) % mod;
      for (int i = l; i < lb * B; ++i) ansv += d(i, x);
      for (int i = rb * B; i <= r; ++i) ansv += d(i, x);
    } else
      for (int i = l; i <= r; ++i) ansv += d(i, x);
    printf("%d\n", (int)(ansv % mod));
  }
  return 0;
}

