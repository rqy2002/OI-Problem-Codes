/**************************************************************
 * Problem: BZOJ5119
 * Author: _rqy
 * Date: 2018 Mar 16
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 30050;
const int M = 35;
const int mod = 998244353;
const int g = 3;

typedef long long LL;
typedef std::vector<LL> VLL;

int n, m;
LL a[N], fac[N], ifac[N], inv[N];

inline LL pow_mod(LL x, int b) {
  LL ans = 1;
  for ((b += mod - 1) %= (mod - 1); b; b >>= 1, (x *= x) %= mod)
    if ((b & 1) != 0) (ans *= x) %= mod;
  return ans;
}

void NTT(LL *A, int len, int opt) {
  for (int i = 1, j = 0; i < len; ++i) {
    int k = len;
    do j ^= (k >>= 1); while ((j & k) == 0);
    if (i < j) std::swap(A[i], A[j]);
  }
  for (int h = 2; h <= len; h <<= 1) {
    LL wn = pow_mod(g, (mod - 1) / h * opt);
    for (int j = 0; j < len; j += h) {
      LL w = 1LL;
      for (int i = j; i < j + (h >> 1); ++i) {
        LL _tmp1 = A[i], _tmp2 = A[i + (h >> 1)] * w % mod;
        A[i] = (_tmp1 + _tmp2) % mod;
        A[i + (h >> 1)] = (_tmp1 - _tmp2) % mod;
        (w *= wn) %= mod;
      }
    }
  }

  if (opt == -1)
    for (int i = 0; i < len; ++i)
      (A[i] *= -(mod - 1) / len) %= mod;
}

LL S[2 * M][2 * M];

struct PVLL{
  VLL A, B;
  PVLL() : A(0), B(0) {}
};

inline void Copy(const VLL &x, LL *A, int len) {
  for (int i = 0; i < len; ++i) A[i] = (i < x.size() ? x[i] : 0);
}

PVLL operator*(const PVLL &x, const PVLL &y) {
  static LL T1[N * M * 4], T2[N * M * 4], T3[N * M * 4];
  PVLL ans;
  int len = 1,
      ansl = std::max(x.A.size() + y.B.size(), x.B.size() + y.A.size());
  while (len < ansl - 1) len <<= 1;

  Copy(x.A, T1, len);
  NTT(T1, len, 1);
  Copy(y.A, T2, len);
  NTT(T2, len, 1);

  for (int i = 0; i < len; ++i) T3[i] = T1[i] * T2[i] % mod;
  NTT(T3, len, -1);
  ans.A.resize(std::min<int>(n, x.A.size() + y.A.size() - 1));
  for (int i = 0; i < std::min<int>(n, x.A.size() + y.A.size() - 1); ++i)
    (ans.A[i] = T3[i]) %= mod;

  Copy(x.B, T3, len);
  NTT(T3, len, 1);
  for (int i = 0; i < len; ++i) (T3[i] *= T2[i]) %= mod;
  NTT(T3, len, -1);
  ans.B.resize(std::min(n, ansl - 1));
  for (int i = 0; i < std::min(n, ansl - 1); ++i)
    ans.B[i] = T3[i];

  Copy(y.B, T3, len);
  NTT(T3, len, 1);
  for (int i = 0; i < len; ++i) (T3[i] *= T1[i]) %= mod;
  NTT(T3, len, -1);
  for (int i = 0; i < std::min(n, ansl - 1); ++i)
    (ans.B[i] += T3[i]) %= mod;
  return ans;
}

PVLL Solve(int l, int r) {
  if (l == r - 1) {
    PVLL ans;
    ans.A.resize(m + 1);
    ans.B.resize(2 * m + 1);
    LL pa = a[l];
    for (int i = 0; i <= 2 * m; ++i, (pa *= a[l]) %= mod) {
      if (i <= m) ans.A[i] = (LL)pa * S[m + 1][i + 1] % mod;
      ans.B[i] = (LL)pa * S[2 * m + 1][i + 1] % mod;
    }
    return ans;
  }
  int mid = (l + r + 1) >> 1;
  return Solve(l, mid) * Solve(mid, r);
}

LL ps[N];

int main() {
  scanf("%d%d", &n, &m);

  fac[0] = fac[1] = ifac[0] = ifac[1] = inv[1] = 1;
  for (int i = 2; i <= n; ++i) {
    fac[i] = fac[i - 1] * i % mod;
    inv[i] = -(mod / i) * inv[mod % i] % mod;
    ifac[i] = ifac[i - 1] * inv[i] % mod;
  }

  S[0][0] = 1;
  for (int i = 1; i <= 2 * m + 1; ++i)
    for (int j = 1; j <= 2 * m + 1; ++j)
      S[i][j] = (S[i - 1][j - 1] + S[i - 1][j] * j) % mod;

  int s = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%lld", &a[i]);
    (s += a[i]) %= mod;
  }
  PVLL res = Solve(0, n);
  LL ans = 0;
  ps[0] = 1;
  for (int i = 1; i <= n - 2; ++i) ps[i] = ps[i - 1] * s % mod;
  for (int i = 0; i <= n - 2; ++i)
    (ans += res.B[i] * ps[n - 2 - i] % mod * ifac[n - 2 - i] % mod) %= mod;
  printf("%lld\n", (ans * fac[n - 2] % mod + mod) % mod);
  return 0;
}
