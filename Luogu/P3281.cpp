/**************************************************************
 * Problem: Luogu P3281
 * Author: Rqy
 * Date: 2017 Dec 27
 * Algorithm: 数位DP
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
typedef long long LL;
const int N = 100050;
const int mod = 20130427;
int n, m, B;
int L[N], R[N];
LL SB[N], S[N];
LL a[N][2], s[N][2], ss[N][2], sl[N][2];
int solve(int *p, int l) {
  memset(a, 0, sizeof a);
  memset(s, 0, sizeof s);
  memset(ss, 0, sizeof ss);
  memset(sl, 0, sizeof sl);
  a[l][0] = 1;
  for (int i = l - 1; ~i; --i) {
    int c = (i == l - 1 ? 0 : B);
    a[i][0] = a[i + 1][0];
    a[i][1] = (c - 1 + a[i + 1][1] * B + a[i + 1][0] * p[i]) % mod;
    sl[i][0] = sl[i + 1][0] + a[i + 1][0];
    sl[i][1] = (c - 1 + sl[i][0] * p[i] +
                (sl[i + 1][1] + a[i + 1][1]) * B) % mod;
    ss[i][0] = (ss[i + 1][0] * B + p[i] * sl[i][0]) % mod;
    ss[i][1] = (S[c] + ss[i + 1][0] * B * p[i] + S[p[i]] * sl[i][0] +
                ss[i + 1][1] * B % mod * B +
                S[B] * (sl[i + 1][1] + a[i + 1][1])) % mod;
    s[i][0] = (s[i + 1][0] + ss[i][0]) % mod;
    s[i][1] = (s[i + 1][0] * p[i] + s[i + 1][1] * B + ss[i][1]) % mod;
  }
  return (s[0][0] + s[0][1]) % mod;
}
int main() {
  scanf("%d", &B);
  SB[0] = 1;
  for (int i = 0; i < N - 1; ++i) SB[i + 1] = (SB[i] * B + 1) % mod;
  S[0] = 0;
  for (int i = 0; i < B; ++i) S[i + 1] = (S[i] + i) % mod;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d", &L[n - i - 1]);
  for (int i = 0; i < n; ++i) {
    if (L[i] > 0) {
      --L[i];
      break;
    }
    L[i] = B - 1;
  }
  if (!L[n - 1]) --n;
  scanf("%d", &m);
  for (int i = 0; i < m; ++i) scanf("%d", &R[m - i - 1]);
  printf("%d\n", (solve(R, m) - solve(L, n) + mod) % mod);
  return 0;
}
