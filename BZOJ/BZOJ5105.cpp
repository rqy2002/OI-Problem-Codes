/**************************************************************
 * Problem: BZOJ5105
 * Author: Rqy
 * Date: 2018 Feb 27
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
typedef long long LL;
LL gcd(LL a, LL b) { while (b) std::swap(b, a %= b); return a; }
inline LL lcm(LL a, LL b) { return a / gcd(a, b) * b; }
int main() {
  int a, b, c; scanf("%d%d%d", &a, &b, &c); printf("%lld\n", lcm(lcm(a, b), c));
}
