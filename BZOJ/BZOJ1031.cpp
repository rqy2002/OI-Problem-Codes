#include <algorithm>
#include <cstdio>
const int N = 400050;
char s[N];
int sa[N];
int c[N], tmp[2][N];
int main() {
  scanf("%s", s);
  int n, m = 128, i, j;
  int *x = tmp[0], *y = tmp[1];
  for (i = 0; i < m; ++i) c[i] = 0;
  for (n = 0; s[n]; ++n) ++c[x[n] = s[n]];
  for (i = 0; i < n; ++i) ++c[x[n + i] = s[n + i] = s[i]];
  n *= 2;
  for (i = 1; i < m; ++i) c[i] += c[i - 1];
  for (i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;
  for (int k = 1; k < n; k <<= 1) {
    j = 0;
    for (i = n - k; i < n; ++i) y[j++] = i;
    for (i = 0; i < n; ++i) if (sa[i] >= k) y[j++] = sa[i] - k;
    for (i = 0; i < m; ++i) c[i] = 0;
    for (i = 0; i < n; ++i) ++c[x[y[i]]];
    for (i = 1; i < m; ++i) c[i] += c[i - 1];
    for (i = n - 1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
    std::swap(x, y);
    j = 0;
    x[sa[0]] = j++;
    for (i = 1; i < n; ++i)
      x[sa[i]] = y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k] ? j - 1 : j++;
    if ((m = j) == n) break;
  }
  for (int i = 0; i < n; ++i)
    if (sa[i] < n / 2)
      putchar(s[(sa[i] + n / 2 - 1) % (n / 2)]);
  return 0;
}
