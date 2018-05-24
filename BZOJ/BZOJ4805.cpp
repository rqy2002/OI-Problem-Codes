/**************************************************************
 * Problem: BZOJ4805
 * Author: Rqy
 * Date: 2018 Feb 24
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 2000000050;
const int M = 1000050;
typedef long long LL;
LL s[M], s2[N / M + 50];
int pr[M], cnt;
void sieve() {
  s[1] = 1;
  for (int i = 2; i < M; ++i) {
    if (!s[i]) s[pr[cnt++] = i] = i - 1;
    for (int j = 0; j < cnt && (LL)pr[j] * i < M; ++j)
      if (i % pr[j])
        s[i * pr[j]] = s[i] * s[pr[j]];
      else {
        s[i * pr[j]] = s[i] * pr[j];
        break;
      }
  }
  for (int i = 2; i < M; ++i) s[i] += s[i - 1];
}
int n;
LL S(int d) {
  if (n / d < M) return s[n / d];
  LL &ans = s2[d];
  if (ans) return ans;
  int m = n / d;
  ans = (LL)m * (m + 1) / 2;
  for (int i = 2, last; i <= m; i = last + 1) {
    last = m / (m / i);
    ans -= (last - i + 1) * S(d * i);
  }
  return ans;
}
int main() {
  sieve();
  scanf("%d", &n);
  printf("%lld\n", S(1));
  return 0;
}
