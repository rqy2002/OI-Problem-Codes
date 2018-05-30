#include <cstdio>
#include <cstring>
const int N = 1050;
const int L = 505;
bool f[N][L];
char s1[N];
char s2[L];
int main() {
  int t;
  scanf("%s%d", s1, &t);
  int ans = 0;
  int n = strlen(s1);
  while (t--) {
    scanf("%s", s2);
    int m = strlen(s2);
    if (!n || !m) {
      ++ans;
      continue;
    }
    memset(f, 0, sizeof f);
    f[0][0] = true;
    for (int i = 1; i <= n; ++i)
      for (int j = 0, f2 = 0; j <= m; ++j) {
        f2 = f2 || f[i - 1][j];
        if (s1[i - 1] != '*')
          f[i][j] = j && (s1[i - 1] == '?' || s1[i - 1] == s2[j - 1]) && f[i - 1][j - 1];
        else
          f[i][j] = f2;
      }
    ans += !f[n][m];
  }
  printf("%d\n", ans);
  return 0;
}
