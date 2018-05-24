/**************************************************************
 * Problem: BZOJ5104
 * Author: Rqy
 * Date: 2018 Feb 27
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <map>
const int mod = 1000000009;
const int inv2 = 500000005;
const int g = 13;
const int S = 32000;
std::map<int, int> M;
typedef long long LL;
inline int pow_mod(int a, int b) {
  int ans = 1;
  for (b = (b % (mod-1) + mod-1) % (mod-1); b; b >>= 1, a = (LL)a * a % mod)
    if (b & 1) ans = (LL)ans * a % mod;
  return ans;
}
int BSGS(int g, int x) {
  if (x == 1) return 0;
  int gS = pow_mod(g, S);
  M.clear();
  for (int i = 0, t = x; i < S; ++i, t = (LL)t * g % mod) M[t] = i;
  for (int i = 1, t = gS; i <= S; ++i, t = (LL)t * gS % mod)
    if (M.count(t)) return i * S - M[t];
  return 0;
}
int sqrt(LL x) {
  int p = BSGS(g, (x % mod + mod) % mod);
  if ((p & 1) || (!p && x != 1)) return 0;
  return pow_mod(g, p >> 1);
}
int main() {
  int n;
  scanf("%d", &n);
  int s5 = mod-sqrt(5);
  int x = (LL)(1 + s5) * inv2 % mod;
  int ans = 0x7fffffff;
  int n5 = (LL)n * s5 % mod;
  if (int d = sqrt(5LL * n * n + 4)) {
    int r1 = ((LL)(n5+d) * inv2 % mod + mod) % mod;
    int r2 = ((LL)(n5-d) * inv2 % mod + mod) % mod;
    if (int t = BSGS(x, r1)) (~t & 1) && (ans = std::min(ans, t));
    if (int t = BSGS(x, r2)) (~t & 1) && (ans = std::min(ans, t));
  }
  if (int d = sqrt(5LL * n * n - 4)) {
    int r1 = ((LL)(n5+d) * inv2 % mod + mod) % mod;
    int r2 = ((LL)(n5-d) * inv2 % mod + mod) % mod;
    if (int t = BSGS(x, r1)) (t & 1) && (ans = std::min(ans, t));
    if (int t = BSGS(x, r2)) (t & 1) && (ans = std::min(ans, t));
  }
  printf("%d\n", ans == 0x7fffffff ? -1 : ans);
  return 0;
}
