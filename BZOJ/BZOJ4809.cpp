/**************************************************************
 * Problem: BZOJ4809
 * Author: Rqy
 * Date: 2018 Feb 24
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 16;
int l[N];
int n, ans = 0;
void dfs(int x, int A, int B, int C) {
  if (x == n) { ++ans; return; }
  for (register int able = l[x] & ~(A | B | C); able; able &= (able - 1)) {
    int t = able & -able;
    dfs(x + 1, A | t, (B | t) << 1, (C | t) >> 1);
  }
}
int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    for (int j = 0, x; j < n; ++j) {
      scanf("%d", &x);
      if (!x) l[i] |= (1 << j);
    }
  dfs(0, 0, 0, 0);
  printf("%d\n", ans);
  return 0;
}
