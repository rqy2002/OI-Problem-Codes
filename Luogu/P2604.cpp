/**************************************************************
 * Problem: Luogu P2604
 * Author: Rqy
 * Date: 2017 Dec 22
 * Algorithm: 费用流
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
typedef long long LL;
const LL N = 5000;
const LL M = 80000;
const LL INF = 0x7f7f7f7f7f7f7f7f;
namespace MCMF{
LL pre[N], nxt[M], to[M], ret[M], cost[M], cnt;
LL dis[N], fa[N];
inline void addEdge_(LL x, LL y, LL r, LL c) {
  nxt[cnt] = pre[x];
  ret[cnt] = r;
  cost[cnt] = c;
  to[pre[x] = cnt++] = y;
}
inline void addEdge(LL x, LL y, LL r, LL c) {
  addEdge_(x, y, r, c); addEdge_(y, x, 0, -c);
}
struct HeapNode{
  LL x, d;
  HeapNode(LL x, LL d) : x(x), d(d) {}
  bool operator<(const HeapNode &t) const {
    return d > t.d;
  }
};
std::priority_queue<HeapNode> Q;
bool SPFA(LL S, LL T) {
  memset(dis, 0x7f, sizeof dis);
  while (!Q.empty()) Q.pop();
  Q.push(HeapNode(S, dis[S] = 0));
  while (!Q.empty()) {
    HeapNode x = Q.top(); Q.pop();
    if (x.d != dis[x.x]) continue;
    if (x.x == T) return true;
    for (LL i = pre[x.x]; ~i; i = nxt[i])
      if (ret[i] && dis[to[i]] > x.d + cost[i]) {
        fa[to[i]] = i;
        Q.push(HeapNode(to[i], dis[to[i]] = x.d + cost[i]));
      }
  }
  return false;
}
LL ans1, ans2;
void solve(LL S, LL T, LL K) {
  ans1 = -1, ans2 = 0;
  LL ans = 0;
  while (SPFA(S, T)) {
    LL mm = INF;
    if (ans2) mm = K + ans1 - ans;
    if (!mm) break;
    for (LL i = T; i != S; i = to[fa[i] ^ 1])
      mm = std::min(mm, ret[fa[i]]);
    ans += mm;
    for (LL i = T; i != S; i = to[fa[i] ^ 1]) {
      ret[fa[i]] -= mm;
      ret[fa[i] ^ 1] += mm;
      ans2 += mm * cost[fa[i]];
    }
    if (!ans2)
      ans1 = ans;
  }
}
};
int main() {
  LL n, m, k, x, y, c, w;
  scanf("%lld%lld%lld", &n, &m, &k);
  memset(MCMF::pre, -1, sizeof MCMF::pre);
  while (m--) {
    scanf("%lld%lld%lld%lld", &x, &y, &c, &w);
    MCMF::addEdge(x, y, c, 0);
    MCMF::addEdge(x, y, INF, w);
  }
  MCMF::solve(1, n, k);
  printf("%lld %lld\n", MCMF::ans1, MCMF::ans2);
  return 0;
}
