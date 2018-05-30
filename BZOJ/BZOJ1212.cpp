#include <cstdio>
#include <cstring>
const int N = 250, M = 1000050;
int nxt[N][26];
bool t[N];
int cnt = 1;
bool f[M];
char s[M];
void addStr() {
  int l = strlen(s), v = 0;
  for (int i = 0; i < l; ++i) {
    if (!nxt[v][s[i] - 'a'])
      nxt[v][s[i] - 'a'] = cnt++;
    v = nxt[v][s[i] - 'a'];
  }
  t[v] = 1;
}
int solve() {
  int n = strlen(s), ans;
  f[0] = 1;
  for (int i = 1; i <= n; ++i) f[i] = 0;
  for (int i = 0; i <= n; ++i) if (f[i]) {
    ans = i;
    int v = 0;
    for (int j = i; j <= n; ++j) {
      if (t[v]) f[j] = 1;
      if (j == n || !(v = nxt[v][s[j] - 'a'])) break;
    }
  }
  return ans;
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  while (n--) scanf("%s", s), addStr();
  while (m--) scanf("%s", s), printf("%d\n", solve());
  return 0;
}
