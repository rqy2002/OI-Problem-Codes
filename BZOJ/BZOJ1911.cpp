/**************************************************************
 * Problem: BZOJ1911
 * Author: Rqy
 * Date: 2018 Feb 25
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
typedef long long LL;
const int N = 1000050;
LL a, b, c;
LL f[N], x[N], y[N];
LL get(int i, int j) {
  LL s = x[j] - x[i];
  return f[i] + (a * s + b) * s + c;
}
bool check(int i, int j, int k) {
  LL x1 = x[j] - x[i], y1 = y[j] - y[i];
  LL x2 = x[k] - x[i], y2 = y[k] - y[i];
  // return y2 / x2 > y1 / x1
  return y2 * x1 > y1 * x2;
}
int que[N], hd, tl;
int main() {
  int n;
  scanf("%d%lld%lld%lld", &n, &a, &b, &c);
  f[0] = 0; x[0] = 0; y[0] = 0;
  tl++;
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &x[i]); x[i] += x[i - 1];
    while (hd < tl - 1 && get(que[hd], i) < get(que[hd + 1], i)) ++hd;
    f[i] = get(que[hd], i);
    y[i] = f[i] + (a * x[i] - b) * x[i];
    while (hd < tl - 1 && check(que[tl - 2], que[tl - 1], i)) --tl;
    que[tl++] = i;
  }
  printf("%lld\n", f[n]);
  return 0;
}
