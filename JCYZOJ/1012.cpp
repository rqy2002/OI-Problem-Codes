/**************************************************************
 * Problem: JCYZOJ 2012
 * Author: Rqy
 * Date: 2018 Feb 13
 * Algorithm: sort
**************************************************************/
#include <cassert>
#include <cstdio>
typedef long long LL;
const int N = 10;
int n;
LL seed, a, b, c;
int Rand() {
    seed = seed << 5 | seed;
    seed = seed * a + b;
    seed ^= c;
    seed = seed < 0 ? -seed : seed;
    return seed;
}
int num[2][N], *x, *y;
void output() {
  LL res = 1;
  for (int i = 1; i <= n; ++i) {
    int now = x[i - 1] + i;
    now = now << 5 | now;
    now = now * a + b;
    now ^= c;
    now = now < 0 ? -now : now;
    res = (res + now) % 19260817;
  }
  printf("%lld\n", res);
}
int ct[256];

int main() {
  scanf("%d%lld%lld%lld%lld", &n, &seed, &a, &b, &c);
  int i;
  x = num[0];
  y = num[1];
  for (i = 0; i < n; ++i)
    x[i] = Rand();

  for (i = 0; i < 256; ++i) ct[i] = 0;
  for (i = 0; i < n; ++i) ++ct[(x[i] >> 0) & 255];
  for (i = 1; i < 256; ++i) ct[i] += ct[i - 1];
  for (i = n - 1; ~i; --i) y[--ct[(x[i] >> 0) & 255]] = x[i];

  for (i = 0; i < 256; ++i) ct[i] = 0;
  for (i = 0; i < n; ++i) ++ct[(y[i] >> 8) & 255];
  for (i = 1; i < 256; ++i) ct[i] += ct[i - 1];
  for (i = n - 1; ~i; --i) x[--ct[(y[i] >> 8) & 255]] = y[i];

  for (i = 0; i < 256; ++i) ct[i] = 0;
  for (i = 0; i < n; ++i) ++ct[(x[i] >> 16) & 255];
  for (i = 1; i < 256; ++i) ct[i] += ct[i - 1];
  for (i = n - 1; ~i; --i) y[--ct[(x[i] >> 16) & 255]] = x[i];

  for (i = 0; i < 256; ++i) ct[i] = 0;
  for (i = 0; i < n; ++i) ++ct[(y[i] >> 24) & 255];
  for (i = 1; i < 256; ++i) ct[i] += ct[i - 1];
  for (i = n - 1; ~i; --i) x[--ct[(y[i] >> 24) & 255]] = y[i];
  
  for (i = 1; i < n; ++i)
    assert(x[i] > x[i - 1]);
}
