/**************************************************************
 * Problem: BZOJ2818
 * Author: Rqy
 * Date: 2018 Mar 01
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 10000050;
typedef long long LL;
int s[N], pr[N / 10], cnt;
int main() {
  s[1] = 1;
  int n;
  scanf("%d", &n);
  for (int i = 2; i <= n; ++i) s[i] = -2;
  for (int i = 2; i <= n; ++i) {
    if (s[i] == -2) s[pr[cnt++] = i] = -1;
    for (int j = 0; j < cnt && pr[j] <= n / i; ++j)
      if (i % pr[j])
        s[i * pr[j]] = -s[i];
      else {
        s[i * pr[j]] = 0;
        break;
      }
  }
  for (int i = 1; i <= n; ++i) s[i] += s[i - 1];
  LL ans = 0;
  for (int i = 0; i < cnt; ++i)
    for (int m = n / pr[i], j = 1, last; j <= m; j = last + 1) {
      last = m / (m / j);
      ans += (LL)(s[last] - s[j - 1]) * (m / j) * (m / j);
    }
  printf("%lld\n", ans);
  return 0;
}
