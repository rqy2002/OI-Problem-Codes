/**************************************************************
 * Problem: Luogu P2764
 * Author: Rqy
 * Date: 2017 Dec 22
 * Algorithm: 匈牙利
**************************************************************/
#include <cstdio>
const int N = 155;
bool map[N][N];
int mx[N], my[N];
int visy[N], time;
int n;
bool dfs(int x) {
  for (int y = 1; y <= n; ++y) if (visy[y] != time && map[x][y]) {
    visy[y] = time;
    if (!my[y] || dfs(my[y])) {
      mx[my[y] = x] = y;
      return true;
    }
  }
  return false;
}
int main() {
  int m, x, y;
  scanf("%d%d", &n, &m);
  while (m--) {
    scanf("%d%d", &x, &y);
    map[x][y] = 1;
  }
  for (int i = 1; i <= n; ++i)
    if (!mx[i]) ++time, dfs(i);
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    if (!my[i]) {
      ++ans;
      for (int j = i; j; j = mx[j])
        printf("%d ", j);
      printf("\n");
    }
  printf("%d\n", ans);
  return 0;
}
