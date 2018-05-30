#include <algorithm>
#include <cstdio>
#include <cstring>
typedef long long LL;
const int N = 100050;
int phi[N];
void getPhi() {
  for (int i = 1; i < N; ++i) phi[i] = i;
  for (int i = 2; i < N; ++i) if (phi[i] == i)
    for (int j = i; j < N; j += i)
      phi[j] -= phi[j] / i;
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  LL ans = 0;
  getPhi();
  for (int i = 1; i <= n && i <= m; ++i)
    ans += (LL)phi[i] * (n / i) * (m / i);
  printf("%lld\n", ans * 2 - (LL)n * m);
  return 0;
}
