#include <algorithm>
#include <cstdio>
typedef long long LL;
LL n, m, ans;
LL powmod(LL a, LL b) {
  LL ans = 1;
  for (; b; b >>= 1, a = a * a % m)
    if (b & 1) ans = ans * a % m;
  return ans;
}
LL calc1(LL x, LL t) {
  //return (1 + x + ... + x^(t-1)) % m
  if (t == 0) return 0;
  LL ans = (1 + powmod(x, t / 2)) % m * calc1(x, t / 2) % m;
  if (t & 1) ans = (ans * x + 1) % m;
  return ans;
}
LL calc2(LL x, LL t) {
  //return (t + (t - 1)x + (t - 2)x^2 + ... + 1x^(t - 1)) % m
  if (t == 0) return 0;
  LL ans = ((1 + powmod(x, t / 2)) % m * calc2(x, t / 2) % m + 
           (t / 2) % m * calc1(x, t / 2) % m) % m;
  if (t & 1) ans = (ans + calc1(x, t)) % m;
  return ans;
}
void calc(LL l, LL r, int p) {
  //ans = ans : l : (l+1) : ... : r, 10^(p+1) <= l <= r < 10^(p+2)
  //    = ans * 10^(p(r-l+1)) + (l-1)(1+10^p+...+10^(r-l)) +
  //      1*10^(p(r-l)) + 2*10^(p(r-l-1)) + ... + (r-l+1)*10^(p*0)
  LL t = powmod(10, p);
  ans = ans * powmod(t, r - l + 1) % m;
  ans = (ans + (l - 1) % m * calc1(t, r - l + 1) % m) % m;
  ans = (ans + calc2(t, r - l + 1)) % m;
}
  
int main() {
  scanf("%lld%lld", &n, &m);
  ans = 0;
  for (LL p = 1, l = 1; l <= n; ++p, l *= 10)
    calc(l, std::min(l * 10 - 1, n), p);
  printf("%lld\n", ans);
  return 0;
}
