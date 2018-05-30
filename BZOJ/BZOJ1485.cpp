#include <cstdio>
typedef long long LL;
const int N = 1000050;
int prime[1000000];
int cnt = 0;
bool mark[2 * N];
int n, P;
void getPrime() {
  mark[0] = 1;
  for (int i = 2; i <= 2 * n; ++i) {
    if (!mark[i])
      prime[cnt++] = i;
    for (int j = 0; j < cnt && (LL)prime[j] * i <= 2 * n; ++j) {
      mark[prime[j] * i] = 1;
      if (!(i % prime[j])) break;
    }
  }
}
int get(int l, int p) {
  int ans = 0;
  while (l) ans += (l /= p);
  return ans;
}
int powMod(int x, int b) {
  int ans = 1;
  for (; b; b >>= 1, x = (LL)x * x % P)
    if (b & 1) ans = (LL)ans * x % P;
  return ans;
}
int main() {
  scanf("%d%d", &n, &P);
  getPrime();
  int ans = 1;
  for (int i = 0; i < cnt; ++i) {
    int p = prime[i];
    int g = 0;
    int tn = n + 1;
    while (!(tn % p)) --g, tn /= p;
    g += get(2 * n, p) - get(n, p) * 2;
    ans = (LL)ans * powMod(p, g) % P;
  }
  printf("%d\n", ans);
  return 0;
}
