/**************************************************************
 * Problem: BZOJ1054
 * Author: Rqy
 * Date: 2018 Feb 25
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 16;
int n, x[N], y[N], a[N], b[N];
inline int abs(int x) { return x < 0 ? -x : x; }
inline int v(int i, int j) { return abs(x[i] - a[j]) + abs(y[i] - b[j]); }
int sx[N], sy[N], my[N];
bool vx[N], vy[N];
bool dfs(int x) {
  vx[x] = true;
  for (int y = 0; y < n; ++y) if (!vy[y] && v(x, y) == sx[x] + sy[y]) {
    vy[y] = true;
    if (!~my[y] || dfs(my[y])) {
      my[y] = x;
      return true;
    }
  }
  return false;
}
bool check() {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (sx[i] + sy[j] > v(i, j))
        return false;
  return true;
}
int solve() {
  for (int i = 0; i < n; ++i) {
    sx[i] = 100; sy[i] = 0; my[i] = -1;
    for (int j = 0; j < n; ++j)
      sx[i] = std::min(sx[i], v(i, j));
  }
  for (int i = 0; i < n; ++i)
    while (true) {
      for (int j = 0; j < n; ++j) vx[j] = vy[j] = 0;
      if (dfs(i)) break;
      int d = 100;
      for (int j = 0; j < n; ++j) if (vx[j])
        for (int k = 0; k < n; ++k) if (!vy[k])
          d = std::min(d, v(j, k) - sx[j] - sy[k]);
      for (int j = 0; j < n; ++j) if (vx[j]) sx[j] += d;
      for (int j = 0; j < n; ++j) if (vy[j]) sy[j] -= d;
    }
  int ans = 0;
  for (int i = 0; i < n; ++i) ans += sx[i] + sy[i];
  return ans;
}
int main() {
  for (int i = 0; i < 4; ++i)
    for (int j = 0, t; j < 4; ++j) {
      scanf("%1d", &t);
      if (t) {
        x[n] = i;
        y[n] = j;
        ++n;
      }
    }
  for (int i = 0, m = 0; i < 4; ++i)
    for (int j = 0, t; j < 4; ++j) {
      scanf("%1d", &t);
      if (t) {
        a[m] = i;
        b[m] = j;
        ++m;
      }
    }
  printf("%d\n", solve());
}
