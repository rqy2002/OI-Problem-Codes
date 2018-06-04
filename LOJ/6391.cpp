#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <vector>

typedef long long LL;
typedef std::vector<LL> VLL;
const int mod = 998244353;

LL pow_mod(LL a, LL b) {
  LL ans = 1;
  if ((b %= mod - 1) < 0) b += mod - 1;
  for (a %= mod; b > 0; b >>= 1, (a *= a) %= mod)
    if (b & 1) (ans *= a) %= mod;
  return ans;
}

namespace Solve1{
const int g = 3;
const int N = 500000;

void NTT(LL *A, int len, int opt) {
  for (int i = 1, j = 0; i < len; ++i) {
    for (int k = len; ~j & k; j ^= (k >>= 1));
    if (i < j) std::swap(A[i], A[j]);
  }
  for (int h = 2; h <= len; h <<= 1) {
    LL wn = pow_mod(g, (mod - 1) / h * opt);
    for (int j = 0; j < len; j += h) {
      LL w = 1;
      for (int i = j; i < j + (h >> 1); ++i) {
        LL _t1 = A[i], _t2 = A[i + (h >> 1)] * w % mod;
        A[i] = (_t1 + _t2) % mod;
        A[i + (h >> 1)] = (_t1 - _t2) % mod;
        (w *= wn) %= mod;
      }
    }
  }
  if (opt == -1)
    for (int i = 0, v = -(mod - 1) / len; i < len; ++i)
      (A[i] *= v) %= mod;
}

inline int readInt() {
  int ans = 0, c, f = 1;
  while (!isdigit(c = getchar()))
    if (c == '-') f *= -1;
  do ans = ans * 10 + c - '0';
  while (isdigit(c = getchar()));
  return ans * f;
}

void Conv(const VLL &A, const VLL &B, VLL &ans) {
  static LL tA[N], tB[N];
  int n = A.size(), m = B.size(), len = 1;
  while (len < n + m) len <<= 1;
  for (int i = 0; i < n; ++i) tA[i] = A[i];
  for (int i = n; i < len; ++i) tA[i] = 0;
  for (int i = 0; i < m; ++i) tB[i] = B[i];
  for (int i = m; i < len; ++i) tB[i] = 0;
  NTT(tA, len, 1); NTT(tB, len, 1);
  for (int i = 0; i < len; ++i)
    (tA[i] *= tB[i]) %= mod;
  NTT(tA, len, -1);
  ans.resize(n + m - 1);
  for (int i = 0; i < n + m - 1; ++i) ans[i] = tA[i];
}

void PolyInv(const LL *A, int n, LL *B) {
  if (n == 1) {
    B[0] = pow_mod(A[0], mod - 2);
    return;
  }
  static LL tA[N], tB[N];
  int m = (n + 1) / 2, len = 1;
  while (len < n * 2) len <<= 1;
  PolyInv(A, m, B);
  for (int i = 0; i < n; ++i) tA[i] = A[i];
  for (int i = n; i < len; ++i) tA[i] = 0;
  for (int i = 0; i < m; ++i) tB[i] = B[i];
  for (int i = m; i < len; ++i) tB[i] = 0;
  NTT(tA, len, 1); NTT(tB, len, 1);
  for (int i = 0; i < len; ++i)
    (tB[i] *= (2 - tA[i] * tB[i] % mod)) %= mod;
  NTT(tB, len, -1);
  for (int i = 0; i < n; ++i) B[i] = tB[i];
}

void PolyMod(const LL *A, int n, const LL *B, int m, LL *C) {
  if (n < m) {
    for (int i = 0; i < n; ++i) C[i] = A[i];
    return;
  }
  static LL t1[N], t2[N];
  int t = n - m + 1;
  for (int i = 0; i < m; ++i) t2[i] = B[m - i - 1];
  for (int i = m; i < t; ++i) t2[i] = 0;
  PolyInv(t2, t, t1);
  int len = 1;
  while (len < 2 * t) len <<= 1;
  for (int i = t; i < len; ++i) t1[i] = t2[i] = 0;
  for (int i = 0; i < t; ++i) t2[i] = A[n - i - 1];
  NTT(t1, len, 1); NTT(t2, len, 1);
  for (int i = 0; i < len; ++i) (t1[i] *= t2[i]) %= mod;
  NTT(t1, len, -1);
  len = 1;
  while (len < n) len <<= 1;
  for (int i = 0; i < t - i - 1; ++i) std::swap(t1[i], t1[t - i - 1]);
  for (int i = t; i < len; ++i) t1[i] = 0;
  for (int i = 0; i < m; ++i) t2[i] = B[i];
  for (int i = m; i < len; ++i) t2[i] = 0;
  NTT(t1, len, 1); NTT(t2, len, 1);
  for (int i = 0; i < len; ++i) (t1[i] *= t2[i]) %= mod;
  NTT(t1, len, -1);
  for (int i = 0; i < m - 1; ++i) C[i] = (A[i] - t1[i]) % mod;
}

void Mod(const VLL &A, const VLL &B, VLL &C) {
  static LL tA[N], tB[N], tC[N];
  int n = A.size(), m = B.size();
  for (int i = 0; i < n; ++i) tA[i] = A[i];
  for (int i = 0; i < m; ++i) tB[i] = B[i];
  PolyMod(tA, n, tB, m, tC);
  int s = std::min(m - 1, n);
  C.resize(s);
  for (int i = 0; i < s; ++i) C[i] = tC[i];
}

int n, cnt;
VLL A[N], B[N];
LL x[N], y[N];

void Solve1(int t, int l, int r) {
  if (l == r) {
    A[t].clear();
    A[t].push_back(-x[l]);
    A[t].push_back(1);
  } else {
    int mid = (l + r) >> 1, L = ++cnt, R = ++cnt;
    Solve1(L, l, mid);
    Solve1(R, mid + 1, r);
    Conv(A[L], A[R], A[t]);
  }
}

void Solve2(int t, int l, int r) {
  if (l == r) {
    y[l] = B[t][0];
  } else {
    int mid = (l + r) >> 1, L = ++cnt, R = ++cnt;
    Mod(B[t], A[L], B[L]);
    Mod(B[t], A[R], B[R]);
    Solve2(L, l, mid);
    Solve2(R, mid + 1, r);
  }
}

void Solve() {
  Solve1(cnt = 0, 0, n - 1);
  B[0].resize(n);
  for (int i = 0; i < n; ++i)
    B[0][i] = A[0][i + 1] * (i + 1) % mod;
  Solve2(cnt = 0, 0, n - 1);
}
};

