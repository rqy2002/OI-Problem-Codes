/**************************************************************
 * Problem: BZOJ2160
 * Author: Rqy
 * Date: 2018 Feb 28
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 1000050;
const int mod = 19930726;
typedef long long LL;
int pow_mod(int a, int b) {
  int ans = 1;
  for (; b; b >>= 1, a = (LL)a * a % mod)
    if (b & 1) ans = (LL)ans * a % mod;
  return ans;
}
char s[N];
int c[N], f[N];
int main() {
  int n;
  LL k;
  scanf("%d%lld%s", &n, &k, s);
  ++c[f[0] = 1];
  int r = 0;
  for (int i = 1; i < n; ++i) {
    f[i] = 0;
    if (r + f[r] > i) f[i] = std::min(f[2 * r - i], f[r] + r - i);
    while (f[i] <= i && i + f[i] < n && s[i - f[i]] == s[i + f[i]]) ++f[i];
    if (i + f[i] > r + f[r]) r = i;
    ++c[f[i]];
  }
  for (int i = n; i; --i) c[i] += c[i + 1];
  int ans = 1;
  for (int i = n; i >= 1; --i) {
    int t = std::min(k, (LL)c[i]);
    ans = (LL)ans * pow_mod(2 * i - 1, t) % mod;
    k -= t;
  }
  printf("%d\n", k ? -1 : ans);
  return 0;
}
