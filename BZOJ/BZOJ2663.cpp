/**************************************************************
 * Problem: BZOJ2663
 * Author: Rqy
 * Date: 2018 Feb 22
 * Algorithm: 二分, 匈牙利
**************************************************************/
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
const int N = 55;
int X[N], Y[N], x[N], y[N];
int n, K, R;
inline int sqr(int x) { return x * x; }
bool check(int i, int j, bool max) {
  int l = sqr(X[i] - x[j]) + sqr(Y[i] - y[j]);
  return max ? l >= R : l <= R;
}
int my[N];
bool vis[N];
bool dfs(int x, bool max) {
  for (int y = 1; y <= n; ++y) if (!vis[y]) {
    bool l = check(x, y, max);
    if (!l) continue;
    vis[y] = true;
    if (!my[y] || dfs(my[y], max)) {
      my[y] = x;
      return true;
    }
  }
  return false;
}
bool check(int mid, bool max) {
  R = mid;
  memset(my, 0, sizeof my);
  int ans = 0;
  for (int x = 1; x <= n; ++x) {
    memset(vis, 0, sizeof vis);
    if (dfs(x, max)) ++ans;
  }
  return max ? n - ans <= K : ans >= K;
}
int main() {
  scanf("%d%d", &n, &K);
  for (int i = 1; i <= n; ++i) scanf("%d%d", &X[i], &Y[i]);
  for (int i = 1; i <= n; ++i) scanf("%d%d", &x[i], &y[i]);
  int l = 0, r = 10000000;
  while (l < r) {
    int mid = (l + r) / 2;
    if (check(mid, false)) r = mid;
    else l = mid + 1;
  }
  printf("%.2lf ", sqrt(l));
  if (K == n) { puts("+INF"); return 0; }
  l = 0, r = 10000000;
  while (l < r) {
    int mid = r + (l - r) / 2;
    if (check(mid, true)) l = mid;
    else r = mid - 1;
  }
  printf("%.2lf\n", sqrt(l));
  return 0;
}
