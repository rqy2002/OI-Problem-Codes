/**************************************************************
 * Problem: BZOJ2435.cpp
 * Author: Rqy
 * Date: 2018 Feb 28
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 1000050;
typedef long long LL;
int pre[N], to[N * 2], nxt[N * 2], c[N * 2], cnt, n;
inline void addEdge(int x, int y, int v) {
  nxt[cnt] = pre[x];
  c[cnt] = v;
  to[pre[x] = cnt++] = y;
}
LL ans = 0;
LL abs(LL x) { return x < 0 ? -x : x; }
int dfs(int x, int fa) {
  int siz = 1;
  for (int i = pre[x]; ~i; i = nxt[i])
    if (to[i] != fa) {
      int u = dfs(to[i], x);
      ans += (LL)abs(n - 2 * u) * c[i];
      siz += u;
    }
  return siz;
}
int main() {
  scanf("%d", &n);
  memset(pre, -1, sizeof pre);
  for (int i = 1, x, y, z; i < n; ++i) {
    scanf("%d%d%d", &x, &y, &z);
    addEdge(x, y, z);
    addEdge(y, x, z);
  }
  dfs(1, 0);
  printf("%lld\n", ans);
  return 0;
}
