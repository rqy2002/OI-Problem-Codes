#include<cstdio>
#include<cstring>
#include<algorithm>
const int mod = 45989;
typedef long long LL;
int A, B, N, M;
LL t;
struct Martix {
  int n;
  int a[200][200];
  Martix(int nn = 0) : n(nn) {
    memset(a, 0, sizeof a);
  }
  friend Martix operator * (Martix a, Martix b) {
    Martix c(a.n);
    for (int k = 0; k < a.n; ++k)
      for (int i = 0; i < a.n; ++i)
        for (int j = 0; j < a.n; ++j)
          c.a[i][j] = (c.a[i][j] + (LL)a.a[i][k] * b.a[k][j]) % mod;
    return c;
  }
};
Martix a, b;
int x[150], y[150];
int main() {
  int i, j;
  scanf("%d%d%lld%d%d", &N, &M, &t, &A, &B);
  if (t == 0) {
    printf("%d", A == B);
    return 0;
  } else if (t < 0) {
    printf("0");
    return 0;
  }
  a.n = b.n = M * 2;
  for (i = 0; i < M; ++i) {
    scanf("%d%d", &x[i], &y[i]);
    x[M + i] = y[i];
    y[M + i] = x[i];
  }
  for (i = 0; i < M * 2; ++i)
    for (j = 0; j < M * 2; ++j)
      if (j != i + M && i != j + M && y[i] == x[j])
        ++a.a[i][j];
  for (i = 0; i < M * 2; ++i)
    b.a[i][i] = 1;
  for (--t; t; t /= 2, a = a * a)
    if (t & 1) b = a * b;
  int ans = 0;
  for (i = 0; i < M * 2; ++i) if (x[i] == A)
      for (j = 0; j < M * 2; ++j) if (y[j] == B)
          ans = (ans + b.a[i][j]) % mod;
  printf("%d", ans);
  return 0;
}
