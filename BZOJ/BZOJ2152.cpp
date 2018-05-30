#include <algorithm>
#include <cstdio>
#include <cstring>
#define forEdge(x, i) for (int i = pre[(x)]; ~i; i = nxt[i])
typedef long long LL;
const int N = 20050;
int pre[N], nxt[N * 2], to[N * 2], w[N * 2];
int cnt = 0;
int n;
LL f[N][3];
inline void addEdge(int x, int y, int v) {
  to[cnt] = y; w[cnt] = v;
  nxt[cnt] = pre[x]; pre[x] = cnt++;
  to[cnt] = x; w[cnt] = v;
  nxt[cnt] = pre[y]; pre[y] = cnt++;
}
LL dfs(int x, int fa) {
  LL ans = 0;
  f[x][0] = 1;
  forEdge(x, i) if (to[i] != fa) {
    ans += dfs(to[i], x);
    for (int k = 0; k < 3; ++k)
      ans += f[x][k] * f[to[i]][(6 - k - w[i]) % 3];
    for (int k = 0; k < 3; ++k)
      f[x][(k + w[i]) % 3] += f[to[i]][k];
  }
  return ans;
}
LL gcd(LL a, LL b) {
  return b ? gcd(b, a % b) : a;
}
int main() {
  memset(pre, -1, sizeof pre);
  int n, x, y, v;
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    scanf("%d%d%d", &x, &y, &v);
    addEdge(--x, --y, v %= 3);
  }
  LL ans = dfs(0, -1) * 2 + n;
  LL t = (LL)n * n;
  LL g = gcd(ans, t);
  printf("%lld/%lld\n", ans / g, t / g);
  return 0;
}
