/**************************************************************
 * Problem: Luogu P2153
 * Author: Rqy
 * Date: 2017 Dec 22
 * Algorithm: 费用流
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
const int N = 500;
const int M = 50000;
const int INF = 0x7f7f7f7f;
namespace MCMF{
int pre[N], nxt[M], to[M], cost[M], ret[M], cnt;
inline void addEdge_(int x, int y, int r, int c) {
  nxt[cnt] = pre[x];
  ret[cnt] = r;
  cost[cnt] = c;
  to[pre[x] = cnt++] = y;
}
inline void addEdge(int x, int y, int r, int c) {
  addEdge_(x, y, r, c); addEdge_(y, x, 0, -c);
}
int dis[N], fa[N];
struct HeapNode{
  int x, d;
  HeapNode(int x, int d) : x(x), d(d) {}
  bool operator<(const HeapNode &s) const {
    return d > s.d;
  }
};
std::priority_queue<HeapNode> Q;
bool SPFA(int S, int T) {
  memset(dis, 0x7f, sizeof dis);
  while (!Q.empty()) Q.pop();
  Q.push(HeapNode(S, dis[S] = 0));
  while (!Q.empty()) {
    HeapNode x = Q.top(); Q.pop();
    if (x.d != dis[x.x]) continue;
    if (x.x == T) return true;
    for (int i = pre[x.x]; ~i; i = nxt[i])
      if (ret[i] && dis[to[i]] > x.d + cost[i]) {
        fa[to[i]] = i;
        Q.push(HeapNode(to[i], dis[to[i]] = x.d + cost[i]));
      }
  }
  return false;
}
int ans1, ans2;
void solve(int S, int T) {
  ans1 = ans2 = 0;
  while (SPFA(S, T)) {
    int mm = INF;
    for (int i = T; i != S; i = to[fa[i] ^ 1])
      mm = std::min(mm, ret[fa[i]]);
    ans1 += mm;
    for (int i = T; i != S; i = to[fa[i] ^ 1]) {
      ret[fa[i]] -= mm;
      ret[fa[i] ^ 1] += mm;
      ans2 += mm * cost[fa[i]];
    }
  }
}
};
int main() {
  int n, m, x, y, z;
  memset(MCMF::pre, -1, sizeof MCMF::pre);
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    MCMF::addEdge(i * 2 - 1, i * 2, 1 + INF * (i == 1 || i == n), 0);
  while (m--) {
    scanf("%d%d%d", &x, &y, &z);
    MCMF::addEdge(x * 2, y * 2 - 1, 1, z);
  }
  MCMF::solve(1, 2 * n);
  printf("%d %d\n", MCMF::ans1, MCMF::ans2);
  return 0;
}
