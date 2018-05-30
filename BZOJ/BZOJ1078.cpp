#include <cstdio>
#include <cstring>
int fa[200], lc[200], rc[200];
int siz[200];
int p[200][200];
int main() {
  int n;
  scanf("%d", &n);
  ++n;
  for (int i = 1; i < n; ++i) {
    int x;
    scanf("%d", &x);
    if (x < 100) lc[fa[i] = x] = i;
    else rc[fa[i] = x - 100] = i;
  }
  for (int i = n - 1; i >= 0; --i) {
    siz[i] = siz[lc[i]] + siz[rc[i]] + 1;
    if (!rc[i] || siz[lc[i]] >= siz[rc[i]]) {
      int k = siz[lc[i]] - (rc[i] == 0 ? 0 : siz[rc[i]]);
      if (k == 1) {
        p[i][0] = i;
        for (int j = 0; j < siz[i]; j += 2) {
          p[i][j + 1] = p[lc[i]][j / 2];
          p[i][j + 2] = p[rc[i]][j / 2];
        }
        continue;
      }
      for (int j = 0; j < k; ++j)
        p[i][j] = p[lc[i]][j];
      p[i][k] = i;
      for (int j = 0; j < siz[i] - k; j += 2) {
        p[i][j + k + 1] = p[rc[i]][j / 2];
        p[i][j + k + 2] = p[lc[i]][j / 2 + k];
      }
    } else if (siz[lc[i]] < siz[rc[i]]) {
      int k = siz[rc[i]] - siz[lc[i]] + 1;
      for (int j = 0; j < k; ++j)
        p[i][j] = p[rc[i]][j];
      p[i][k] = i;
      for (int j = 0; j < siz[i] - k; j += 2) {
        p[i][j + k + 1] = p[lc[i]][j / 2];
        p[i][j + k + 2] = p[rc[i]][j / 2 + k];
      }
    }
  }
  for (int i = 0; i < n; ++i)
    printf("%d ", p[0][i]);
  return 0;
}
