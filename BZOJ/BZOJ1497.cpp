#include <algorithm>
#include <cstdio>
#include <queue>
typedef long long LL;
const LL INF = 1000000000000000LL;
const int N = 55050;
const int M = 500050;
struct Dinic{
  int to[M], nxt[M], pre[N], cnt;
  int dis[N];
  LL ret[M];
  Dinic() {
    std::fill(pre, pre + N, -1);
    cnt = 0;
  }
  inline void addEdge(int u, int v, LL cap = INF) {
    to[cnt] = v; ret[cnt] = cap;
    nxt[cnt] = pre[u]; pre[u] = cnt++;
    to[cnt] = u; ret[cnt] = 0;
    nxt[cnt] = pre[v]; pre[v] = cnt++;
  }
  std::queue<int> Q;
  bool BFS(int S, int T) {
    std::fill(dis, dis + N, -1);
    dis[S] = 0;
    while (!Q.empty()) Q.pop();
    Q.push(S);
    while (!Q.empty()) {
      int x = Q.front(); Q.pop();
      for (int i = pre[x]; ~i; i = nxt[i]) 
        if (ret[i] && !~dis[to[i]]) {
          dis[to[i]] = dis[x] + 1;
          if (to[i] == T) return true;
          Q.push(to[i]);
        }
    }
    return false;
  }
  LL DFS(int x, int T, LL f) {
    if (x == T) return f;
    LL ans = 0;
    int i;
    for (i = pre[x]; ~i && ans < f; i = nxt[i])
      if (ret[i] && dis[to[i]] == dis[x] + 1) {
        LL d = DFS(to[i], T, std::min(f - ans, ret[i]));
        ret[i] -= d;
        ret[i ^ 1] += d;
        ans += d;
      }
    if (!~i) dis[x] = -1;
    return ans;
  }
  LL solve(int S, int T) {
    LL ans = 0;
    while (BFS(S, T))
      ans += DFS(S, T, INF);
    return ans;
  }
};
Dinic solver;
int main() {
  int n, m, x, y, z;
  scanf("%d%d", &n, &m);
  int S = n + m, T = n + m + 1;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &x);
    solver.addEdge(S, i, x);
  }
  LL ans = 0;
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d", &x, &y, &z);
    solver.addEdge(x - 1, i + n);
    solver.addEdge(y - 1, i + n);
    solver.addEdge(i + n, T, z);
    ans += z;
  }
  printf("%lld\n", ans - solver.solve(S, T));
  return 0;
}
