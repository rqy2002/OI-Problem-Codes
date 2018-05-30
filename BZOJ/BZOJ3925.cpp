#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 10;
const int M = 45 + 1;
bool vis[1 << N][M];
int siz[1 << N], link[N];
double f[1 << N][M];
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  int lim = 1 << n;
  for (int i = 0, x, y; i < m; ++i) {
    scanf("%d%d", &x, &y);
    --x; --y;
    link[x] |= (1 << y);
    link[y] |= (1 << x);
  }
  for (int S = 1; S < lim; ++S) siz[S] = siz[S & (S - 1)] + 1;
  for (int S1 = 3; S1 < lim; ++S1) if (S1 & 1) {
    for (int S2 = (S1 - 1) & S1; S2 != 0; S2 = (S2 - 1) & S1) if (S2 & 1) {
      int T = 0;
      for (int i = 0; i < n; ++i) if ((S1 >> i) & (~S2 >> i) & 1)
        T += siz[link[i] & S2];
      for (int i = 0; i + T <= m; ++i)
        f[S1][i] += 1.0 / (i + T + 1) - f[S2][i + T];
    }
  }
  printf("%.6lf\n", f[lim - 1][0]);
  return 0;
}
