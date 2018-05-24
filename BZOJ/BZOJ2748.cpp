/**************************************************************
 * Problem: BZOJ2748
 * Author: Rqy
 * Date: 2018 Feb 26
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <bitset>
#include <cstdio>
const int N = 1050;
std::bitset<N> cur, able;
int main() {
  int n, b, m, x;
  scanf("%d%d%d", &n, &b, &m);
  able.reset(); cur.reset();
  for (int i = 0; i <= m; ++i) able.set(i);
  cur.set(b);
  while (n--) {
    scanf("%d", &x);
    cur = ((cur << x) | (cur >> x)) & able;
  }
  x = m;
  while (~x && !cur.test(x)) --x;
  printf("%d\n", x);
  return 0;
}