const int N = 300050;

int n, a, b, pre[N], nxt[N * 2], to[N * 2], cnt;
int siz[N], num[N], m;
bool on[N];

inline void addEdge(int x, int y) {
  nxt[cnt] = pre[x];
  to[pre[x] = cnt++] = y;
}

bool dfs(int x, int fa) {
  if (x == b) return on[num[m++] = x] = true;
  for (LL i = pre[x]; i >= 0; i = nxt[i])
    if (to[i] != fa && dfs(to[i], x))
      return on[num[m++] = x] = true;
  return false;
}

int dfs2(int x, int fa) {
  siz[x] = 1;
  for (LL i = pre[x]; i >= 0; i = nxt[i])
    if (to[i] != fa && !on[to[i]])
      siz[x] += dfs2(to[i], x);
  return siz[x];
}

int main() {
  scanf("%d%d%d", &n, &a, &b);
  memset(pre, -1, sizeof pre);
  for (int i = 1, x, y; i < n; ++i) {
    scanf("%d%d", &x, &y);
    addEdge(x, y);
    addEdge(y, x);
  }
  dfs(a, 0);
  Solve1::n = m + 1;
  Solve1::x[0] = 0;
  for (int i = 0; i < m; ++i)
    Solve1::x[i + 1] = Solve1::x[i] + dfs2(num[i], 0);
  Solve1::Solve();
  LL ans = 0;
  for (int i = 0; i <= m; ++i)
    (ans += ((m - i) & 1 ? -1 : 1) * pow_mod(Solve1::y[i], mod - 2)) %= mod;
  for (int i = 1; i <= n; ++i)
    (ans *= i) %= mod;
  for (int i = 1; i <= n; ++i) if (!on[i])
    (ans *= pow_mod(siz[i], mod - 2)) %= mod;
  printf("%lld\n", (ans * pow_mod(2, mod - 2) % mod + mod) % mod);
  return 0;
}
