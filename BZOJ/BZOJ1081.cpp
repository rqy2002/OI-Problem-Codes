/**************************************************************
 * Problem: BZOJ1081
 * Author: Rqy
 * Date: 2018 Feb 25
 * Algorithm: 
**************************************************************/
#include <cstdio>
const int N = 20;
int T[N];
int b, n;
inline int get(int x) { return x < 10 ? x + '0' : x - 10 + 'A'; }
inline void put() {
  for (int i = 0; i < n; ++i) putchar(get(T[i]));
  putchar('\n');
}
void dfs(int x, bool rev) {
  if (!x) put();
  else if (rev)
    for (T[--x] = b - 1; ~T[x]; --T[x])
      dfs(x, ~T[x] & 1);
  else
    for (T[--x] = 0; T[x] < b; ++T[x])
      dfs(x, T[x] & 1);
}
int main() {
  scanf("%d%d", &n, &b);
  dfs(n, false);
  return 0;
}
