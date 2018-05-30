#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#define reg register
typedef long long LL;

struct Int{
  static const int w = 10000;
  int a[30];
  Int() {}
  Int& operator=(const Int &x) {
    memcpy(a, x.a, sizeof a);
    return *this;
  }
  Int(int x) {
    memset(a, 0, sizeof a);
    a[0] = x;
  }
  Int& operator*=(int x) {
    for (reg int i = 0, t = 0; i < 30; ++i) {
      t = (a[i] = a[i] * x + t) / w;
      a[i] %= w;
    }
    return *this;
  }
  Int& operator+=(int x) {
    for (reg int i = 0; i < 30 && x; ++i) {
      x = (a[i] += x) / w;
      a[i] %= w;
    }
    return *this;
  }
  Int operator*(int x) {
    Int tmp(*this);
    tmp *= x;
    return tmp;
  }
  bool operator<(const Int &y)const{
    for (reg int i = 29; ~i; --i)
      if (a[i] != y.a[i]) return a[i] < y.a[i];
    return 0;
  }
  bool operator==(const Int &y)const{
    for (reg int i = 29; ~i; --i)
      if (a[i] != y.a[i]) return 0;
    return 1;
  }
  bool operator<=(const Int &y)const{
    return !(y < *this);
  }
};
Int n;
Int ans;
LL divnum;
const int prime[] = {
  2, 3, 5, 7, 11,
  13, 17, 19, 23, 29,
  31, 37, 41, 43, 47,
  53, 59, 61, 67, 71,
  73, 79, 83, 89, 97,
  101, 103, 107, 109, 113,
  127, 131, 137, 139, 149,
  151, 157, 163, 167, 173,
  179, 181, 191, 193, 197,
  199, 211, 223, 227, 229,
  233, 239, 241, 251, 257
};
const int K[] = {
  2, 2, 3, 3, 4,
  4, 5, 5, 5, 5,
  5, 6, 6, 6, 6,
  6, 6, 6, 7, 7,
  7, 7, 7, 7, 7,
  7, 7, 7, 7, 7,
  7, 8, 8, 8, 8,
  8, 8, 8, 8, 8,
  8, 8, 8, 8, 8,
  8, 8, 8, 8, 8,
  8, 8, 8, 8, 8,
};
int t[55];
int q[55];
int m;
void dfs(int x, Int y, LL d) {
  if (d > divnum || (d == divnum && y < ans)) {
    ans = y;
    divnum = d;
  }
  if (x >= 55) return;
  int Max = 2 * (t[x] - 1);
  if (x) Max = std::min(Max, std::min(q[x - 1], (q[0] + 1) / (K[x] - 1)));
  y *= prime[x];
  for (q[x] = 1; q[x] <= Max && y <= n; ++q[x], y *= prime[x])
    dfs(x + 1, y, d * (q[x] + 1));
}
void readInt(Int &x) {
  x = 0;
  int c;
  while (!isdigit(c = getchar()));
  do (x *= 10) += c - '0';
  while (isdigit(c = getchar()));
}
void putInt(const Int &x) {
  int t = 30;
  while (!x.a[--t]);
  printf("%d", x.a[t]);
  while (t--) printf("%04d", x.a[t]);
}
int main() {
  readInt(n);
  divnum = 0;
  Int c(1);
  for (m = 0; c <= n; ++m)
    c *= prime[m];
  for (int i = 0; i < m; ++i) {
    t[i] = 0;
    for (int j = 1; j <= prime[m]; j *= prime[i], ++t[i]);
  }
  dfs(0, 1, 1);
  putInt(ans);
  return 0;
}
