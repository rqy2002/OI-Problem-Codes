/**************************************************************
 * Problem: BZOJ2118
 * Author: Rqy
 * Date: 2018 Feb 25
 * Algorithm: 
**************************************************************/
#include <cstdio>
#include <queue>
const int N = 15;
const int M = 500050;
typedef long long LL;
int A[N], dis[M];
bool vis[N];
std::deque<int> Q;
int main() {
  int n, m = 0;
  LL l, r;
  scanf("%d%lld%lld", &n, &l, &r);
  for (int i = 0; i < n; ++i) scanf("%d", &A[i]), m = std::max(m, A[i]);
  if (m == 0) return puts("0") & 0;
  for (int i = 0; i < m; ++i) dis[i] = -1;
  dis[0] = 0;
  Q.push_back(0);
  while (!Q.empty()) {
    int x = Q.front(); Q.pop_front();
    if (vis[x]) continue;
    vis[x] = true;
    for (int i = 0; i < n; ++i) {
      int t = x + A[i];
      if (~dis[t % m] && dis[t % m] <= dis[x] + (t / m)) continue;
      dis[t % m] = dis[x] + (t / m);
      if (t >= m) Q.push_back(t - m);
      else Q.push_front(t);
    }
  }
  LL ans = 0;
  for (int i = 0; i < m; ++i) if (~dis[i]) {
    LL t = (LL)dis[i] * m + i;
    if (t <= r) ans += (r - t) / m + 1;
    if (t < l) ans -= (l - 1 - t) / m + 1;
  }
  printf("%lld\n", ans);
  return 0;
}
