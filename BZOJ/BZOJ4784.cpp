#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
typedef long long LL;
const int N = 500050;
const int M = 1000050;
const int mod = 998244353;
int n, m;
int pre[N], nxt[M * 2], to[M * 2];
int task[N], cnt, f[N], deg[N];
int Q[N], low[N], t[N], going[N];
int vis[N];
inline int read() {
  char c = getchar();
  while (!isdigit(c)) c = getchar();
  int ans = 0;
  do {
    ans = ans * 10 + c - '0';
    c = getchar();
  } while (isdigit(c));
  return ans;
}
bool check(int k) {
  cnt = 0;
  f[1] = 0;
  int x = 1;
  while (x) {
    if (vis[x] < k) {
      low[x] = task[x] = ++cnt;
      t[x] = deg[x] = 0;
      going[x] = pre[x];
      vis[x] = k;
    } else
      going[x] = nxt[going[x]];
    if (going[x] < 0) {
      if (low[x] < task[f[x]] && (t[f[x]]++)) return false;
      if (low[f[x]] > low[x]) low[f[x]] = low[x];
      int u = x;
      x = f[x];
      if (low[u] != task[u]) {
        --deg[x];
        f[u] = 0;
      }
    } else if (vis[to[going[x]]] < k) {
      ++deg[f[to[going[x]]] = x];
      x = to[going[x]];
    } else if (to[going[x]] != f[x] && task[to[going[x]]] < task[x]) {
      if (low[x] > task[to[going[x]]]) low[x] = task[to[going[x]]];
      if (t[x]++) return false;
    }
  }
  return true;
}
int h[N];
int solve(int k) {
  if (!check(k)) return 0;
  int ans = 1;
  for (int i = 1; i <= n; ++i) ans = (LL)ans * h[deg[i] + (f[i] ? 1 : 0)] % mod;
  return ans;
}
int cnt2;
int main() {
  int x, y;
  h[0] = h[1] = 1;
  memset(vis, -1, sizeof vis);
  // freopen("cactus.in", "r", stdin);
  for (int i = 2; i < N; ++i) h[i] = ((LL)(i - 1) * h[i - 2] + h[i - 1]) % mod;
  for (int T = read(), k = 0; k < T; ++k) {
    n = read();
    m = read();
    memset(pre, -1, sizeof pre);
    cnt2 = 0;
    for (int i = 0; i < m; ++i) {
      x = read();
      y = read();
      nxt[cnt2] = pre[x];
      to[pre[x] = cnt2++] = y;
      nxt[cnt2] = pre[y];
      to[pre[y] = cnt2++] = x;
    }
    printf("%d\n", solve(k));
  }
  return 0;
}
