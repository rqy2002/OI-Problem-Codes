/**************************************************************
 * Problem: BZOJ4443
 * Author: Rqy
 * Date: 2018 Feb 27
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 300;
int A[N][N], n, m;
bool able[N][N], vis[N];
int my[N];
bool dfs(int x) {
  for (int y = 1; y <= m; ++y) if (able[x][y] && !vis[y]) {
    vis[y] = true;
    if (!my[y] || dfs(my[y])) {
      my[y] = x;
      return true;
    }
  }
  return false;
}
int calc(int x) {
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      able[i][j] = (A[i][j] <= x);
  memset(my, 0, sizeof my);
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    memset(vis, 0, sizeof vis);
    ans += dfs(i);
  }
  return ans;
}
int main() {
  int k;
  scanf("%d%d%d", &n, &m, &k);
  k = n - k + 1;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      scanf("%d", &A[i][j]);
  int l = 0, r = 1000000000;
  while (l < r) {
    int mid = (l + r) / 2;
    if (calc(mid) >= k) r = mid;
    else l = mid + 1;
  }
  printf("%d\n", l);
  return 0;
}
