#include <algorithm>
#include <cstdio>
const int N = 1005;
const int mod = 19650827;
int H[N], _f[2][N], _g[2][N];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d", &H[i]);
  int *f = _f[0], *g = _g[0], *ff = _f[1], *gg = _g[1];
  for (int i = 0; i < n; ++i) f[i] = 1;
  for (int i = 1; i < n; ++i) { 
    std::swap(f, ff); 
    std::swap(g, gg);
    for (int j = 0; i + j < n; ++j) {
      f[j] = g[j] = 0;
      if (H[j] < H[j + 1]) f[j] += ff[j + 1];
      if (H[j] < H[j + i]) f[j] += gg[j + 1];
      if (H[j + i] > H[j]) g[j] += ff[j];
      if (H[j + i] > H[j + i - 1]) g[j] += gg[j];
      f[j] %= mod;
      g[j] %= mod;
      //printf("%d %d   ", f[j], g[j]);
    }
    //printf("\n");
  }
  printf("%d\n", (f[0] + g[0]) % mod);
  return 0;
}
