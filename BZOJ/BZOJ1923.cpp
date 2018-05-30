#include<cstdio>
#include<bitset>
#include<algorithm> 
using std::bitset;
bitset<1005> A[2005];
int main() {
  int n, m, i, j, k, x;
  scanf("%d%d", &n, &m);
  for (i = 0; i < m; ++i) {
    A[i].reset();
    for (j = 0; j <= n; ++j) {
      scanf("%1d", &x);
      if (x)
        A[i].set(j);
    }
  }
  int ans = 0;
  for (i = 0; i < n; ++i) {
    for (j = i; j < m; ++j)
      if (A[j].test(i))
        break;
    if (j >= m)
      return !puts("Cannot Determine");
    if (j > ans) ans = j;
    std::swap(A[j], A[i]);
    for (j = 0; j < m; ++j)
      if (j != i && A[j].test(i))
        A[j] ^= A[i];
  }
  printf("%d\n", ans + 1);
  for (i = 0; i < n; ++i)
    puts(A[i].test(n) ? "?y7M#" : "Earth");
  return 0;
}
