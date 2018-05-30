#include <cstdio>
typedef long long LL;
const int N = 100050;
LL f[N], c[4];
LL s, d[4];
LL calc(int S) {
  LL t = s;
  for (int i = 0; i < 4; ++i)
    t -= ((S >> i) & 1) * (d[i] + 1) * c[i];
  if (t < 0) return 0;
  return f[t];
}
int main() {
  f[0] = 1;
  for (int i = 0; i < 4; ++i) {
    scanf("%lld", &c[i]);
    for (int j = c[i]; j < N; ++j)
      f[j] += f[j - c[i]];
  }
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%lld%lld%lld%lld%lld", &d[0], &d[1], &d[2], &d[3], &s);
    printf("%lld\n", 
        calc(0) - calc(1) - calc(2) - calc(4) - calc(8)
      + calc(3) + calc(5) + calc(9) + calc(6) + calc(10) + calc(12)
      - calc(7) - calc(11) - calc(13) - calc(14) + calc(15));
  }
  return 0;
}
