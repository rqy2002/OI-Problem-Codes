/**************************************************************
 * Problem: Luogu P1903
 * Author: Rqy
 * Date: 2017 Dec 26
 * Algorithm: 暴力,bitset
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <bitset>
#include <map>
const int N = 12000;
unsigned A[N];
std::bitset<N> B[32768];
std::bitset<N> ans;
int L;
void build(int n) {
  L = 1;
  while (L < n) L <<= 1;
  for (int i = 0; i < L; ++i) {
    B[i + L].reset();
    B[i + L].set((unsigned)A[i]);
  }
  for (int i = L - 1; i; --i)
    B[i] = B[i << 1] | B[i << 1 | 1];
}
void modify(int x, unsigned y) {
  unsigned z = A[x];
  if (z == y) return;
  int i = x + L;
  A[x] = y;
  do {
    B[i].set(y); i >>= 1;
  } while (i && !B[i].test(y));
  B[i = x + L].reset(z);
  while (i > 1 && !B[i ^ 1].test(z))
    B[i >>= 1].reset(z);
}
int query(int x, int y) {
  ans.reset();
  --x; ++y;
  for (x += L, y += L; x != (y ^ 1); x >>= 1, y >>= 1) {
    if (~x & 1) ans |= B[x ^ 1];
    if (y & 1) ans |= B[y ^ 1];
  }
  return (int)ans.count();
}
unsigned get(int x) {
  static unsigned p = 0;
  static std::map<int, unsigned> M;
  if (M.count(x)) return M[x];
  return M[x] = p++;
}
char s[10];
int main() {
  int n, q, x, y;
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x);
    A[i] = get(x);
  }
  build(n + 2);
  while (q--) {
    scanf("%s%d%d", s, &x, &y);
    if (*s == 'R') modify(x, get(y));
    else printf("%d\n", query(x, y));
  }
  return 0;
}
