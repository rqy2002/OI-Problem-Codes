#include <cstdio>
#include <cstring>
const int N = 105;
int fa[N], dis[N];
int Find(int x) {
  if (fa[x]) {
    int t = Find(fa[x]);
    dis[x] += dis[fa[x]];
    return fa[x] = t;
  } else
    return x;
}
bool Union(int s, int t, int v) {
  int ss = Find(s), tt = Find(t);
  if (ss == tt) return dis[t] - dis[s] == v;
  fa[tt] = ss;
  dis[tt] = v - dis[t] + dis[s];
  return true;
}
int main() {
  int w, m;
  scanf("%d", &w);
  while (w--) {
    memset(fa, 0, sizeof fa);
    memset(dis, 0, sizeof dis);
    scanf("%*d%d", &m);
    bool ok = true;
    int s, t, v;
    while (m--) {
      scanf("%d%d%d", &s, &t, &v);
      ok = ok && Union(s, t + 1, v);
    }
    puts(ok ? "true" : "false");
  }
  return 0;
}
