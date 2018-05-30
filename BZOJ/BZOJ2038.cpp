#include <algorithm>
#include <cstdio>
#include <cstring>
typedef long long LL;
const int N = 50050;
int C[N], t[N];
int p[N], L[N], R[N];
LL ansv[N][2];
int k;
bool cmp(int a, int b) {
  if (L[a] / k != L[b] / k) return L[a] / k < L[b] / k;
  return R[a] < R[b];
}
LL gcd(LL a, LL b) {
  return a && b ? gcd(b, a % b) : a | b;
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) scanf("%d", &C[i]);
  for (int i = 0; i < m; ++i) scanf("%d%d", &L[i], &R[i]), p[i] = i;
  k = 0;
  while (k * k < n) ++k;
  std::sort(p, p + m, cmp);
  LL ans = 0, l = 0, r = -1, q, g;
  for (int i = 0; i < m; ++i) {
    while (r < R[p[i]] - 1) ans += t[C[++r]]++;
    while (l > L[p[i]] - 1) ans += t[C[--l]]++;
    while (r > R[p[i]] - 1) ans -= --t[C[r--]];
    while (l < L[p[i]] - 1) ans -= --t[C[l++]];
    q = r - l;
    q = q * (q + 1) / 2;
    g = gcd(ans, q);
    ansv[p[i]][0] = ans / g;
    ansv[p[i]][1] = q / g;
  }
  for (int i = 0; i < m; ++i)
    printf("%lld/%lld\n", ansv[i][0], ansv[i][1]);
  return 0;
}
