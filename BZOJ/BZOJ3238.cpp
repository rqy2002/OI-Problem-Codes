/**************************************************************
 * Problem: BZOJ3238
 * Author: Rqy
 * Date: 2018 Feb 27
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 1500050;
typedef long long LL;
int n;
char s[N];
int sa[N], tmp[2][N], c[N], h[N], rank[N];
int stack[N], left[N], right[N];
int main() {
  scanf("%s", s);
  n = strlen(s);
  memset(tmp, -1, sizeof tmp);
  int i, m = 26, *x = tmp[0], *y = tmp[1];
  for (i = 0; i < m; ++i) c[i] = 0;
  for (i = 0; i < n; ++i) ++c[x[i] = s[i] - 'a'];
  for (i = 1; i < m; ++i) c[i] += c[i - 1];
  for (i = n - 1; ~i; --i) sa[--c[x[i]]] = i;
  for (int k = 1; k == 1 || m < n; k <<= 1, std::swap(x, y)) {
    int j = 0;
    for (i = n - k; i < n; ++i) y[j++] = i;
    for (i = 0; i < n; ++i) if (sa[i] >= k) y[j++] = sa[i] - k;

    for (i = 0; i < m; ++i) c[i] = 0;
    for (i = 0; i < n; ++i) ++c[x[y[i]]];
    for (i = 1; i < m; ++i) c[i] += c[i - 1];
    for (i = n - 1; ~i; --i) sa[--c[x[y[i]]]] = y[i];

    m = 0;
    y[sa[0]] = m++;
    for (i = 1; i < n; ++i)
      y[sa[i]] = (x[sa[i]] == x[sa[i - 1]] &&
          x[sa[i] + k] == x[sa[i - 1] + k]) ? m - 1 : m++;
  }
  std::copy(x, x + n, rank);
  for (int k = i = 0; i < n; ++i) {
    if (k) --k;
    if (rank[i]) {
      int j = sa[rank[i] - 1];
      while (s[j + k] == s[i + k]) ++k;
      h[rank[i]] = k;
    }
  }
  LL ans = (LL)(n - 1) * n * (n + 1) / 2;
  int top = 1;
  stack[0] = 0;
  for (int i = 1; i < n; ++i) {
    while (top && h[stack[top - 1]] > h[i]) --top;
    left[i] = stack[top - 1];
    stack[top++] = i;
  }
  top = 1;
  stack[0] = n;
  for (int i = n - 1; i; --i) {
    while (top && h[stack[top - 1]] >= h[i]) --top;
    right[i] = stack[top - 1];
    stack[top++] = i;
  }
  for (int i = 1; i < n; ++i)
    ans -= 2LL * h[i] * (i - left[i]) * (right[i] - i);
  printf("%lld\n", ans);
  return 0;
}
