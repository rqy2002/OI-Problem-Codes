/**************************************************************
 * Problem: BZOJ1415
 * Author: Rqy
 * Date: 2018 Feb 24
 * Algorithm: 
**************************************************************/
#include <cstdio>
#include <cstring>
const int N = 1050;
bool e[N][N];
int n, nxt[N][N];
void bfs(int x) {
  static bool vis[N];
  static int que[N];
  memset(vis, 0, sizeof vis);
  int hd = 0, tl = 0;
  vis[que[tl++] = x] = true;
  while (hd < tl) {
    int y = que[hd++];
    for (int z = 1; z <= n; ++z)
      if (e[y][z] && !vis[z]) {
        nxt[x][z] = (y == x ? z : nxt[x][y]);
        vis[que[tl++] = z] = true;
      }
  }
}
bool vis[N][N];
double f[N][N];
double F(int s, int t) {
  if (vis[s][t]) return f[s][t];
  double &ans = f[s][t];
  vis[s][t] = true;
  if (s == t) return ans = .0;
  if ((s = nxt[s][t]) == t) return ans = 1.0;
  if ((s = nxt[s][t]) == t) return ans = 1.0;
  int d = 0;
  for (int i = 1; i <= n; ++i) if (e[t][i])
    ans += F(s, i), ++d;
  return (ans /= d) += 1;
}
int main() {
  int m, s, t;
  scanf("%d%d%d%d", &n, &m, &s, &t);
  while (m--) {
    int x, y;
    scanf("%d%d", &x, &y);
    e[x][y] = e[y][x] = true;
  }
  for (int i = 1; i <= n; ++i) e[i][i] = true;
  for (int i = 1; i <= n; ++i) bfs(i);
  printf("%.3lf", F(s, t));
  return 0;
}
