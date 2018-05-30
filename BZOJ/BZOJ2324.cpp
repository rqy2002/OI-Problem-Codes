#include <algorithm>
#include <cstdio>
#include <queue>
typedef long long LL;
const LL INF = 100000000000;

using std::swap;
using std::fill;
using std::min;
using std::max;
using std::priority_queue;

const int N = 155;
LL dis2[N][N][N];

LL cost[N * 2][N * 2], dis[N * 2];
int cap[N * 2][N * 2];
LL h[N * 2], fa[N * 2];
int n2;

struct HeapNode{
  int x;
  LL d;
  bool operator < (const HeapNode &a) const {
    return d > a.d;
  }
};
bool Dijkstra() {
  static priority_queue<HeapNode> Q;
  while (!Q.empty()) Q.pop();
  fill(dis, dis + n2, INF);
  dis[0] = 0;
  Q.push((HeapNode){0, 0});
  while (!Q.empty()) {
    HeapNode x = Q.top(); Q.pop();
    if (x.d != dis[x.x]) continue;
    for (int j = 0; j < n2; ++j) if (cap[x.x][j])
      if (dis[j] > dis[x.x] + cost[x.x][j] + h[x.x] - h[j]) {
        fa[j] = x.x;
        dis[j] = dis[x.x] + cost[x.x][j] + h[x.x] - h[j];
        Q.push((HeapNode){j, dis[j]});
      }
  }
  return dis[n2 - 1] < INF;
}

LL MCMF() {
  for (int i = 0; i < n2; ++i) {
    h[i] = 0;
    for (int j = 0; j < i; ++j)
      h[i] = min(h[i], cost[j][i] + h[j]);
  }
  LL ans = 0;
  while (Dijkstra()) {
    for (int i = 0; i < n2; ++i)
      h[i] += dis[i];
    ans += h[n2 - 1];
    for (int i = n2 - 1; i; i = fa[i]) {
      --cap[fa[i]][i];
      ++cap[i][fa[i]];
    }
  }
  return ans;
}

int main() {
  int n, m, k, x, y, z, i;
  scanf("%d%d%d", &n, &m, &k);
  fill(dis2[0][0], dis2[n + 1][0], INF);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d", &x, &y, &z); 
    dis2[0][x][y] = min(dis2[0][x][y], (LL)z);
    dis2[0][y][x] = dis2[0][x][y];
  }
  for (int i = 0; i <= n; ++i)
    dis2[0][i][i] = 0;
  for (int i = 0; i <= n; ++i)
    for (int j = 0; j <= n; ++j)
      dis2[0][i][j] = min(dis2[0][i][j], dis2[0][i][0] + dis2[0][0][j]);
  for (int kk = 1; kk <= n; ++kk)
    for (int i = 0; i <= n; ++i)
      for (int j = 0; j <= n; ++j)
        dis2[kk][i][j] = min(dis2[kk - 1][i][j], dis2[kk - 1][i][kk] + dis2[kk - 1][kk][j]);
  fill(cost[0], cost[n + 1], INF * 10);
  n2 = (n + 1) * 2;
  for (int i = 0; i <= n; ++i) {
    cost[2 * i][2 * i + 1] = -INF / 1000;
    cap[2 * i][2 * i + 1] = 1;
    cost[2 * i + 1][2 * i] = INF / 1000;
    cap[2 * i + 1][2 * i] = 0;
    for (int j = i + 1; j <= n; ++j) {
      cost[2 * i + 1][2 * j] = dis2[j][i][j];
      cap[2 * i + 1][2 * j] = 1;
      cost[2 * j][2 * i + 1] = -dis2[j][i][j];
      cap[2 * j][2 * i + 1] = 0;
    }
    cost[2 * i + 1][n2 - 1] = 0;
    cap[2 * i + 1][n2 - 1] = 1;
    cost[n2 - 1][2 * i + 1] = 0;
    cap[n2 - 1][2 * i + 1] = 0;
  }
  cap[0][1] = k;
  cost[0][1] = 0;
  cost[1][0] = 0;
  printf("%d\n", MCMF() + n * INF / 1000);
  return 0;
}
