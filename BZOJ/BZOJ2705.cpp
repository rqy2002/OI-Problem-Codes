#include <cstdio>
typedef long long LL;
const int M = 100;
int n;
LL ans;
int pr[M], prcnt;
inline void calc(int x) {
  int anst = x;
  for (int i = 0; i < prcnt; ++i) if (!(x % pr[i]))
    anst = anst / pr[i] * (pr[i] - 1);
  ans += (LL)n / x * anst;
}
int main() {
  scanf("%d", &n);
  int tn = n;
  for (int i = 2; (LL)i * i <= tn; ++i)
    if (!(tn % i)) {
      pr[prcnt++] = i;
      while (!(tn % i)) tn /= i;
    }
  if (tn > 1)
    pr[prcnt++] = tn;
  for (int i = 1; (LL)i * i <= n; ++i) if (!(n % i)) {
    calc(i);
    if (i != n / i) calc(n / i);
  }
  printf("%lld\n", ans);
  return 0;
}
