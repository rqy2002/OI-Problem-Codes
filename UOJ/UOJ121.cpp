/**************************************************************
 * Problem: UOJ121
 * Author: Rqy
 * Date: 2017 Dec 19
 * Algorithm: 
**************************************************************/
#include <bitset>
#include <cstdio>
typedef unsigned long long ULL;
const int N = 100050;
const int M = 105;
int siz[1 << 16];
inline int count(ULL a) {
  return siz[a & 65535] +
         siz[(a >> 16) & 65535] +
         siz[(a >> 32) & 65535] +
         siz[(a >> 48) & 65535];
}
struct Bitset{
  ULL a, b;
  inline int count() { return ::count(a) + ::count(b); }
  Bitset(ULL aa = 0, ULL bb = 0) : a(aa), b(bb) {}
  Bitset operator&(const Bitset &t) const {
    return Bitset(a & t.a, b & t.b);
  }
  inline void set(int x) {
    if (x < 64) a |= (1ULL << x);
    else b |= (1ULL << (x - 64));
  }
}A[N], B[N];
int n, m, k;
inline int prod(int i, int j) {
  int ans = (A[i] & A[j]).count();
  if (k == 3) {
    ans -= (A[i] & B[j]).count();
    ans -= (B[i] & A[j]).count();
    ans += (B[i] & B[j]).count();
  }
  return ans;
}
int main() {
  for (int i = 1; i < (1 << 16); ++i)
    siz[i] = siz[i & (i - 1)] + 1;
  scanf("%d%d%d", &n, &m, &k);
  int x;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      scanf("%d", &x);
      if (x % k == 1) A[i].set(j);
      else if (x % k == 2) B[i].set(j);
    }
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if ((i != j) && !(prod(i, j) % k)) {
        printf("%d %d\n", i + 1, j + 1);
        return 0;
      }
  printf("-1 -1\n");
  return 0;
}
