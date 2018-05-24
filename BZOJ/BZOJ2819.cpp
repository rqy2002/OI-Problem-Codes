/**************************************************************
 * Problem: BZOJ2819
 * Author: Rqy
 * Date: 2018 Mar 01
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 500050;
int pre[N], nxt[N * 2], to[N * 2], cnt;
inline void addEdge(int x, int y) {
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
  nxt[cnt] = pre[y];
  to[pre[y] = cnt++] = x;
}
int dep[N], fa[N][20], pos[N], A[N], cnt2;
void dfs(int x, int f) {
  dep[x] = dep[fa[x][0] = f] + 1;
  for (int i = 0; fa[x][i]; ++i)
    fa[x][i + 1] = fa[fa[x][i]][i];
  for (int i = pre[x]; ~i; i = nxt[i])
    if (to[i] != f) dfs(to[i], x);
}
int LCA(int x, int y) {
  if (dep[x] < dep[y]) std::swap(x, y);
}
