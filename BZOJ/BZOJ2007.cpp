/**************************************************************
 * Problem: BZOJ2007
 * Author: Rqy
 * Date: 2018 Feb 25
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <queue>
const int N = 505;
const int NN = N * N;
const int M = 8 * N * N;
const int inf = 1000000000;
int pre[NN], nxt[M], to[M], c[M], dis[NN], cnt;
inline void addEdge(int x, int y, int v) {
  nxt[cnt] = pre[x];
  c[cnt] = v;
  to[pre[x] = cnt++] = y;
}
struct HeapNode{
  int x, d;
  HeapNode(int x, int d) : x(x), d(d) {}
  bool operator<(const HeapNode &t) const {
    return d > t.d;
  }
};
std::priority_queue<HeapNode> PQ;
int Dijkstra(int S, int T) {
  std::fill(dis, dis + NN, inf);
  while (!PQ.empty()) PQ.pop();
  PQ.push(HeapNode(S, dis[S] = 0));
  while (!PQ.empty()) {
    HeapNode x = PQ.top(); PQ.pop();
    if (x.d != dis[x.x]) continue;
    if (x.x == T) return x.d;
    for (int i = pre[x.x]; ~i; i = nxt[i])
      if (x.d + c[i] < dis[to[i]])
        PQ.push(HeapNode(to[i], dis[to[i]] = x.d + c[i]));
  }
  return inf;
}
int n;
int S, T;
inline int get(int i, int j) {
  if (i < 0 || j >= n) return S;
  if (i >= n || j < 0) return T;
  return i * n + j;
}
int main() {
  scanf("%d", &n);
  std::fill(pre, pre + NN, -1);
  S = n * n; T = n * n + 1;
  for (int i = 0, v; i <= n; ++i)
    for (int j = 0; j < n; ++j) {
      scanf("%d", &v);
      addEdge(get(i - 1, j), get(i, j), v);
    }
  for (int i = 0, v; i < n; ++i)
    for (int j = 0; j <= n; ++j) {
      scanf("%d", &v);
      addEdge(get(i, j), get(i, j - 1), v);
    }
  for (int i = 0, v; i <= n; ++i)
    for (int j = 0; j < n; ++j) {
      scanf("%d", &v);
      addEdge(get(i, j), get(i - 1, j), v);
    }
  for (int i = 0, v; i < n; ++i)
    for (int j = 0; j <= n; ++j) {
      scanf("%d", &v);
      addEdge(get(i, j - 1), get(i, j), v);
    }
/*
  for (int i = 0; i <= T; ++i) {
    printf("%d:", i);
    for (int j = pre[i]; ~j; j = nxt[j])
      printf(" (%d, %d)", to[j], c[j]);
    printf("\n");
  }
*/
  printf("%d\n", Dijkstra(S, T));
  return 0;
}
