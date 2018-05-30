#include <algorithm>
#include <cstdio>
const int N = 100050;
int s[N][2], mindep[N], maxdep[N];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &s[i][0], &s[i][1]);
    s[i][0] = std::max(s[i][0], 0);
    s[i][1] = std::max(s[i][1], 0);
  }
  for (int i = n; i; --i) {
    int l = s[i][0], r = s[i][1];
    mindep[i] = std::min(mindep[l], mindep[r]) + 1;
    maxdep[i] = std::max(maxdep[l], maxdep[r]) + 1;
  }
  if (maxdep[1] - mindep[1] > 1) return puts("-1") & 0;
  int ans = 0;
  for (int o = n; o; --o) {
    if (mindep[o] == maxdep[o]) continue;
    int l = s[o][0], r = s[o][1];
    if (maxdep[l] <= mindep[r])
      ++ans;
    if (mindep[r] != maxdep[r] && mindep[l] != maxdep[l])
      return puts("-1") & 0;
  }
  return printf("%d\n", ans) & 0;
}
