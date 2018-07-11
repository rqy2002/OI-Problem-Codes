#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long LL;

const int N = 800000;
const int mod = 998244353;
const int inv2 = (mod + 1) / 2;
const int g = 3;

LL inv[N];

char L[N * 10], *q = L;

int readInt() {
  int ans = 0, c;
  while (!isdigit(c = *(q++)));
  do ans = ans * 10 + c - '0';
  while (isdigit(c = *(q++)));
  return ans;
}

char S[N * 10], *p = S;

void output(LL x) {
  if (x / 10) output(x / 10);
  *(p++) = '0' + x % 10;
}

LL pow_mod(LL a, int b) {
  if ((b %= mod - 1) < 0) b += mod - 1;
  LL ans = 1;
  for (; b; b >>= 1, a = a * a % mod)
    if (b & 1) ans = ans * a % mod;
  return ans;
}

int ib[N];
LL omega[N], iomega[N];
void Init(int len) {
  int k = 0; while ((1 << (k + 1)) < len) ++k;
  for (int i = 1; i < len; ++i) ib[i] = (ib[i >> 1] >> 1) | ((i & 1) << k);
  omega[0] = iomega[0] = 1;
  omega[1] = pow_mod(g, mod / len);
  iomega[1] = pow_mod(g, -mod / len);
  for (int i = 2; i < len; ++i) {
    omega[i] = omega[i - 1] * omega[1] % mod;
    iomega[i] = iomega[i - 1] * iomega[1] % mod;
  }
}

void NTT(LL *A, int len, int opt) {
  for (int i = 1; i < len; ++i)
    if (i < ib[i]) std::swap(A[i], A[ib[i]]);
  LL *p = opt == 1 ? omega : iomega;
  for (int h = 2, s = len / 2; h <= len; h <<= 1, s >>= 1)
    for (int j = 0; j < len; j += h)
      for (LL *A1 = A + j, *E = A + j + (h >> 1), *A2 = E, *k = p;
          A1 != E; ++A1, ++A2, k += s) {
        LL _t1 = *A1, _t2 = *A2 * *k % mod;
        *A1 = (_t1 + _t2) % mod;
        *A2 = (_t1 - _t2) % mod;
      }
  if (opt == -1)
    for (int i = 0, v = -mod / len; i < len; ++i)
      A[i] = A[i] * v % mod;
}

void PolyInv(const LL *A, int n, LL *B) {
  if (n == 1) {
    B[0] = pow_mod(A[0], mod - 2);
    return;
  }
  static LL tA[N], tB[N];
  int m = (n + 1) / 2;
  PolyInv(A, m, B);
  int len = 1;
  while (len < n * 2) len <<= 1;
  for (int i = 0; i < n; ++i) tA[i] = A[i];
  for (int i = n; i < len; ++i) tA[i] = 0;
  for (int i = 0; i < m; ++i) tB[i] = B[i];
  for (int i = m; i < len; ++i) tB[i] = 0;
  Init(len);
  NTT(tA, len, 1); NTT(tB, len, 1);
  for (int i = 0; i < len; ++i)
    tB[i] = tB[i] * (2 - tA[i] * tB[i] % mod) % mod;
  NTT(tB, len, -1);
  for (int i = 0; i < n; ++i) B[i] = tB[i];
}

void PolySqrt(const LL *A, int n, LL *B) {
  if (n == 1) {
    B[0] = (LL)(std::sqrt(A[0]) + 1e-5);
    return;
  }
  int m = (n + 1) / 2;
  PolySqrt(A, m, B);
  static LL tA[N], tB[N];
  for (int i = m; i < n; ++i) B[i] = 0;
  PolyInv(B, n, tB);
  int len = 1;
  while (len < n * 2) len <<= 1;
  for (int i = 0; i < n; ++i) tA[i] = A[i];
  for (int i = n; i < len; ++i) tA[i] = 0;
  for (int i = n; i < len; ++i) tB[i] = 0;
  Init(len);
  NTT(tA, len, 1); NTT(tB, len, 1);
  for (int i = 0; i < len; ++i)
    tA[i] = tA[i] * tB[i] % mod;
  NTT(tA, len, -1);
  for (int i = 0; i < n; ++i)
    B[i] = (tA[i] + B[i]) * inv2 % mod;
}

void PolyLn(const LL *A, int n, LL *B) {
  static LL tA[N], tB[N];
  PolyInv(A, n, tA);
  for (int i = 0; i < n; ++i) tB[i] = A[i + 1] * (i + 1) % mod;
  int len = 1;
  while (len < n * 2) len <<= 1;
  for (int i = n; i < len; ++i) tA[i] = tB[i] = 0;
  Init(len);
  NTT(tA, len, 1); NTT(tB, len, 1);
  for (int i = 0; i < len; ++i) tA[i] = tA[i] * tB[i] % mod;
  NTT(tA, len, -1);
  B[0] = 0;
  for (int i = 1; i < n; ++i)
    B[i] = tA[i - 1] * inv[i] % mod;
}

void PolyExp(const LL *A, int n, LL *B) {
  if (n == 1) {
    B[0] = 1;
    return;
  }
  int m = (n + 1) / 2;
  PolyExp(A, m, B);
  // B + (A-lnB)B
  static LL tA[N], tB[N];
  for (int i = m; i < n; ++i) B[i] = 0;
  PolyLn(B, n, tB);
  int len = 1;
  while (len < 2 * m) len <<= 1;
  for (int i = 0; i < m; ++i) tA[i] = (A[i + m] - tB[i + m]) % mod;
  for (int i = m; i < len; ++i) tA[i] = 0;
  for (int i = 0; i < m; ++i) tB[i] = B[i];
  for (int i = m; i < len; ++i) tB[i] = 0;
  Init(len);
  NTT(tA, len, 1); NTT(tB, len, 1);
  for (int i = 0; i < len; ++i) tA[i] = tA[i] * tB[i] % mod;
  NTT(tA, len, -1);
  for (int i = m; i < len; ++i) B[i] = tA[i - m];
}

int n;
LL F[N], G[N];

int main() {
  freopen("polynomial.in", "r", stdin);
  freopen("polynomial.out", "w", stdout);
  fread(L, 1, N * 10, stdin);
  inv[1] = 1;
  for (int i = 2; i < N; ++i) inv[i] = -(mod / i) * inv[mod % i] % mod;
  int k;
  n = readInt(); k = readInt();
  for (int i = 0; i < n; ++i) F[i] = readInt();
  PolySqrt(F, n, G);
  PolyInv(G, n, F);
  for (int i = 1; i < n; ++i) G[i] = F[i - 1] * inv[i] % mod;
  G[0] = 0;
  PolyExp(G, n, F);
  PolyInv(F, n, G);
  G[0] += 1;
  PolyLn(G, n, F);
  F[0] += 1;
  PolyLn(F, n, G);
  for (int i = 0; i < n; ++i) G[i] = G[i] * k % mod;
  PolyExp(G, n, F);
  for (int i = 1; i < n; ++i)
    //printf("%lld ", (F[i] * i % mod + mod) % mod);
    output((F[i] * i % mod + mod) % mod), *(p++) = ' ';
  *(p++) = '0'; *(p++) = '\n';
  fwrite(S, 1, p - S, stdout);
  fclose(stdin);
  fclose(stdout);
  return 0;
}
