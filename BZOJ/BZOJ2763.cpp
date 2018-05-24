/**************************************************************
 * Problem: BZOJ2763
 * Author: Rqy
 * Date: 2018 Feb 26
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <queue>
#include <cstring>
const int N = 200050;
const int M = 5000050;
typedef long long LL;
int pre[N], to[M], nxt[M], c[M], cnt;
inline void addEdge(int a, int b, int v) {
  nxt[cnt] = pre[a];
  c[cnt] = v;
  to[pre[a] = cnt++] = b;
}
struct HeapNode{
  int x;
  LL d;
  HeapNode(int x, LL d) : x(x), d(d) {}
  bool operator<(const HeapNode &h) const { return d > h.d; }
};
std::priority_queue<HeapNode> PQ;
LL dis[N];
LL Dijkstra(int S, int T) {
  memset(dis, 0x3f, sizeof dis);
  while (!PQ.empty()) PQ.pop();
  PQ.push(HeapNode(S, dis[S] = 0));
  while (!PQ.empty()) {
    HeapNode x = PQ.top(); PQ.pop();
    if (x.d != dis[x.x]) continue;
    if (x.x == T) return x.d;
    for (int i = pre[x.x]; ~i; i = nxt[i])
      if (dis[to[i]] > x.d + c[i])
        PQ.push(HeapNode(to[i], dis[to[i]] = x.d + c[i]));
  }
  return 0x3f3f3f3f3f3f3f3fLL;
}
int main() {
  int n, m, k, s, t;
  scanf("%d%d%d%d%d", &n, &m, &k, &s, &t);
  memset(pre, -1, sizeof pre);
  for (int i = 0, a, b, v; i < m; ++i) {
    scanf("%d%d%d", &a, &b, &v);
    for (int j = 0; j <= k; ++j) {
      addEdge(j * n + a, j * n + b, v);
      addEdge(j * n + b, j * n + a, v);
      if (j) addEdge((j - 1) * n + a, j * n + b, 0);
      if (j) addEdge((j - 1) * n + b, j * n + a, 0);
    }
  }
  for (int i = 1; i <= k; ++i) addEdge((i - 1) * n + t, i * n + t, 0);
  printf("%lld\n", Dijkstra(s, k * n + t));
  return 0;
}
