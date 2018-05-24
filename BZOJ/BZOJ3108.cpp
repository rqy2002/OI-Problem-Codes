/**************************************************************
 * Problem: BZOJ3108
 * Author: Rqy
 * Date: 2018 Feb 23
 * Algorithm: 
**************************************************************/
#include <bitset>
#include <cstdio>
const int N = 305;
std::bitset<N> out[N], zero;
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m;
    scanf("%d%d", &n, &m);
    zero.reset();
    for (int i = 0; i < n; ++i) out[i].reset();
    for (int x, y; m; --m) {
      scanf("%d%d", &x, &y);
      out[x].set(y);
    }
    bool ok = true;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        ok = ok && ((out[i] & out[j]) == zero || out[i] == out[j]);
    puts(ok ? "Yes" : "No");
  }
  return 0;
}
