/**************************************************************
 * Problem: JCYZOJ 1042
 * Author: Rqy
 * Date: 2018 Feb 13
 * Algorithm: BigNum, Sort
**************************************************************/
#include <algorithm>
#include <cstdio>
const int N = 1050;
struct P{
  int a, b;
  bool operator<(const P &x) const {
    return a * b < x.a * x.b;
  }
}p0, p[N];
struct BigNum{
  int v[N * 10], len;
  BigNum operator*=(int x) {
    for (int i = 0, t = 0; i < len || t; ++i) {
      t = (v[i] = v[i] * x + t) / 10;
      v[i] %= 10;
      len = std::max(len, i + 1);
    }
    return *this;
  }
  BigNum operator/=(int x) {
    for (int i = len - 1, t = 0; ~i; --i) {
      t = (v[i] += t * 10) % x;
      v[i] /= x;
    }
    while (len && !v[len - 1]) --len;
    return *this;
  }
  bool operator<(const BigNum &x) const {
    if (len != x.len) return len < x.len;
    for (int i = len - 1; ~i; --i)
      if (v[i] != x.v[i])
        return v[i] < x.v[i];
    return false;
  }
}A, B, ans;
int main() {
  int n;
  scanf("%d%d%d", &n, &p0.a, &p0.b);
  for (int i = 0; i < n; ++i)
    scanf("%d%d", &p[i].a, &p[i].b);
  std::sort(p, p + n);
  A.len = A.v[0] = 1;
  A *= p0.a;
  for (int i = 0; i < n; ++i) {
    (B = A) /= p[i].b;
    if (!i || ans < B) ans = B;
    A *= p[i].a;
  }
  for (int i = ans.len - 1; ~i; --i)
    printf("%d", ans.v[i]);
  return 0;
}

