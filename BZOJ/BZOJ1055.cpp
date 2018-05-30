#include <cstdio>
int readWING() {
  char c;
  do c = getchar();
  while (c != EOF && c != 'W' && c != 'I' && c != 'N' && c != 'G');
  if (c == 'W') return 0;
  if (c == 'I') return 1;
  if (c == 'N') return 2;
  if (c == 'G') return 3;
  return EOF;
}
const int N = 205;
char s[N];
int A[N];
bool f[N][N][4];
int num[4], to[4][20][2];
int main() {
  for (int i = 0; i < 4; ++i)
    scanf("%d", &num[i]);
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < num[i]; ++j) {
      to[i][j][0] = readWING();
      to[i][j][1] = readWING();
    }
  int n;
  scanf("%s", s);
  for (n = 0; s[n]; ++n)
    A[n] = s[n] == 'W' ? 0 : s[n] == 'I' ? 1 : s[n] == 'N' ? 2 : 3;
  for (int i = 0; i < n; ++i) f[i][i + 1][A[i]] = 1;
  for (int l = 2; l <= n; ++l)
    for (int i = 0; i + l <= n; ++i)
      for (int j = i + l, k = 0; k < 4; ++k)
        for (int l = 0; l < num[k]; ++l)
          for (int t = i + 1; t < j; ++t)
            if (f[i][t][to[k][l][0]] && f[t][j][to[k][l][1]]) {
              f[i][j][k] = 1;
              l = num[k];
              break;
            }
  bool c = false;
  for (int i = 0; i < 4; ++i)
    if (f[0][n][i]) {
      putchar("WING"[i]);
      c = true;
    }
  if (!c) puts("The name is wrong!");
  return 0;
}
