#include <algorithm>
#include <cstdio>
using std::min;
const int N = 105;
const int M = 25;
const int E = M * M;
typedef long long LL;
const LL INF = 1e15;
int from[E], to[E];
LL cost[E], dis[M][M];
int S[E][N];
int n, m, e;
inline bool test(int x, int t1, int t2) {
  return S[x][t1 - 1] == S[x][t2];
}
inline LL calcDis(int t1, int t2) {
  for (int i = 1; i <= m; ++i)
    for (int j = 1; j <= m; ++j)
      dis[i][j] = i == j ? 0 : INF;
  for (int i = 0; i < e; ++i)
    if (test(from[i], t1, t2) && test(to[i], t1, t2) && cost[i] < dis[from[i]][to[i]])
      dis[from[i]][to[i]] = dis[to[i]][from[i]] = cost[i];
  for (int k = 1; k <= m; ++k) 
    for (int i = 1; i <= m; ++i)
      for (int j = 1; j <= m; ++j)
        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
  return dis[1][m];
}
LL Dis[N][N];
void calcDis() {
  for (int i = 1; i <= n; ++i)
    for (int j = i; j <= n; ++j)
      Dis[i][j] = calcDis(i, j);
}
LL f[N];
int main() {
  int k, i, j;
  scanf("%d%d%d%d", &n, &m, &k, &e);
  for (i = 0; i < e; ++i) scanf("%d%d%lld", &from[i], &to[i], &cost[i]);
  int d;
  scanf("%d", &d);
  while (d--) {
    int p, a, b;
    scanf("%d%d%d", &p, &a, &b);
    ++S[p][a];
    --S[p][b + 1];
  }
  for (i = 1; i <= m; ++i) {
    for (j = 1; j <= n; ++j)
      S[i][j] += S[i][j - 1];
    for (j = 1; j <= n; ++j)
      S[i][j] += S[i][j - 1];
  }
  calcDis();
  f[0] = -k;
  for (i = 1; i <= n; ++i)
    for (j = 0, f[i] = INF; j < i; ++j)
      f[i] = min(f[i], f[j] + Dis[j + 1][i] * (i - j) + k);
  printf("%lld
", f[n]);
  return 0;
}
