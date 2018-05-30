#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define N 3003
#define LL long long
#define inf 1e9
using namespace std;
int n, m, q[N];
LL a[N], sum[N], f[N], g[N];
#define K(x) ((LL)-2 * sum[(x)])
#define B(x) ((LL)g[(x)] + sum[(x)] * sum[(x)])
inline LL calc(int x, int y) {
  return K(x) * sum[y] + B(x) + sum[y] * sum[y];
}
inline bool pd(int x1, int x2, int x3) {
  LL w1 = (LL)(K(x2) - K(x3)) * (B(x2) - B(x1));
  LL w2 = (LL)(K(x1) - K(x2)) * (B(x3) - B(x2));
  return w1 <= w2;
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
int main() {
  int i, j;
  scanf("%d%d", &n, &m);
  sum[0] = 0;
  for (i = 1; i <= n; ++i)
    sum[i] = sum[i - 1] + read();
  LL ans = inf;
  for (i = 1; i <= n; ++i)
    g[i] = inf;
  g[0] = 0;
  for (i = 1; i <= m; ++i) {
    int head = 0, tail = 0;
    for (j = 1; j <= n; ++j) {
      while (head < tail && calc(q[head + 1], j) <= calc(q[head], j))
        ++head;
      f[j] = calc(q[head], j);
      while (head < tail && pd(q[tail - 1], j, q[tail]))
        --tail;
      ++tail;
      q[tail] = j;
    }
    ans = min(ans, f[n]);
    memcpy(g, f, sizeof f);
  }
  printf("%lld\n", ans * m - sum[n] * sum[n]);
  return 0;
}
