#include<cstdio>
#include<cstring>
int c[30050];
int SG[30050];
int cnt[100];
int pow[2][20];
int main() {
  //freopen("new1.txt", "r", stdin);
  int n, maxq, T, i, j, p, q, k;
  scanf("%d", &T);
  for (i = 1; i <= 30000; ++i) {
    c[i] = i;
    while (!(c[i] % 2)) c[i] /= 2;
    while (!(c[i] % 3)) c[i] /= 3;
  }
  pow[0][0] = pow[1][0] = 1;
  for (i = 1; i < 16; ++i) {
    pow[0][i] = pow[0][i - 1] * 2;
    pow[1][i] = pow[1][i - 1] * 3;
  }
  while (T--) {
    scanf("%d%d", &n, &maxq);
    SG[0] = 0;
    memset(cnt, 0, sizeof cnt);
    for (i = 0; pow[0][i] <= n; ++i)
      for (j = 0; pow[0][i] * pow[1][j] <= n; ++j) {
        for (p = 1; p <= i; ++p)
          for (q = 1, k = 0; p * q <= i && q <= maxq; ++q)
            cnt[k ^= SG[pow[0][i - p * q] * pow[1][j]]] = pow[0][i] * pow[1][j];
        
        for (p = 1; p <= j; ++p)
          for (q = 1, k = 0; p * q <= j && q <= maxq; ++q)
            cnt[k ^= SG[pow[0][i] * pow[1][j - p * q]]] = pow[0][i] * pow[1][j];
        
        k = 0;
        while (cnt[k] == pow[0][i] * pow[1][j]) ++k;
        SG[pow[0][i] * pow[1][j]] = k;
      }
    int ans = 0;
    for (i = 1; i <= n; ++i) {
      scanf("%d", &j);
      if (!j)
        ans ^= SG[i / c[i]];
    }
    if (ans)
      puts("win");
    else
      puts("lose");
  }
  return 0;
}
