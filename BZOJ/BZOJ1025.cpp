#include <cstdio>
typedef long long LL;
const int N = 1050;
bool mark[N];
int cnt, prime[500];
void getPrime(int n) {
  cnt = 0;
  for (int i = 2; i <= n; ++i) {
    if (!mark[i])
      prime[cnt++] = i;
    for (int j = 0; j < cnt && prime[j] * i <= n; ++j) {
      mark[i * prime[j]] = 1;
      if (!(i % prime[j])) break;
    }
  }
}
LL f[N];
LL tmp[N];
int main() {
  int n;
  scanf("%d", &n);
  f[0] = 1;
  getPrime(n);
  for (int i = 0; i < cnt; ++i) {
    for (int j = 0; j <= n; ++j) {
      tmp[j] = 0;
      for (int k = prime[i]; k <= j; k *= prime[i])
        tmp[j] += f[j - k];
    }
    for (int i = 0; i <= n; ++i)
      f[i] += tmp[i];
  }
  for (int i = 0; i < n; ++i)
    f[n] += f[i];
  printf("%lld\n", f[n]);
  return 0;
}
