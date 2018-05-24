/**************************************************************
 * Problem: BZOJ4804
 * Author: Rqy
 * Date: 2018 Feb 24
 * Algorithm: 
**************************************************************/
#include <cstdio>
#include <cstring>
const int N = 10000050;
typedef long long LL;
LL s[N];
int pr[N], cnt;
void sieve() {
  memset(s, -1, sizeof s);
  s[0] = 0;
  s[1] = 1;
  for (int i = 2; i < N; ++i) {
    if (!~s[i])
      s[pr[cnt++] = i] = i - 2;
    for (int j = 0; j < cnt && (LL)i * pr[j] < N; ++j)
      if (i % pr[j]) s[i * pr[j]] = s[i] * s[pr[j]];
      else {
        if (!(i / pr[j] % pr[j])) s[i * pr[j]] = s[i] * pr[j];
        else s[i * pr[j]] = s[i / pr[j]] * (pr[j] - 1) * (pr[j] - 1);
        break;
      }
  }
  for (int i = 2; i < N; ++i) s[i] += s[i - 1];
}
int main() {
  sieve();
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    LL ans = 0;
    for (int i = 1, last; i <= n; i = last + 1) {
      last = n / (n / i);
      ans += (LL)(n / i) * (n / i) * (s[last] - s[i - 1]);
    }
    printf("%lld\n", ans);
  }
  return 0;
}
