#include <algorithm>
#include <cstdio>
#include <cmath>
#include <queue>
const int N = 50;
int map[N][N];
struct HeapNode{
  int i, j, d;
  HeapNode(int i = 0, int j = 0, int d = 0) : i(i), j(j), d(d) {}
  bool operator<(const HeapNode &x)const{
    return d > x.d;
  }
};
std::priority_queue<HeapNode> Q;
int dis[N][N], n, m, T, ans;
const int d[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
void Dijkstra(int si, int sj) {
  std::fill(dis[0], dis[n], 10000);
  while (!Q.empty()) Q.pop();
  Q.push(HeapNode(si, sj, dis[si][sj] = map[si][sj]));
  while (!Q.empty()) {
    HeapNode x = Q.top(); Q.pop();
    if (x.d != dis[x.i][x.j]) continue;
    if (x.d > T) return;
    int ui = x.i, uj = x.j;
    ans = std::max(ans, (ui - si) * (ui - si) + (uj - sj) * (uj - sj));
    for (int k = 0; k < 4; ++k) {
      int vi = ui + d[k][0], vj = uj + d[k][1];
      if (~vi && ~vj && vi < n && vj < m && dis[vi][vj] > x.d + map[vi][vj])
        Q.push(HeapNode(vi, vj, dis[vi][vj] = x.d + map[vi][vj]));
    }
  }
}
int main() {
  scanf("%d%d%d", &n, &m, &T);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      scanf("%1d", &map[i][j]);
  ans = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      Dijkstra(i, j);
  printf("%.6f", sqrt((float)ans));
  return 0;
}
