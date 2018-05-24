/**************************************************************
 * Problem: UOJ54
 * Author: Rqy
 * Date: 2017 Dec 13
 * Algorithm: 莫比乌斯反演
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 12;
const int C = 21;
const int M = 100001;
const int mod = 10007;
int fac[mod], inv[mod];
int mu[M], f[C][M], S[C][M][N];
int p[N * 1000], m[N];
inline int CC(int a, int b) {
  if (!b) return 1;
  if (a % mod < b % mod) return 0;
  return CC(a / mod, b / mod) * fac[a % mod] % mod * inv[fac[b % mod]] % mod * inv[fac[(a - b) % mod]] % mod;
}
int a[64][N], po[64];
int mdp[N];
int n, mm, c;
void upd(int x) {
  int l = x * 2, r = x * 2 + 1;
  po[x] = po[l] + po[r];
  for (int i = 0; i <= po[x]; ++i) a[x][i] = 0;
  for (int i = 0; i <= po[l]; ++i)
    for (int j = 0; j <= po[r]; ++j)
      a[x][i + j] = (a[x][i + j] + a[l][i] * a[r][j] % mod) % mod;
}
int sum(int l, int r) {
  int ans = 0;
  for (int i = 0; i <= po[1]; ++i)
    ans = (ans + a[1][i] * (S[c][r][i] - S[c][l - 1][i]) % mod) % mod;
  return ans;
}
int main() {
  fac[0] = 1;
  for (int i = 1; i < mod; ++i) fac[i] = fac[i - 1] * i % mod;
  inv[1] = 1;
  for (int i = 2; i < mod; ++i) inv[i] = mod - (mod / i) * inv[mod % i] % mod;
  mu[1] = 1;
  for (int i = 1; i < M; ++i)
    for (int j = i * 2; j < M; j += i)
      mu[j] -= mu[i];
  for (int c = 2; c < C; ++c) {
    for (int i = 1; i < M; ++i)
      f[c][i] = 0;
    for (int d = c - 1; d < M; ++d) {
      int cc = CC(d - 1, c - 2);
      for (int i = 1; i * d < M; ++i)
        f[c][i * d] = (f[c][i * d] + cc * mu[i]) % mod;
    }
    for (int j = 0; j < N; ++j)
      S[c][0][j] = 0;
    for (int i = 1; i < M; ++i)
      for (int j = 0, ij = 1; j < N; ++j, ij = ij * (i % mod) % mod)
        S[c][i][j] = (S[c][i - 1][j] + f[c][i] * ij) % mod;
  }
  int T;
  scanf("%d", &T);
  while (T--) {
    mm = 10000000;
    scanf("%d%d", &n, &c);
    for (int i = 0; i < n; ++i)
      scanf("%d", &m[i]), mm = std::min(mm, m[i]);
    if (mm < c) {
      printf("0\n");
      continue;
    } if (n == 1) {
      printf("%d\n", CC(m[0], c));
      continue;
    }
    int t = 0;
    p[t++] = 1;
    for (int i = 0; i < n; ++i) {
      int last = 1;
      while (last < m[i] - 1) {
        last = (m[i] - 1) / ((m[i] - 1) / last) + 1;
        p[t++] = last;
      }
    }
    std::sort(p, p + t);
    t = (int)(std::unique(p, p + t) - p);
    p[t] = mm;
    int d = 1;
    while (d < n) d <<= 1;
    for (int i = 0; i < n; ++i) mdp[i] = m[i];
    for (int i = 1; i <= d * 2; ++i) a[i][po[i] = 0] = 1;
    int ans = 0;
    for (int i = 0; p[i] < mm && i < t; ++i) {
      int l = p[i], r = p[i + 1] - 1; //[l, r]
      for (int j = 0; j < n; ++j)
        if ((m[j] - 1) / l != mdp[j]) {
          mdp[j] = (m[j] - 1) / l;
          int k = d + j;
          po[k] = 1;
          a[k][0] = m[j] % mod * (mdp[j] % mod) % mod;
          a[k][1] = -mdp[j] % mod * ((mdp[j] + 1) % mod) % mod * inv[2] % mod;
          while (k /= 2)
            upd(k);
        }
      for (int i = 0; i <= n; ++i) printf("%d ", a[1][i]);
      printf("\n");
      ans = (ans + sum(l, r)) % mod;
    }
    printf("%d\n", (ans + mod) % mod);
  }
  return 0;
}
