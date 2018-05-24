/**************************************************************
 * Problem: BZOJ4915
 * Author: Rqy
 * Date: 2018 Feb 24
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
typedef long long LL;
int main() {
  LL l, r;
  scanf("%lld%lld", &l, &r);
  if (!l) ++l;
  printf("4\n%lld\n", std::max(r / 29 - l + 1, 0LL) + std::max(r / 11 - l + 1, 0LL));
  return 0;
}
