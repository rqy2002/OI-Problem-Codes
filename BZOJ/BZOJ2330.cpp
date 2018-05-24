/**************************************************************
 * Problem: BZOJ2330
 * Author: Rqy
 * Date: 2018 Feb 22
 * Algorithm: 差分约束
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 100050;
int pre[N], nxt[N * 2], to[N * 2], c[N * 2], cnt;
void addEdge(int a, int b, int v) {
  nxt[cnt] = pre[a];
  c[cnt] = v;
  to[pre[a] = cnt++] = b;
}
bool inque[N];
int dis[N];
int que[N], hd, tl;
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  memset(pre, -1, sizeof pre);
  int x, a, b;
  while (m--) {
    scanf("%d%d%d", &x, &a, &b);
    if (x == 5) addEdge(a, b, 0);
    else if (x == 4) addEdge(b, a, 1);
    else if (x == 3) addEdge(b, a, 0);
    else if (x == 2) addEdge(a, b, 1);
    else { addEdge(a, b, 0); addEdge(b, a, 0); }
  }
  hd = tl = 0;
  for (int i = 1; i <= n; ++i) {
    dis[i] = 1;
    inque[que[tl++] = i] = true;
  }
  int maxv = 0;
  while (hd != tl && maxv <= n) {
    int x = que[hd++];
    inque[x] = false;
    hd %= N;
    for (int i = pre[x]; ~i; i = nxt[i])
      if (dis[to[i]] < dis[x] + c[i]) {
        maxv = std::max(maxv, dis[to[i]] = dis[x] + c[i]);
        if (!inque[to[i]]) {
          inque[que[tl++] = to[i]] = true;
          tl %= N;
        }
      }
  }
  if (maxv > n) { puts("-1"); return 0; }
  long long ans = 0;
  for (int i = 1; i <= n; ++i) ans += dis[i];
  printf("%lld\n", ans);
  return 0;
}
