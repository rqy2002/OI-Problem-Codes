/**************************************************************
 * Problem: BZOJ3884
 * Author: Rqy
 * Date: 2018 Feb 23
 * Algorithm: 
**************************************************************/
#include <cstdio>
typedef long long LL;
const int N = 10000050;
int phi[N], pr[N / 10], cnt;
int pow_mod(int a, int b, int p) {
  int ans = 1;
  for (; b; b >>= 1, a = (LL)a * a % p)
    if (b & 1) ans = (LL)ans * a % p;
  return ans;
}
int calc(int p) {
  // 2 ^ (2 ^ (...)) % p
  if (p == 1) return 0;
  return pow_mod(2, calc(phi[p]) + phi[p], p);
}
int main() {
  for (int i = 1; i < N; ++i) phi[i] = i;
  for (int i = 2; i < N; ++i) {
    if (phi[i] == i)
      --phi[pr[cnt++] = i];
    for (int j = 0; j < cnt && (LL)pr[j] * i < N; ++j) {
      if (i % pr[j])
        phi[i * pr[j]] = phi[i] * phi[pr[j]];
      else {
        phi[i * pr[j]] = phi[i] * pr[j];
        break;
      }
    }
  }
  int T, p;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &p);
    printf("%d\n", calc(p));
  }
}
