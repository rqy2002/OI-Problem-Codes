#include <algorithm>
#include <cstdio>
#include <queue>
typedef long long LL;
const LL INF = 1000000000000000LL;
const int N = 550;
const int M = 300000;
int pre[N], nxt[M], to[M], t[M], c[M], cnt = 0;
inline void addedge(int p, int q, int ti, int ci) {
  to[cnt] = q; t[cnt] = ti; c[cnt] = ci;
  nxt[cnt] = pre[p]; pre[p] = cnt++;
  to[cnt] = p; t[cnt] = ti; c[cnt] = ci;
  nxt[cnt] = pre[q]; pre[q] = cnt++;
}
LL dis[N];
int n, m;
struct HeapNode{
  int x;
  LL d;
  HeapNode(int x = 0, LL d = 0) : x(x), d(d) {}
  inline bool operator<(const HeapNode &y)const{
    return d > y.d;
  }
};
void Dijkstra() {
  static std::priority_queue<HeapNode> Q;
  std::fill(dis + 1, dis + n + 1, INF);
  while (!Q.empty()) Q.pop();
  Q.push(HeapNode(1, dis[1] = 0));
  while (!Q.empty()) {
    HeapNode x = Q.top(); Q.pop();
    if (x.d != dis[x.x]) continue;
    int u = x.x;
    if (u == n) return;
    for (int i = pre[u]; ~i; i = nxt[i])
      if (dis[to[i]] > dis[u] + t[i])
        Q.push(HeapNode(to[i], dis[to[i]] = dis[u] + t[i]));
  }
}
struct Dinic{
  int pre[N], nxt[M], to[M], cnt;
  LL ret[M];
  int dis[N];
  Dinic() {
    cnt = 0;
    std::fill(pre, pre + N, -1);
  }
  inline void addedge(int p, int q, LL c) {
    to[cnt] = q; ret[cnt] = c;
    nxt[cnt] = pre[p]; pre[p] = cnt++;
    to[cnt] = p; ret[cnt] = 0;
    nxt[cnt] = pre[q]; pre[q] = cnt++;
  }
  bool BFS() {
    static std::queue<int> Q;
    while (!Q.empty()) Q.pop();
    std::fill(dis + 1, dis + n + 1, -1);
    dis[1] = 0;
    Q.push(1);
    while (!Q.empty()) {
      int x = Q.front(); Q.pop();
      for (int i = pre[x]; ~i; i = nxt[i]) 
        if (ret[i] && !~dis[to[i]]) {
          dis[to[i]] = dis[x] + 1;
          Q.push(to[i]);
          if (to[i] == n) return true;
        }
    }
    return false;
  }
  LL DFS(int x, LL f) {
    if (x == n) return f;
    LL ans = 0;
    for (int i = pre[x]; ~i && f; i = nxt[i])
      if (ret[i] && dis[to[i]] == dis[x] + 1) {
        LL df = DFS(to[i], std::min(f - ans, ret[i]));
        ans += df;
        ret[i] -= df; ret[i ^ 1] += df;
      }
    if (ans == f) dis[x] = n + 2;
    return ans;
  }
  LL solve() {
    LL ans = 0;
    while (BFS()) ans += DFS(1, INF);
    return ans;
  }
};
Dinic solver;
int main() {
  scanf("%d%d", &n, &m);
  std::fill(pre + 1, pre + n + 1, -1);
  int p, q, ti, ci;
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d%d", &p, &q, &ti, &ci);
    addedge(p, q, ti, ci);
  }
  Dijkstra();
  for (int i = 0; i < cnt; ++i)
    if (dis[to[i]] - dis[to[i ^ 1]] == t[i])
      solver.addedge(to[i ^ 1], to[i], c[i]);
  printf("%lld\n%lld\n", dis[n], solver.solve());
  return 0;
}
