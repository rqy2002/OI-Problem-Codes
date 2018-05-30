#include <algorithm>
#include <cstdio>
long long s[1000005];
int main() {
  int n, a;
  scanf("%d", &n);
  scanf("%lld", &s[0]);
  for (int i = 1; i < n; ++i) {
    scanf("%lld", &s[i]);
    s[i] += s[i - 1];
  }
  for (int i = 0; i < n; ++i) s[i] = s[i] - s[n - 1] / n * (i + 1);
  std::sort(s, s + n);
  long long ans = 0;
  for (int i = 0; i < n; ++i) ans += std::abs(s[i] - s[(n + 1) / 2]);
  return !printf("%lld\n", ans);
}
