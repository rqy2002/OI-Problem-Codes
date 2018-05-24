/**************************************************************
 * Problem: BZOJ2761
 * Author: Rqy
 * Date: 2018 Feb 25
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <set>
std::set<int> S;
int main() {
  int T, n, x;
  scanf("%d", &T);
  while (T--) {
    S.clear();
    scanf("%d", &n);
    bool fst = true;
    while (n--) {
      scanf("%d", &x);
      if (S.count(x)) continue;
      S.insert(x);
      if (!fst) printf(" ");
      else fst = false;
      printf("%d", x);
    }
    if (T) puts("");
  }
}
