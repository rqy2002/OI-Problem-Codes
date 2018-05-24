/**************************************************************
 * Problem: BZOJ4917
 * Author: Rqy
 * Date: 2018 Feb 26
 * Algorithm: 
**************************************************************/
#include <cstdio>
typedef unsigned int UI;
int main() {
  int Q;
  scanf("%d", &Q);
  while (Q--) {
    UI t;
    scanf("%u", &t);
    t *= 4294901761u;
    t ^= (t >> 11); t ^= (t >> 22);
    t *= 954437177u;
    t ^= (t >> 6); t ^= (t >> 12); t ^= (t >> 24);
    t *= 3222273025u;
    printf("%u\n", t);
  }
  return 0;
}
