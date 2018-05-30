#include <cstdio>
int n, p, cir[70];
int Sr, Sb, Sg;
bool vis[70];
int siz[70], f[25][25][25];
int getNum() {
  for (int i = 1; i <= n; ++i)
    vis[i] = 0;
  int cnt = 0;
  for (int i = 1; i <= n; ++i) if (!vis[i]) {
    siz[cnt] = 0;
    for (int j = i; !vis[j]; j = cir[j]) {
      ++siz[cnt];
      vis[j] = 1;
    }
    ++cnt;
  }
  for (int i = 0; i <= Sr; ++i)
    for (int j = 0; j <= Sb; ++j)
      for (int k = 0; k <= Sg; ++k)
        f[i][j][k] = 0;
  f[0][0][0] = 1;
  while (cnt--)
    for (int i = Sr; i >= 0; --i)
      for (int j = Sb; j >= 0; --j)
        for (int k = Sg; k >= 0; --k) {
          if (i >= siz[cnt]) f[i][j][k] = (f[i][j][k] + f[i - siz[cnt]][j][k]) % p;
          if (j >= siz[cnt]) f[i][j][k] = (f[i][j][k] + f[i][j - siz[cnt]][k]) % p;
          if (k >= siz[cnt]) f[i][j][k] = (f[i][j][k] + f[i][j][k - siz[cnt]]) % p;
        }
  return f[Sr][Sb][Sg];
}
int main() {
  int m;
  scanf("%d%d%d%d%d", &Sr, &Sb, &Sg, &m, &p);
  n = Sr + Sb + Sg;
  int ans = 0;
  for (int i = 0; i < m; ++i) {
    for (int j = 1; j <= n; ++j)
      scanf("%d", &cir[j]);
    ans = (ans + getNum()) % p;
  }
  for (int i = 1; i <= n; ++i) cir[i] = i;
  ans = (ans + getNum()) % p;
  for (int i = 1; i < p; ++i) if (i * (m + 1) % p == 1) {
    printf("%d
", ans * i % p);
    return 0;
  }
}