#include <cstdio>
const int N = 1005;
int prime[N], cnt;
int e[N];
void getPrime() {
  int i, j;
  cnt = 0;
  for (i = 2; i < N; ++i) {
    for (j = 0; j < cnt; ++j)
      if (!(i % prime[j])) break;
    if (j == cnt) prime[cnt++] = i;
  }
}
void getFac(int n, int op) {
  for (int i = 0, k = n; i < cnt; ++i, k = n)
    while (k) {
      k /= prime[i];
      e[i] += k * op;
    }
}
int ans[100000], len;
void mul(int t) {
  int i, c;
  for (i = 0, c = 0; i < len || c; ++i) {
    c = (ans[i] = ans[i] * t + c) / 10;
    ans[i] %= 10;
  }
  len = i;
}
int main() {
  getPrime();
  int n;
  scanf("%d", &n);
  getFac(n - 2, 1);
  int tot = n - 2, m = n;
  for (int i = 0; i < n; ++i) {
    int t;
    scanf("%d", &t);
    if (t < 0) continue;
    --m;
    tot -= --t;
    getFac(t, -1);
  }
  if (tot < 0) return printf("0\n"), 0;
  getFac(tot, -1);
  ans[0] = len = 1;
  for (int i = 0; i < cnt; ++i)
    while (e[i]--) mul(prime[i]);
  while (tot--) mul(m);
  while (len--) printf("%d", ans[len]);
  return 0;
}
