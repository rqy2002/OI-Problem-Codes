#include <algorithm>
#include <cstdio>
using std::fill;
using std::min;
using std::max;
const int N = 600;
const int INF = 998244353;
int n, m;
int w[N][N];
int lx[N], ly[N], link[N], slack[N];
int visx[N], visy[N], dfsnum;
bool dfs(int x) {
  visx[x] = dfsnum;
  for (int y = 0; y < n; ++y)
    if (visy[y] < dfsnum) {
      int t = lx[x] + ly[y] - w[x][y];
      if (!t) {
        visy[y] = dfsnum;
        if (link[y] < 0 || dfs(link[y])) {
          link[y] = x;
          return true;
        }
      } else
        slack[y] = min(slack[y], t);
    }
  return false;
}
int solve() {
  std::fill(link, link + N, -1);
  dfsnum = 0;
  std::fill(visx, visx + N, 0);
  std::fill(visy, visy + N, 0);
  for (int i = 0; i < n; ++i) {
    lx[i] = -INF;
    for (int j = 0; j < n; ++j) lx[i] = max(lx[i], w[i][j]);
  }
  std::fill(ly, ly + N, 0);
  for (int x = 0; x < n; ++x) {
    std::fill(slack, slack + N, INF);
    while (1) {
      ++dfsnum;
      if (dfs(x)) break;
      int d = INF;
      for (int i = 0; i < n; ++i)
        if (visy[i] < dfsnum) d = min(d, slack[i]);
      for (int i = 0; i < n; ++i)
        if (visx[i] == dfsnum) lx[i] -= d;
      for (int i = 0; i < n; ++i)
        if (visy[i] == dfsnum)
          ly[i] += d;
        else
          slack[i] -= d;
    }
  }
  int ans = 0;
  for (int i = 0; i < n; ++i) ans += w[link[i]][i];
  return ans;
}
int main() {
  int n2;
  scanf("%d%d", &m, &n2);
  int x;
  for (int j = 0; j < n2; ++j)
    for (int i = 0; i < m; ++i) {
      scanf("%d", &x);
      for (int k = 0; k < n2; ++k) w[j][i * n2 + k] = -x * (k + 1);
    }
  n = n2 * m;
  printf("%.2lf\n", -1.0 * solve() / n2);
  return 0;
}
