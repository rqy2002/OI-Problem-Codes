/**************************************************************
 * Problem: Luogu P2602
 * Author: Rqy
 * Date: 2017 Dec 26
 * Algorithm: 数位DP
**************************************************************/
#include <cstdio>
typedef long long LL;
const int N = 15;
LL p[N], a[N][2], b[N][2];
LL solve(LL t, int k) {
  int l = 0;
  while (t) p[l++] = t % 10, t /= 10;
  a[l][0] = 1; a[l][1] = 0;
  b[l][0] = b[l][1] = 0;
  for (int i = l - 1; ~i; --i) {
    a[i][0] = a[i + 1][0];
    a[i][1] = a[i + 1][1] * 10 + a[i + 1][0] * p[i];
    b[i][0] = b[i + 1][0] + (p[i] == k);
    b[i][1] = b[i + 1][1] * 10 + b[i + 1][0] * p[i] +
              (a[i + 1][1] - (!k && i != l - 1)) +
              a[i + 1][0] * (p[i] > k) * (!!k || i != l - 1);
  }
  return b[0][0] + b[0][1];
}
int main() {
  LL A, B;
  scanf("%lld%lld", &A, &B);
  for (int i = 0; i < 10; ++i) {
    if (i) printf(" ");
    printf("%lld", solve(B, i) - solve(A - 1, i));
  }
  return 0;
}
