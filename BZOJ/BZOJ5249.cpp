#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>

inline int readInt() {
  int ans = 0, c;
  while (!isdigit(c = getchar()));
  do ans = ans * 10 + c - '0';
  while (isdigit(c = getchar()));
  return ans;
}

const int N = 530000;
const int L = N * 20;

char s[L], *p = s;

void print(int x) {
  if (x == 0) return;
  print(x / 10);
  *(p++) = x % 10 + '0';
}

int n, m, A[N], B[N], C[N];
int siz[N], val[N];
double k;

inline int fa(int x) { return (int)(floor(x / k + 1e-5)); }

int len;
int sumv[N * 4], minv[N * 4];

inline void upd(int o) {
  sumv[o] = sumv[o << 1] + sumv[o << 1 | 1];
  minv[o] = std::min(minv[o << 1 | 1], minv[o << 1] + sumv[o << 1 | 1]);
}

void build() {
  for (int i = 0; i < len; ++i) minv[i + len] = sumv[i + len] = B[i + 1];
  for (int i = len - 1; i > 0; --i) upd(i);
}

void add(int x, int y) {
  int t = B[x] -= y;
  x += len - 1;
  sumv[x] = minv[x] = t;
  for (x >>= 1; x > 0; x >>= 1) upd(x);
}

inline bool check() { return minv[1] >= 0; }
inline bool check(int x, int y) {
  add(y, siz[x]);
  bool ans = check();
  add(y, -siz[x]);
  return ans;
}

int main() {
  n = readInt();
  scanf("%lf", &k);
  for (int i = 0; i < n; ++i) A[i] = readInt();
  std::sort(A, A + n);

  for (int i = 0; i < n; ++i) {
    ++B[(i != 0 && A[i] == A[i - 1]) ? m : ++m];
    C[m] = A[i];
  }

  len = 1;
  while (len < m) len <<= 1;
  build();
  for (int i = n; i > 0; --i)
    siz[fa(i)] += ++siz[i];
  add(val[0] = 1, n);
  for (int i = 1; i <= n; ++i) {
    int s = siz[i];
    add(val[fa(i)], -s);
    int l = val[fa(i)], r = m;
    while (l < r) {
      int mid = (l + r + 1) >> 1;
      if (check(i, mid)) l = mid;
      else r = mid - 1;
    }
    add(val[i] = l, s);
  }
  for (int i = 1; i <= n; ++i) {
    print(C[val[i]]);
    *(p++) = ' ';
  }
  *(p++) = '\0';
  puts(s);
  return 0;
}
