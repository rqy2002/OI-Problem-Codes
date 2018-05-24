/**************************************************************
 * Problem: BZOJ2456
 * Author: Rqy
 * Date: 2018 Feb 28
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
int main() {
  int n, a = 0, b = 0, x;
  scanf("%d", &n);
  while (n--) {
    scanf("%d", &x);
    x == a ? ++b : b ? --b : (a = x, ++b);
  }
  printf("%d\n", a);
  return 0;
}
