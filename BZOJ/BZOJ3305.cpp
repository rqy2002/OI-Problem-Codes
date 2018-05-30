#include <algorithm>
#include <cstdio>
typedef long long LL;
const int mod = 1000000009;
int main() {
  int n, ans = 1;
  scanf("%d", &n);
  for (int i = 1; i < n; ++i)
    ans = (LL)ans * (2 * i + 1) % mod;
  printf("%d\n", ans);
  return 0;
}
