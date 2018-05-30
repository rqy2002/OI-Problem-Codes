#include <algorithm>
#include <cstdio>
typedef long long LL;

const int modv = 19940417;
const int mod[2] = {7, 2848631};

int fac[2][3000000];
int inv[2][3000000];

int getNum(int a, int b) {
  return ((LL)a * 11394524 + (LL)b * 8545894) % modv;
}

inline int C(int k, int n, int m) {
  if (n < m) return 0;
  return (LL)fac[k][n] * inv[k][m] % mod[k] * inv[k][n - m] % mod[k];
}

int Lucas(int k, LL m, LL n) {
  if (n < m) return 0;
  int ans = 1;
  while (m) {
    if (!(ans = (LL)ans * C(k, n % mod[k], m % mod[k]) % mod[k])) break;
    n /= mod[k];
    m /= mod[k];
  }
  return ans;
}

inline LL read() {
  LL ans = 0, f = 1;
  int c;
  do c = getchar(); while ((c > '9' || c < '0') && c != '-');
  if (c == '-') {
    f = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    ans = ans * 10 + c - '0';
    c = getchar();
  }
  return ans;
}

struct Point{
  int x;
  LL fx;
  Point(int x = 0, LL fx = 0LL) : x(x), fx(fx) {}
  inline bool operator < (const Point &p) const {
    return x < p.x;
  }
};

Point p[1000005];

int main() {
  int i, k;
  for (k = 0; k < 2; ++k) {
    fac[k][0] = 1;
    for (i = 1; i < mod[k]; ++i)
      fac[k][i] = (LL)fac[k][i - 1] * i % mod[k];
    inv[k][mod[k] - 1] = mod[k] - 1;
    for (i = mod[k] - 1; i; --i)
      inv[k][i - 1] = (LL)inv[k][i] * i % mod[k];
  }
  int n;
  n = read();
  k = read();
  for (int i = 0; i < k; ++i) {
    p[i].x = read();
    p[i].fx = read();
  }
  p[k++] = Point(0, 0);
  p[k++] = Point(n, 0);
  std::sort(p, p + k);
  int ans1[2] = {1, 1};
  LL ans2 = 0;
  for (int i = 1; i < k; ++i) if (p[i].x != p[i - 1].x) {
    int c = p[i].x - p[i - 1].x;
    LL y1 = p[i - 1].fx, y2 = p[i].fx;
    ans2 = std::max(ans2, (c + y1 + y2) / 2);
    if (y1 > y2) std::swap(y1, y2);
    int X = (c + y2 - y1) / 2, Y = (c - y2 + y1) / 2, Z = y1;
    ans1[0] = (LL)ans1[0] * ((Lucas(0, X, X + Y) - Lucas(0, X + Z + 1, X + Y) + mod[0]) % mod[0]) % mod[0];
    ans1[1] = (LL)ans1[1] * ((Lucas(1, X, X + Y) - Lucas(1, X + Z + 1, X + Y) + mod[1]) % mod[1]) % mod[1];
  }
  printf("%d %lld\n", getNum(ans1[0], ans1[1]), ans2);
  return 0;
}
