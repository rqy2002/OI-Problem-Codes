#include <algorithm>
#include <cstdio>
#include <cstring>
using std::min;
const int N = 10050;
int c[N], f[N][2];
int to[N * 2], nxt[N * 2], pre[N];
int n, m;
void dfs(int x, int fa) {
  f[x][0] = f[x][1] = 1;
  if (x <= n) {
    f[x][c[x] ^ 1] = 1000000000;
    return;
  }
  for (int i = pre[x]; ~i; i = nxt[i])
    if (to[i] != fa) {
      dfs(to[i], x);
      f[x][0] += min(f[to[i]][0] - 1, f[to[i]][1]);
      f[x][1] += min(f[to[i]][1] - 1, f[to[i]][0]);
    }
}
int main() {
  scanf("%d%d", &m, &n);
  memset(pre, -1, sizeof pre);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &c[i]);
  int cnt = 0;
  for (int i = 1, x, y; i < m; ++i) {
    scanf("%d %d", &x, &y);
    nxt[cnt] = pre[x]; to[pre[x] = cnt++] = y;
    nxt[cnt] = pre[y]; to[pre[y] = cnt++] = x;
  }
  dfs(m, -1);
  printf("%d\n", min(f[m][0], f[m][1]));
  return 0;
}
