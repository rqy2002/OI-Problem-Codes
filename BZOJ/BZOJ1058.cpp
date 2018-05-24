/**************************************************************
 * Problem: BZOJ1058
 * Author: Rqy
 * Date: 2018 Feb 25
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <set>
#include <map>
const int N = 500050;
int A[N], B[N], ans2;
std::set<int> S;
std::map<int, int> M;
void updS(int x) {
  if (!S.empty()) {
    std::set<int>::iterator it = S.end();
    if (x > *(--it)) {
      ans2 = std::min(ans2, x - *it);
    } else {
      it = S.lower_bound(x);
      ans2 = std::min(ans2, *it - x);
      if (it != S.begin()) ans2 = std::min(ans2, x - *(--it));
    }
  }
  S.insert(x);
}
inline void delM(int x) { if (!--M[x]) M.erase(x); }
inline void addM(int x) { if (!M.count(x)) M[x] = 0; ++M[x]; }
int main() {
  int n, m, x, y;
  scanf("%d%d", &n, &m);
  ans2 = 10000000;
  for (int i = 1; i <= n; ++i) scanf("%d", &A[i]), updS(B[i] = A[i]);
  for (int i = 1; i < n; ++i) addM(std::abs(A[i + 1] - A[i]));
  char s[20];
  while (m--) {
    scanf("%s", s);
    if (*s == 'I') {
      scanf("%d%d", &x, &y);
      updS(y);
      if (x < n) {
        delM(std::abs(A[x + 1] - B[x]));
        addM(std::abs(A[x + 1] - y));
      }
      addM(std::abs(y - B[x]));
      B[x] = y;
    } else if (s[4] == 'S')
      printf("%d\n", ans2);
    else
      printf("%d\n", M.begin()->first);
  }
  return 0;
}
