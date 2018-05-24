/**************************************************************
 * Problem: BZOJ4466
 * Author: Rqy
 * Date: 2018 Feb 22
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 33000;
const int M = 2000050;
int pre[N], nxt[M], to[M], cnt, deg[N];
int A[N], que[N];
bool vis[N];
inline void addEdge(int x, int y) {
  ++deg[x];
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m, x, y;
    scanf("%d%d", &n, &m);
    int k = 1;
    while ((1 << k) < n) ++k;
    memset(pre, -1, sizeof pre);
    memset(deg, 0, sizeof deg);
    cnt = 0;
    while (m--) {
      scanf("%d%d", &x, &y);
      addEdge(x, y);
      addEdge(y, x);
    }
    bool ok = true;
    for (int i = 0; i < n; ++i)
      ok = ok && deg[i] == k;
    if (!ok) { puts("-1"); continue; }
    memset(A, 0, sizeof A);
    memset(vis, 0, sizeof vis);
    int hd = 0, tl = 0;
    vis[0] = true;
    for (int i = pre[0], j = 1; ~i; i = nxt[i], j <<= 1)
      A[que[tl++] = to[i]] = j;
    while (hd < tl) {
      int x = que[hd++];
      vis[x] = true;
      for (int i = pre[x]; ~i; i = nxt[i])
        if (!vis[to[i]]) {
          if (!A[to[i]]) que[tl++] = to[i];
          A[to[i]] |= A[x];
        }
    }
    memset(vis, 0, sizeof vis);
    for (int i = 0; i < n; ++i) vis[A[i]] = true;
    for (int i = 0; i < n; ++i) ok = ok && vis[i];
    if (!ok) { puts("-1"); continue; }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < k; ++j) vis[A[i] ^ (1 << j)] = false;
      for (int j = pre[i]; ~j; j = nxt[j]) vis[A[to[j]]] = true;
      for (int j = 0; j < k; ++j) ok = ok && vis[A[i] ^ (1 << j)];
    }
    if (!ok) { puts("-1"); continue; }
    for (int i = 0; i < n; ++i)
      printf("%d ", A[i]);
    puts("");
  }
}
