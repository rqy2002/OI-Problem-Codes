/**************************************************************
 * Problem: Luogu P2473
 * Author: Rqy
 * Date: 2017 Dec 23
 * Algorithm: 期望概率
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 16;
const int K = 105;
double f[K][1 << N];
int P[K], S[K];
int main() {
  int n, k;
  scanf("%d%d", &k, &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &P[i]);
    int x;
    S[i] = 0;
    while (~scanf("%d", &x) && x)
      S[i] |= (1 << (x - 1));
  }
  std::fill(f[0], f[1], .0);
  int lim = 1 << n;
  double p1 = 1.0 / n;
  for (int i = 1; i <= k; ++i)
    for (int SS = 0; SS < lim; ++SS) {
      f[i][SS] = .0;
      for (int p = 0; p < n; ++p)
        f[i][SS] += p1 * std::max(f[i - 1][SS],
            ((S[p] & SS) == S[p]) * (f[i - 1][SS | (1 << p)] + P[p]));
    }
  printf("%.6lf", f[k][0]);
  return 0;
}
