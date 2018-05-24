/**************************************************************
 * Problem: BZOJ4591
 * Author: Rqy
 * Date: 2018 Feb 23
 * Algorithm: 
**************************************************************/
#include <cstdio>
const int p = 2333;
typedef long long LL;
int CC[p][p], SS[p][p];
int C(LL n, LL k) {
  int ans = 1;
  while (n || k) {
    int n1 = n % p, k1 = k % p;
    ans = ans * CC[n1][k1] % p;
    n /= p; k /= p;
  }
  return ans;
}
int S(LL n, LL k) {
  if (k < 0) return 0;
  return (SS[n % p][p - 1] * S(n / p, k / p - 1)
      + C(n / p, k / p) * SS[n % p][k % p]) % p;
}
int main() {
  for (int i = 0; i < p; ++i) {
    CC[i][0] = 1;
    for (int j = 1; j <= i; ++j)
      CC[i][j] = (CC[i - 1][j] + CC[i - 1][j - 1]) % p;
  }
  for (int i = 0; i < p; ++i) {
    SS[i][0] = 1;
    for (int j = 1; j < p; ++j)
      SS[i][j] = (SS[i][j - 1] + CC[i][j]) % p;
  }
  int t;
  scanf("%d", &t);
  LL n, k;
  while (t--) {
    scanf("%lld%lld", &n, &k);
    printf("%d\n", S(n, k));
  }
  return 0;
}
