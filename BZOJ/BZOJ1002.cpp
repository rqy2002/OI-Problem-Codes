#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
typedef long long LL;
const LL wei = 10000000;
LL b[110][200];
void mul(LL *x, int a) {
  int i, c;
  for (i = 1, c = 0; i <= x[0] || c; ++i) {
    c = (x[i] = x[i] * a + c) / wei;
    x[i] %= wei;
  }
  x[0] = i - 1;
}
void sub(LL *x, const LL *a) {
  int i, c;
  for (i = 1, c = 0; i <= a[0] || c; ++i) {
    c = (wei - 1 - (x[i] = x[i] - a[i] - c)) / wei;
    x[i] = (x[i] + wei) % wei;
  }
  while (!x[x[0]]) --x[0];
}
void sub(LL *x, int a) {
  int i, c = -a;
  for (i = 1; c; ++i) {
    c = (x[i] = x[i] + c) / wei;
    x[i] = (x[i] + wei) % wei;
  }
  while (!x[x[0]]) --x[0];
}
int main() {
  //freopen("bzoj_1002.in", "r", stdin);
  //freopen("bzoj_1002.out", "w", stdout);
  int n, i;
  scanf("%d", &n);
  b[0][0] = b[0][1] = 0;
  b[1][0] = b[1][1] = 1;
  for (i = 2; i <= n + 1; ++i) {
    memcpy(b[i], b[i - 1], sizeof b[i]);
    mul(b[i], 3);
    sub(b[i], b[i - 2]);
  }
  sub(b[n + 1], b[n - 1]);
  sub(b[n + 1], 2);
  printf("%lld", b[n + 1][b[n + 1][0]]);
  for (i = b[n + 1][0] - 1; i; --i)
    printf("%07lld", b[n + 1][i]);
  return 0;
}