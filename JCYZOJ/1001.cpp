/**************************************************************
 * Problem: JCYZOJ 1001
 * Author: Rqy
 * Date: 2018 Feb 13
 * Algorithm: 01-BFS
**************************************************************/
#include <algorithm>
#include <cstdio>
typedef long long LL;
const int N = 55;
const int M = 10050;
int que[M * 2];
LL dis[M];
int v[N];
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m = 0;
    LL t;
    scanf("%d%lld", &n, &t);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &v[i]);
      m = std::max(m, v[i]);
    }
    std::fill(dis, dis + m, 5000000000000000000LL);
    int hd = M, tl = M;
    dis[que[tl++] = 0] = 0;
    while (hd < tl) {
      int x = que[hd++];
      for (int i = 0; i < n; ++i) {
        int u = (x + v[i]) % m;
        int l = (x + v[i]) / m;
        if (dis[u] <= dis[x] + l) continue;
        dis[u] = dis[x] + l;
        que[l ? tl++ : --hd] = u;
      }
    }
    puts(dis[t % m] <= t / m ? "Possible" : "Impossible");
  }
  return 0;
}
