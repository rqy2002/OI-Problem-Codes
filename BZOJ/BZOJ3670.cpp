#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>
const int N = 1000050;
int T, n;
char s[N];
int nxt[N], num[N];
int Find(int x, int g) {
  if (x <= g) return x;
  return nxt[x] = Find(nxt[x], g);
}
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%s", s);
    n = strlen(s);
    nxt[0] = nxt[1] = 0;
    num[0] = num[1] = 0;
    for (int i = 1, j = 0; i < n; ++i) {
      while (j && s[j] != s[i]) j = nxt[j];
      int tj = j;
      nxt[i + 1] = j += s[i] == s[j];
      num[i + 1] = num[j] + (s[i] == s[tj]);
    }
    for (int i = n; i; --i)
      nxt[i] = Find(nxt[i], i / 2);
    int ans = 1;
    for (int i = 1; i <= n; ++i)
      if (nxt[i])
        ans = (long long)ans * (num[nxt[i]] + 2) % 1000000007;
    printf("%d\n", ans);
  }
  return 0;
}
