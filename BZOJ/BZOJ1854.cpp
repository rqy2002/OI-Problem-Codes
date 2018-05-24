/**************************************************************
 * Problem: BZOJ1854
 * Author: Rqy
 * Date: 2018 Feb 26
 * Algorithm: 
**************************************************************/
#include <cstdio>
const int N = 10050;
int fa[N], e[N];
int find(int x) { return fa[x] ? fa[x] = find(fa[x]) : x; }
int main() {
  int n;
  scanf("%d", &n);
  for (int x, y; n; --n) {
    scanf("%d%d", &x, &y);
    if ((x = find(x)) != (y = find(y)))
      fa[x] = y, e[y] += e[x];
    ++e[y];
  }
  for (int i = 1; i < N; ++i) if (!(e[find(i)]--)) {
    printf("%d\n", i - 1);
    break;
  }
  return 0;
}
