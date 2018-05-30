#include <algorithm>
#include <cstdio>
using std::max;
using std::min;
double dfs(double t, int n) {
  if (n == 1) {
    if (t > 1.0) return t;
    return 1.0 / t;
  }
  double ans = 1e15;
  for (int i = 1; i <= n / 2; ++i) {
    double ans1 = max(dfs(t / n * i, i), dfs(t / n * (n - i), n - i));
    double ans2 = max(dfs(t * n / i, i), dfs(t * n / (n - i), n - i));
    ans = min(ans, min(ans1, ans2));
  }
  return ans;
}
int main() {
  double x, y;
  int n;
  scanf("%lf%lf%d", &x, &y, &n);
  printf("%.6lf\n", dfs(x / y, n));
  return 0;
}
