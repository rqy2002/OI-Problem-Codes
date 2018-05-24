/**************************************************************
 * Problem: BZOJ2751
 * Author: Rqy
 * Date: 2018 Feb 22
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <map>
#include <set>
typedef long long LL;
const int mod = 1000000007;
std::map<int, int> M;
std::map<int, std::set<int> > MS;
int main() {
  int n, m, k, x, y;
  scanf("%d%d%d", &n, &m, &k);
  n = (LL)n * (n + 1) / 2 % mod;
  while (k--) {
    scanf("%d%d", &x, &y);
    if (!M.count(x)) {
      M[x] = n;
      MS[x] = std::set<int>();
    }
    if (!MS[x].count(y)) {
      (M[x] -= y) %= mod;
      MS[x].insert(y);
    }
  }
  int ans = 1;
  m -= M.size();
  for (; m; m >>= 1, n = (LL)n * n % mod)
    if (m & 1) ans = (LL)ans * n % mod;
  for (std::map<int, int>::iterator it = M.begin(); it != M.end(); ++it)
    ans = (LL)ans * it->second % mod;
  printf("%d\n", (ans + mod) % mod);
  return 0;
}
