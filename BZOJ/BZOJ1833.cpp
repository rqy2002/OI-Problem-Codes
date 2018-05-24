/**************************************************************
 * Problem: BZOJ1833
 * Author: Rqy
 * Date: 2018 Feb 26
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
typedef long long LL;
const int N = 20;
LL f[N][2], g[N][2], n[N];
LL solve(LL m, int k) {
  int l = 0;
  while (m) n[l++] = m % 10, m /= 10;
  f[l][0] = 1; f[l][1] = g[l][0] = g[l][1] = 0;
  if (k) {
    for (int i = l - 1; ~i; --i) {
      f[i][0] = f[i + 1][0];
      f[i][1] = f[i + 1][0] * n[i] + f[i + 1][1] * 10;
      g[i][0] = g[i + 1][0] + (n[i] == k);
      g[i][1] = g[i + 1][0] * n[i] + (k < n[i]) + g[i + 1][1] * 10 + f[i + 1][1];
    }
    return g[0][0] + g[0][1];
  } else {
    for (int i = l - 1; ~i; --i) {
      f[i][0] = f[i + 1][0];
      f[i][1] = f[i + 1][0] * n[i] + f[i + 1][1] * 10;
      g[i][0] = g[i + 1][0] + (n[i] == k);
      g[i][1] = g[i + 1][0] * n[i] + (i + 1 != l && k < n[i]) + g[i + 1][1] * 10 + f[i + 1][1] - (i + 1 != l);
    }
    return g[0][0] + g[0][1];
  }
}
int main() {
  LL a, b;
  scanf("%lld%lld", &a, &b);
  for (int i = 0; i < 10; ++i) {
    if (i) printf(" ");
    printf("%lld", solve(b, i) - solve(a - 1, i));
  }
  return 0;
}
