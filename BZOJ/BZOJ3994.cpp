#include <algorithm>
#include <cstdio>
typedef long long LL;
const int N = 50050;
LL t[N];
LL calcT(int n) {
  LL ans = 0;
  for (int i = 1, last; i <= n; i = last + 1) {
    last = n / (n / i);
    ans += n / i * (last - i + 1);
  }
  return ans;
}
bool mark[N];
int pr[N], pcnt = 0, mu[N], S[N];
void getMu() {
  mu[1] = 1;
  for (int i = 2; i < N; ++i) {
    if (!mark[i]) mu[pr[pcnt++] = i] = -1;
    for (int j = 0; j < pcnt && (LL)i * pr[j] < N; ++j) {
      mark[i * pr[j]] = 1;
      if (!(i % pr[j])) {
        mu[i * pr[j]] = 0;
        break;
      }
      mu[i * pr[j]] = -mu[i];
    }
  }
  for (int i = 1; i < N; ++i) S[i] = S[i - 1] + mu[i];
}
LL solve(int n, int m) {
  LL ans = 0;
  for (int i = 1, last; i <= n && i <= m; i = last + 1) {
    last = std::min(n / (n / i), m / (m / i));
    ans += t[n / i] * t[m / i] * (S[last] - S[i - 1]);
  }
  return ans;
}
int main() {
  for (int i = 1; i < N; ++i) t[i] = calcT(i);
  getMu();
  int T, n, m;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    printf("%lld\n", solve(n, m));
  }
  return 0;
}
