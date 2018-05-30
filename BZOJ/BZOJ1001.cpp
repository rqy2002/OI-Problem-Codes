#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using std::priority_queue;
typedef long long LL;
const int N = 1000050;
const LL INF = 998244353;
int to[N * 6], nxt[N * 6], pre[N * 2], cnt;
LL dis[N * 2], cost[N * 6];
int que[N * 3];
bool inque[N * 2];
struct HeapNode {
  int x, d;
  bool operator < (const HeapNode &y) const {
    return d > y.d;
  }
  HeapNode(int xx = 0, int dd = 0) : x(xx), d(dd) {}
} ;
priority_queue<HeapNode> Q;
LL Dijkstra(int S, int T) {
  while (!Q.empty()) Q.pop();
  std::fill(dis, dis + N * 2, INF);
  dis[S] = 0;
  Q.push(HeapNode(S, 0));
  while (!Q.empty()) {
    HeapNode l = Q.top();
    Q.pop();
    if (dis[l.x] != l.d)
      continue;
    if (l.x == T)
      break;
    for (int i = pre[l.x]; i >= 0; i = nxt[i]) {
      if (dis[to[i]] > dis[l.x] + cost[i]) {
        dis[to[i]] = dis[l.x] + cost[i];
        Q.push(HeapNode(to[i], dis[to[i]]));
      }
    }
  }
  return dis[T];
}
inline LL read() {
  LL ans = 0;
  char c;
  do c = getchar();
  while (c > '9' || c < '0');
  do {
    ans = ans * 10 + c - '0';
    c = getchar();
  } while (c <= '9' && c >= '0');
  return ans;
}
inline void addedge(int x, int y) {
  LL c = read();
  to[cnt] = y;
  nxt[cnt] = pre[x];
  cost[cnt] = c;
  pre[x] = cnt++;
  to[cnt] = x;
  nxt[cnt] = pre[y];
  cost[cnt] = c;
  pre[y] = cnt++;
}
int main() {
  //freopen("bjrabbit.in", "r", stdin);
  //freopen("bjrabbit.out", "w", stdout);
  int n, m, i, j;
  scanf("%d%d", &n, &m);
  //printf("%d %d
", n, m);
  --n;
  --m;
  if (n <= 0 || m <= 0) {
    LL ans = INF;
    for (i = 0; i < n + m - 1; ++i)
      ans = std::min(ans, read());
    printf("%lld", ans);
    return 0;
  }
  int S = n * m * 2, T = n * m * 2 + 1;
  memset(pre, -1, sizeof pre);
  cnt = 0;
  for (j = 0; j < m; ++j)
    addedge(2 * j + 1, T);
  for (i = 1; i < n; ++i)
    for (j = 0; j < m; ++j)
      addedge(2 * m * i + 2 * j + 1, 2 * m * (i - 1) + 2 * j);
  for (j = 0; j < m; ++j)
    addedge(S, 2 * m * (n - 1) + 2 * j);
  for (i = 0; i < n; ++i) {
    addedge(S, 2 * m * i);
    for (j = 1; j < m; ++j)
      addedge(2 * m * i + 2 * j - 1, 2 * m * i + 2 * j);
    addedge(2 * m * (i + 1) - 1, T);
  }
  for (i = 0; i < n; ++i)
    for (j = 0; j < m; ++j)
      addedge(2 * m * i + 2 * j, 2 * m * i + 2 * j + 1);
  printf("%lld", Dijkstra(S, T));
  return 0;
}
