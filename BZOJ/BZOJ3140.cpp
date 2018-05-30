#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 5000;
int A[N][N], S;
int gg[N];
int my[N], vis[N], time, time2;
int a, b, c;
bool match(int x) {
  for (int y = 1; y <= c; ++y) if (vis[y] < time && (A[x][y] & ~S)) {
    vis[y] = time;
    if (gg[y] < time2 || !my[y] || match(my[y])) {
      gg[y] = time2;
      my[y] = x;
      return true;
    }
  }
  return false;
}
int solve() {
  ++time2;
  int ans = 0;
  for (int x = 1; x <= b; ++x)
    ++time, ans += match(x);
  return ans;
}
int siz[1 << 20];
int main() {
  int T;
  scanf("%d", &T);
  for (int i = 1; i < (1 << 20); ++i)
    siz[i] = siz[i & (i - 1)] + 1;
  while (T--) {
    scanf("%d%d%d", &a, &b, &c);
    int t = (a < b) ? ((a < c) ? 0 : 2) : ((b < c) ? 1 : 2);
    int x;
    for (int i = 1; i <= a; ++i)
      for (int j = 1; j <= b; ++j)
        for (int k = 1; k <= c; ++k) {
          scanf("%d", &x);
          if (t == 0 && i == 1) A[j][k] = 0;
          if (t == 1 && j == 1) A[i][k] = 0;
          if (t == 2 && k == 1) A[i][j] = 0;
          if (x) {
            if (t == 0) A[j][k] |= (1 << (i - 1));
            else if (t == 1) A[i][k] |= (1 << (j - 1));
            else A[i][j] |= (1 << (k - 1));
          }
        }
    if (t == 1) std::swap(a, b);
    else if (t == 2) std::swap(a, c);
    int ans = a;
    for (S = 0; S < (1 << a); ++S)
      ans = std::min(ans, solve() + siz[S]);
    printf("%d\n", ans);
  }
}
