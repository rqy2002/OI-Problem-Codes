#include <cstdio>
const int N = 9;
const int K = 25 + 1;
typedef long long LL;
LL _f[2][89][K], (*f)[K] = _f[0], (*g)[K] = _f[1], (*tmp)[K], ans;
int siz[1 << N], n, k, all, m, i, j, t, l, s;
inline bool check1(int x) {
  if (x & (x >> 1)) return false;
  return true;
}
inline bool check2(int x, int y) {
  if (x & y) return false;
  return check1(x | y);
}
int vaild[89];
int main() {
  scanf("%d%d", &n, &k);
  if (k >= K) return puts("0") & 0;
  all = (1 << n) - 1;
  for (s = 0; s < all; ++s)
    for (j = 1; j < all && (~s & j); j <<= 1)
      siz[s | j] = siz[s] + 1;
  m = 0;
  for (s = 0; s <= all; ++s)
    if (check1(s)) vaild[m++] = s;
  f[0][0] = 1;
  for (i = 0; i < n; ++i) {
    for (j = 0; j < m; ++j)
      for (t = 0; t <= k; ++t)
        g[j][t] = 0;
    for (j = 0; j < m; ++j)
      for (t = 0; t < m; ++t) if (check2(vaild[j], vaild[t]))
        for (s = siz[vaild[t]], l = 0; l + s <= k; ++l)
          g[t][l + s] += f[j][l];
    tmp = f;
    f = g;
    g = tmp;
  }
  ans = 0;
  for (i = 0; i < m; ++i)
    ans += f[i][k];
  printf("%lld\n", ans);
  return 0;
}
