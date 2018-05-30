#include <cstdio>
const int N = 25;
int SG[N], a[N];
int f[10000];
int main() {
  int T, n, sg = 0;
  SG[0] = 0;
  for (int i = 1; i < N; ++i) {
    for (int j = 0; j < i; ++j)
      for (int k = 0; k < i; ++k)
        f[SG[j] ^ SG[k]] = i;
    for (SG[i] = 0; f[SG[i]] == i; ++SG[i]);
  }
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    sg = 0;
    for (int i = n - 1; ~i; --i) {
      scanf("%d", &a[i]);
      if (a[i] & 1) sg ^= SG[i];
    }
    if (!sg) {
      printf("-1 -1 -1\n0\n");
      continue;
    }
    int ans = 0;
    for (int i = n - 1; ~i; --i)
      for (int j = i - 1; ~j; --j)
        for (int k = j; ~k; --k)
          if (a[i] && !(sg ^ SG[i] ^ SG[k] ^ SG[j]) && !(ans++))
            printf("%d %d %d\n", n - i - 1, n - j - 1, n - k - 1);
    printf("%d\n", ans);
  }
  return 0;
}
