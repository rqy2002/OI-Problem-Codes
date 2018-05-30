#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 30050;
const int LOGN = 17;
int m2[N]; //m2[t] = max(i | 2^i <= t)
struct RMQ{
  int m[LOGN][N];
  void init(int len, const int *A) {
    std::copy(A, A + len, m[0]);
    for (int i = 1; (1 << i) <= len; ++i)
      for (int j = 0; j + (1 << i) <= len; ++j)
        m[i][j] = std::min(m[i - 1][j], m[i - 1][j + (1 << (i - 1))]);
  }
  inline int query(int l, int r) {
    int k = m2[r - l + 1];
    return std::min(m[k][l], m[k][r - (1 << k) + 1]);
  }
};
struct SA{
  static int tmp[2][N], c[N];
  int sa[N], rank[N], height[N];
  RMQ rmq;
  void init(const char *s, int n) {
    memset(tmp, -1, sizeof tmp);
    int *x = tmp[0], *y = tmp[1], i, m = 26;
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
        y[sa[i]] = (sa[i] + k < n && sa[i - 1] + k < n && 
            x[sa[i]] == x[sa[i - 1]] &&
            x[sa[i] + k] == x[sa[i - 1] + k]) ? m - 1 : m++;
    }
    for (i = 0; i < n; ++i) rank[sa[i]] = i;
    for (int i = 0, k = 0; i < n; ++i) {
      if (k) --k;
      if (rank[i]) {
        int j = sa[rank[i] - 1];
        while (s[i + k] == s[j + k]) ++k;
        height[rank[i]] = k;
      }
    }
    rmq.init(n, height);
  }
  inline int getLCP(int i, int j) {
    if (rank[i] > rank[j]) std::swap(i, j);
    return rmq.query(rank[i] + 1, rank[j]);
  }
};
int SA::tmp[2][N], SA::c[N];
SA a, b;
char s[N * 2], rs[N * 2];
int left[N], right[N], n;
inline int LCP(int i, int j) {
  if (i == n || j == n) return 0;
  return a.getLCP(i, j);
}
inline int LCS(int i, int j) {
  return b.getLCP(n - i - 1, n - j - 1);
}
int main() {
  int T;
  for (int i = 0; (1 << i) < N; ++i)
    for (int j = 0; j < (1 << i) && j + (1 << i) < N; ++j)
      m2[j + (1 << i)] = i;
  scanf("%d", &T);
  while (T--) {
    scanf("%s", s);
    n = (int)strlen(s);
    for (int i = 0; i < n; ++i) rs[i] = s[n - i - 1];
    rs[n] = '\0';
    a.init(s, n);
    b.init(rs, n);
    memset(left, 0, sizeof left);
    memset(right, 0, sizeof right);
    for (int L = 1; 2 * L <= n; ++L) {
      for (int i = L; i + L <= n; i += L) {
        int j = i + L;
        int x = LCS(i - 1, j - 1), y = LCP(i, j);
        x = std::min(x, L);
        y = std::min(y, L - 1);
        if (x + y >= L) {
          ++left[i - x]; --left[i + y - L + 1];
          ++right[i - x + 2 * L - 1]; --right[i + y + L];
        }
      }
    }
    for (int i = 1; i < n; ++i) {
      left[i] += left[i - 1];
      right[i] += right[i - 1];
    }
    long long ans = 0;
    for (int i = 1; i < n; ++i)
      ans += (long long)right[i - 1] * left[i];
    printf("%lld\n", ans);
  }
}
