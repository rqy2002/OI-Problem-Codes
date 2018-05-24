#include <algorithm>
#include <cstdio>
int A[100];
int main() {
  int n, m, l;
  scanf("%d%d%d", &n, &m, &l);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      for (int k = 1; k <= l; ++k)
        ++A[i + j + k];
  int ans = 0;
  for (int i = 1; i <= n + m + l; ++i)
    ans = std::max(ans, A[i]);
  for (int i = 1; i <= n + m + l; ++i)
    if (A[i] == ans) {
      printf("%d\n", i);
      break;
    }
  return 0;
}
