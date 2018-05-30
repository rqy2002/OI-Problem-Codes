#include <algorithm>
#include <cstdio>
const int N = 60;
int a[N];
double f[N][N];
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  double p = 1.0 / m;
  for (int i = 0; i < m; ++i) scanf("%d", &a[i]), --a[i];
  f[1][0] = 1.0;
  for (int i = 2; i <= n; ++i)
    for (int j = 0; j < m; ++j)
      for (int l = a[j] % i + 1, k = 0; k < i - 1; ++k)
        f[i][(l + k) % i] += p * f[i - 1][k];
  for (int i = 0; i < n; ++i) {
    if (i) putchar(' ');
    printf("%.2lf%%", f[n][i] * 100.0);
  }
  return 0;
}
