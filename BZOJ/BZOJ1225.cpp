/**************************************************************
 * Problem: BZOJ1225
 * Author: Rqy
 * Date: 2018 Feb 25
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <map>
const int N = 50050;
const int p[20] = {
   2,  3,  5,  7, 11,
  13, 17, 19, 23, 29,
  31, 37, 41, 43, 47,
  53, 59, 61, 67, 71
};
double logp[20];
double f[505][20];
int d[505];
int cnt;
int A[100000], len;
void mul(int x) {
  int v = 0;
  for (int i = 0; i < len; ++i) {
    v = (A[i] = A[i] * x + v) / 10;
    A[i] %= 10;
  }
  while (v) A[len++] = v % 10, v /= 10;
}
int main() {
  int n, m = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) if (!(n % i)) d[m++] = i;
  for (int i = 0; i < 20; ++i) f[0][i] = .0;
  for (int i = 0; i < 20; ++i) logp[i] = log(p[i]);
  for (int i = 1; i < m; ++i) {
    for (int k = 0; k < 20; ++k)
      f[i][k] = 1e9;
    for (int j = 0; j < i; ++j) if (!(d[i] % d[j])) {
      int t = d[i] / d[j];
      for (int k = 1; k < 20; ++k)
        f[i][k] = std::min(f[i][k], f[j][k - 1] + logp[k - 1] * (t - 1));
    }
  }
  A[0] = len = 1;
  int j = 0;
  for (int i = 0; i < 20; ++i) if (f[m - 1][i] < f[m - 1][j]) j = i;
  for (int i = m - 1, nxt; i; i = nxt, --j) {
    for (nxt = 0; d[i] % d[nxt] || f[i][j] < f[nxt][j - 1]
        + logp[j - 1] * (d[i] / d[nxt] - 1) - 1e-5; ++nxt);
    for (int k = 1; k < d[i] / d[nxt]; ++k)
      mul(p[j - 1]);
  }
  while (len--) printf("%d", A[len]);
  return 0;
}

