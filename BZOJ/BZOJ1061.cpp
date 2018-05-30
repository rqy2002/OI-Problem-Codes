#include <algorithm>
#include <cstdio>
#include <queue>
using std::queue;
typedef long long LL;
const LL INF = 10000000000000000;
const int N = 1050;
const int M = 100050;
struct MCMF{
  int to[M];
  LL cost[M], ret[M];
  int pre[N], nxt[M], cnt;
  LL dis[N];
  int las[N];
  bool inQ[N];
  queue<int> Q;
  MCMF() {
    std::fill(pre, pre + N, -1);
    cnt = 0;
  }
  inline void addEdge(int u, int v, LL w, LL c) {
    to[cnt] = v, cost[cnt] = w, ret[cnt] = c;
    nxt[cnt] = pre[u], pre[u] = cnt++;
    to[cnt] = u, cost[cnt] = -w, ret[cnt] = 0;
    nxt[cnt] = pre[v], pre[v] = cnt++;
  }
  bool SPFA(int s, int t) {
    std::fill(dis, dis + N, INF);
    std::fill(inQ, inQ + N, 0);
    dis[s] = 0;
    inQ[s] = true;
    while (!Q.empty()) Q.pop();
    Q.push(s);
    while (!Q.empty()) {
      int x = Q.front(); Q.pop();
      inQ[x] = false;
      for (int i = pre[x]; ~i; i = nxt[i]) if (ret[i]) {
        int v = to[i];
        if (dis[v] > dis[x] + cost[i]) {
          dis[v] = dis[x] + cost[i];
          las[v] = i;
          if (!inQ[v]) {
            inQ[v] = true;
            Q.push(v);
          }
        }
      }
    }
    return dis[t] < INF;
  }
  LL solve(int s, int t) {
    LL ans = 0;
    while (SPFA(s, t)) {
      LL p = INF;
      for (int i = t; i != s; i = to[las[i] ^ 1])
        p = std::min(p, ret[las[i]]);
      ans += p * dis[t];
      for (int i = t; i != s; i = to[las[i] ^ 1]) {
        ret[las[i]] -= p;
        ret[las[i] ^ 1] += p;
      }
    }
    return ans;
  }
};
MCMF solver;
int A[N];
int main() {
  int n, m, a, b, c;
  scanf("%d%d", &n, &m);
  int S = 0, T = n + 2;
  for (int i = 1; i <= n; ++i) scanf("%d", &A[i]);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d", &a, &b, &c);
    solver.addEdge(a, b + 1, c, INF);
  }
  for (int i = 1; i <= n + 1; ++i) {
    int t = A[i] - A[i - 1];
    if (t >= 0) solver.addEdge(S, i, 0, t);
    else solver.addEdge(i, T, 0, -t);
    if (i > 1) solver.addEdge(i, i - 1, 0, INF);
  }
  printf("%lld\n", solver.solve(S, T));
  return 0;
}
