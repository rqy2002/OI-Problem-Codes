#include <algorithm>
#include <cstdio>
using std::min;
using std::max;
const int N = 155;
const int K = 25;
const int mod = 12345678;
int f[N][N][K][K];
int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i <= k; ++i)
    for (int j = 0; j <= k; ++j)
      f[0][0][i][j] = 1;
  for (int ij = 1; ij <= n + m; ++ij)
    for (int i = max(ij - m, 0); i <= min(ij, n); ++i) {
      int j = ij - i;
      for (int a = 0; a <= k; ++a)
        for (int b = 0; b <= k; ++b) {
          f[i][j][a][b] = 0;
          if (i && a) f[i][j][a][b] += f[i - 1][j][a - 1][min(b + 1, k)];
          if (j && b) f[i][j][a][b] += f[i][j - 1][min(a + 1, k)][b - 1];
          f[i][j][a][b] %= mod;
        }
    }
  printf("%d\n", f[n][m][k][k]);
  return 0;
}
