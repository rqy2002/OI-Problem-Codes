#include <algorithm>
#include <cmath>
#include <cstdio>
using std::min;
typedef double LL;
const int N = 15;
LL s[N][N], f[N][N][N][N][N];
inline LL sqr(LL x) {
  return x * x;
}
inline LL sum(int l, int r, int u, int d) {
  return s[d][r] - s[d][l - 1] - s[u - 1][r] + s[u - 1][l - 1];
}
int main() {
  int a, b, n;
  scanf("%d%d%d", &a, &b, &n);
  for (int i = 1; i <= a; ++i)
    for (int j = 1; j <= b; ++j) {
      scanf("%lf", &s[i][j]);
      s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
    }
  for (int u = 1; u <= a; ++u)
    for (int d = u; d <= a; ++d)
      for (int l = 1; l <= b; ++l)
        for (int r = l; r <= b; ++r)
          f[1][u][d][l][r] = sqr(sum(l, r, u, d));
  for (int k = 2; k <= n; ++k)
    for (int hei = 1; hei <= a; ++hei)
      for (int u = 1; u + hei - 1 <= a; ++u) {
        int d = u + hei - 1;
        for (int wid = 1; wid <= b; ++wid)
          for (int l = 1; l + wid - 1 <= b; ++l) {
            int r = l + wid - 1;
            LL &ans = f[k][u][d][l][r];
            ans = 1000000000000000000LL;
            for (int k1 = 1; k1 < k; ++k1) {
              int k2 = k - k1;
              for (int i = u + 1; i <= d; ++i)
                ans = min(ans, f[k1][u][i - 1][l][r] + f[k2][i][d][l][r]);
              for (int j = l + 1; j <= r; ++j)
                ans = min(ans, f[k1][u][d][l][j - 1] + f[k2][u][d][j][r]);
            }
          }
      }
  printf("%.2lf\n", sqrt(f[n][1][a][1][b] / n - sqr(s[a][b] / n)));
  return 0;
}
