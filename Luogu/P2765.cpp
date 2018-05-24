/**************************************************************
 * Problem: Luogu P2765
 * Author: Rqy
 * Date: 2017 Dec 22
 * Algorithm: 公式
**************************************************************/
#include <cstdio>
int n, n1, ans, i, j, s, t;
inline int sqr(int x) { return x * x; }
const int L = 9050;
char ss[L], *l = ss;
void put(int x, char c) {
  static int p[20];
  int top = 0;
  while (x) {
    p[top++] = x % 10;
    x /= 10;
  }
  while (top--) *(l++) = char(p[top] + '0');
  *(l++) = c;
}
int main() {
  scanf("%d", &n);
  n1 = (n + 1) / 2;
  if (n & 1)
    ans = 2 * n1 * n1;
  else
    ans = 2 * n1 * (n1 + 1);
  put(ans - 1, '\n');
  for (i = 1; i <= n; ++i) {
    s = i / 2;
    if (i & 1) {
      if (i != 1) put(2 * s * (s + 1), ' ');
      for (j = 0, t = -1; j <= n - i; ++j, t *= -1)
        put(2 * sqr(s + j / 2 + 1) + t * (2 * s + j / 2 + 1), ' ');
    } else {
      put(2 * s * s, ' ');
      for (j = 0, t = -1; j < n - i; ++j, t *= -1)
        put(2 * sqr(s + j / 2 + 1) + t * (j / 2 + 1), ' ');
    }
    *(l++) = '\n';
  }
  *l = '\0';
  puts(ss);
  printf("%d\n", l - ss);
  return 0;
}
