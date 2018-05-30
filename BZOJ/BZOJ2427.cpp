#include <algorithm>
#include <cstdio>
#include <queue>
using std::max;
const int N = 105;
const int M = 505;
const int INF = 998244353;
int D[N], W[N], V[N], F[N];
int vis[N];  // 0: not visited. 1: visiting. 2: visited.
int deg[N], n, m;
void dfs(int x) {
  if (vis[x] == 1) {
    for (int i = D[x]; i != x; i = D[i]) {
      W[x] += W[i];
      V[x] += V[i];
      F[i] = x;
    }
    F[x] = x;
    D[x] = 0;
  } else if (!vis[x]) {
    vis[x] = 1;
    dfs(D[x]);
    if (!F[x]) F[x] = x;
  }
  vis[x] = 2;
}
std::queue<int> Q;
int f[N][M];
int solve() {
  std::fill(vis, vis + n + 1, 0);
  std::fill(F, F + n + 1, 0);
  int i;
  for (i = 1; i <= n; ++i)
    if (!vis[i]) dfs(i);
  F[0] = 0;
  for (i = 1; i <= n; ++i)
    if (F[i] == i) ++deg[D[i] = F[D[i]]];
  while (!Q.empty()) Q.pop();
  for (i = 1; i <= n; ++i)
    if (F[i] == i) {
      if (!deg[i]) Q.push(i);
      std::fill(f[i], f[i] + m + 1, -INF);
      f[i][W[i]] = V[i];
    }
  deg[0] = n + 1;
  std::fill(f[0], f[0] + m + 1, 0);
  while (!Q.empty()) {
    int x = Q.front();
    Q.pop();
    for (int i = m; i >= 0; --i)
      for (int j = 0; i + j <= m; ++j)
        f[D[x]][i + j] = max(f[D[x]][i + j], f[D[x]][i] + f[x][j]);
    if (!--deg[D[x]]) Q.push(D[x]);
  }
  return f[0][m];
}
int main() {
  // freopen("install.in", "r", stdin);
  // freopen("install.out", "w", stdout);
  scanf("%d%d", &n, &m);
  int i;
  for (i = 1; i <= n; ++i) scanf("%d", &W[i]);
  for (i = 1; i <= n; ++i) scanf("%d", &V[i]);
  for (i = 1; i <= n; ++i) scanf("%d", &D[i]);
  printf("%d\n", solve());
  return 0;
}
