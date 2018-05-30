#include <algorithm>
#include <cstdio>
#include <cstring>
typedef long long LL;
const int N = 300050;
int sa[N], c[N], tmp[2][N * 2], rank[N], height[N];
struct Info{
  int max1, max2, min1, min2;
  int maxn, minn;
  Info(int x = 0) {
    max1 = min1 = max2 = min2 = 0;
    maxn = minn = 0;
    (x < 0 ? min1 : max1) = x;
    (x < 0 ? minn : maxn) = 1;
  }
  inline void merge(const Info &t) {
    int a[4] = {max1, max2, t.max1, t.max2};
    std::nth_element(a, a + 2, a + 4);
    max1 = a[3]; max2 = a[2];
    maxn += t.maxn;
    int b[4] = {min1, min2, t.min1, t.min2};
    std::nth_element(b, b + 1, b + 4);
    min1 = b[0]; min2 = b[1];
    minn += t.minn;
  }
  inline LL get() {
    LL ans = -1000000000000000000LL;
    if (maxn >= 2) ans = std::max(ans, (LL)max1 * max2);
    if (minn >= 2) ans = std::max(ans, (LL)min1 * min2);
    if (maxn + minn >= 2) ans = std::max(ans, (LL)max1 * min1);
    return ans;
  }
}f[N];
int fa[N], siz[N];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
char s[N];
int P[N];
bool cmp(int a, int b) {
  return height[a] > height[b];
}
LL ans1[N], ans2[N];
int main() {
  int n, t, i;
  scanf("%d%s", &n, s);
  memset(tmp, -1, sizeof tmp);
  int m = 26, *x = tmp[0], *y = tmp[1];
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
      height[rank[i]] = k;
    }
  }
  for (i = 0; i < n; ++i) {
    scanf("%d", &t);
    f[rank[i]] = Info(t);
    P[i] = fa[i] = i;
    siz[i] = 1;
  }
  std::sort(P + 1, P + n, cmp);
  std::fill(ans1, ans1 + n + 1, 0);
  std::fill(ans2, ans2 + n + 1, -1000000000000000000LL);
  for (int i = 1; i < n; ++i) {
    int j = P[i], k = height[j];
    int v = find(j - 1);
    ans1[k] += (LL)siz[v] * siz[j];
    f[v].merge(f[j]);
    siz[v] += siz[j];
    fa[j] = v;
    ans2[k] = std::max(ans2[k], f[v].get());
  }
  for (int i = n - 1; ~i; --i) {
    ans1[i] += ans1[i + 1];
    ans2[i] = std::max(ans2[i], ans2[i + 1]);
  }
  for (int i = 0; i < n; ++i)
    printf("%lld %lld\n", ans1[i], ans1[i] ? ans2[i] : 0);
  return 0;
}
