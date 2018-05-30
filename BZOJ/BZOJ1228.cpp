#include<cstdio>
#include<cstring>
#include<algorithm>
typedef unsigned int UI;
bool t[100];
int lowbitnum[1 << 16];
inline int lbn(UI x) {
  return x ? x & 65535 ? lowbitnum[x & 65535] : lowbitnum[x >> 16] + 16 : 0;
}
int main() {
  int n, i, j, k, s;
  for (i = 0; i < 16; ++i)
    for (k = (j = 1 << i) << 1; j < 65536; j += k)
      lowbitnum[j] = i;
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    k = 0;
    while (n) {
      n -= 2;
      scanf("%d%d", &i, &j);
      k ^= lbn(~(UI)((i - 1) | (j - 1)));
    }
    puts(k ? "YES" : "NO");
  }
  return 0;
}
