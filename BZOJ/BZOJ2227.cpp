/**************************************************************
 * Problem: BZOJ2227
 * Author: Rqy
 * Date: 2018 Feb 22
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 205;
int p[N];
int A[10000], len;
void add(int n, int m) {
  for (int i = 2; i <= n; ++i) if (!(n % i)) {
    while (!(n % i)) {
      p[i] += m;
      n /= i;
    }
  }
}
void mul(int x) {
  for (int i = 0, t = 0; i < len || t; ++i) {
    t = (A[i] = A[i] * x + t) / 10;
    A[i] %= 10;
    if (i >= len) len = i + 1;
  }
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, k;
    scanf("%d%d", &n, &k);
    if (n > k) { puts("0 1"); continue; }
    memset(p, 0, sizeof p);
    add(k - n + 1, 1);
    add(k + 1, n - 1);
    add(k, -n);
    memset(A, 0, sizeof A);
    A[0] = len = 1;
    for (int i = 1; i <= k + 1; ++i)
      for (int j = 0; j < p[i]; ++j)
        mul(i);
    while (len--) printf("%d", A[len]);
    putchar(' ');
    memset(A, 0, sizeof A);
    A[0] = len = 1;
    for (int i = 1; i <= k + 1; ++i)
      for (int j = p[i]; j < 0; ++j)
        mul(i);
    while (len--) printf("%d", A[len]);
    putchar('\n');
  }
}
