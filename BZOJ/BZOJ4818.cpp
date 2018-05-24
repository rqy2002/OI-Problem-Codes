/**************************************************************
 * Problem: BZOJ4818
 * Author: Rqy
 * Date: 2018 Feb 24
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
typedef long long LL;
const int N = 20000050;
const int mod = 20170408;
bool mark[N];
int pr[N / 10], cnt;
int n, m, p;
struct P{
  int A[100];
  P() { memset(A, 0, sizeof A); }
  friend P operator*(const P &x, const P &y) {
    P ans;
    for (int i = 0; i < p; ++i)
      for (int j = 0; j < p; ++j)
        (ans.A[(i + j) % p] += (LL)x.A[i] * y.A[j] % mod) %= mod;
    return ans;
  }
}x, ans;
int main() {
  scanf("%d%d%d", &n, &m, &p);
  mark[1] = 1;
  for (int i = 2; i <= m; ++i) {
    if (!mark[i]) pr[cnt++] = i;
    for (int j = 0; j < cnt && pr[j] <= m / i; ++j) {
      mark[i * pr[j]] = 1;
      if (!i % pr[j]) break;
    }
  }
  ans.A[0] = 1;
  for (int i = 1; i <= m; ++i) x.A[i % p] += mark[i];
  for (int t = n; t; t >>= 1, x = x * x)
    if (t & 1) ans = ans * x;
  int t1 = ans.A[0];
  ans = P(); x = P();
  ans.A[0] = 1;
  for (int i = 1; i <= m; ++i) ++x.A[i % p];
  for (int t = n; t; t >>= 1, x = x * x)
    if (t & 1) ans = ans * x;
  printf("%d\n", (ans.A[0] - t1 + mod) % mod);
  return 0;
}
