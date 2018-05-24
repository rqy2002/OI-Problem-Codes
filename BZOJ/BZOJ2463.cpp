/**************************************************************
 * Problem: BZOJ2463
 * Author: Rqy
 * Date: 2018 Feb 28
 * Algorithm: 
**************************************************************/
#include <cstdio>
int main() {
  int n;
  while (~scanf("%d", &n) && n) puts(n & 1 ? "Bob" : "Alice");
  return 0;
}
