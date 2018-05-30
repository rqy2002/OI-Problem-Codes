#include <cstdio>
const int N = 205;
bool map[N][N];
int n, my[N], vis[N], time;
bool match(int x) {
  for (int y = 1; y <= n; ++y) if (map[x][y] && vis[y] != time) {
    vis[y] = time;
    if (!my[y] || match(my[y])) {
      my[y] = x;
      return true;
    }
  }
  return false;
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    int x;
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j) {
        scanf("%d", &x);
        map[i][j] = x;
        my[i] = 0;
      }
    bool ok = true;
    for (int i = 1; i <= n; ++i) {
      ++time;
      ok = ok && match(i);
    }
    puts(ok ? "Yes" : "No");
  }
  return 0;
}
