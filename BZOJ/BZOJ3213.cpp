#include <algorithm>
#include <cstdio>
#include <cstring>
typedef long long LL;

struct Int{
  static const int w;
  LL a[3005];
  Int& operator = (LL x) {
    a[0] = 0;
    std::fill(a, a + 305, 0);
    while (x) {
      a[++a[0]] = x % w;
      x /= w;
    }
    return *this;
  }
  Int& operator = (const Int &x) {
    std::copy(x.a, x.a + 305, a);
    return *this;
  }
  Int(int x = 0) { *this = x; }
  Int(const Int &x) { *this = x; }
  void OutPut() const {
    printf("%lld", a[a[0]]);
    for (int i = a[0] - 1; i; --i)
      printf("%08lld", a[i]);
  }
  
  friend Int operator + (const Int &a, const Int &b) {
    Int x;
    x.a[0] = std::max(a.a[0], b.a[0]);
    for (int i = 1; i <= x.a[0]; ++i) {
      x.a[i] += a.a[i] + b.a[i];
      x.a[i + 1] = x.a[i] / w;
      x.a[i] %= w;
    }
    while (x.a[x.a[0] + 1]) ++x.a[0];
    return x;
  }
  
  friend Int operator - (const Int &a, const Int &b) {
    Int x(a);
    for (int i = 1; i <= x.a[0]; ++i)
      if ((x.a[i] -= b.a[i]) < 0) {
        x.a[i] += w;
        --x.a[i + 1];
      }
    while (x.a[0] && !x.a[x.a[0]]) --x.a[0];
    return x;
  }
  
  friend Int operator * (const Int &a, const Int &b) {
    Int x;
    x.a[0] = a.a[0] + b.a[0] - 1;
    for (int i = 1; i <= a.a[0]; ++i)
      for (int j = 1; j <= b.a[0]; ++j) {
        x.a[i + j] += (x.a[i + j - 1] + (LL)a.a[i] * b.a[j]) / w;
        x.a[i + j - 1] = (x.a[i + j - 1] + (LL)a.a[i] * b.a[j]) % w;
      }
    while (x.a[x.a[0] + 1]) ++x.a[0];
    return x;
  }
  
  friend Int operator / (const Int &a, int b) {
    Int x(a);
    int t(0);
    for (int i = x.a[0]; i; --i) {
      int t2 = t;
      t = (x.a[i] + (LL)t * w) % b;
      x.a[i] = (x.a[i] + (LL)t2 * w) / b;
    }
    while (x.a[0] && !x.a[x.a[0]]) --x.a[0];
    return x;
  }
  
  friend int operator % (const Int &a, int b) {
    int t(0);
    for (int i = a.a[0]; i; --i)
      t = (a.a[i] + (LL)t * w) % b;
    return t;
  }
  
};
const int Int::w = 100000000;

struct Frac{
  Int num, den;
  void doit() {
    for (int i = 2; i <= 100; ++i)
      while (!(num % i) && !(den % i)) {
        num = num / i;
        den = den / i;
      }
  }
  
  Frac(const Int &num, const Int &den) : num(num), den(den) {
      doit();
    }
  
  Frac(int num = 0, int den = 1) : num(num), den(den) {
    doit();
  }
  
  friend Frac operator + (const Frac &a, const Frac &b) {
    return Frac(a.num * b.den + b.num * a.den, a.den * b.den);
  }
  
  friend Frac operator - (const Frac &a, const Frac &b) {
    return Frac(a.num * b.den - b.num * a.den, a.den * b.den);
  }
  
  friend Frac operator * (const Frac &a, const Frac &b) {
    return Frac(a.num * b.num, a.den * b.den);
  }
  
  friend Frac operator / (const Frac &a, const Frac &b) {
    return Frac(a.num * b.den, a.den * b.num);
  }
  
  void OutPut() const {
    //printf("%lld/%lld", num, den);
    num.OutPut();
    putchar('/');
    den.OutPut();
    putchar('\n');
  }
} p[2], B[1050];

int s[1050];
int nxt[1050];
int fail[1050][2];
int get() {
  int c;
  do c = getchar(); while (c != 'H' && c != 'T' && c != EOF);
  if (c == EOF) return EOF;
  return c == 'H';
}
int main() {
  int a, b, n = 0;
  scanf("%d%d", &a, &b);
  p[1] = Frac(a, b);
  p[0] = Frac(b - a, b);
  while ((s[n++] = get()) != EOF);
  --n;
  nxt[0] = nxt[1] = 0;
  for (int i = 1; i + 1 < n; ++i) {
    int j = nxt[i];
    while (j && s[j] != s[i]) j = nxt[j];
    nxt[i + 1] = (j + (s[j] == s[i]));
  }
  fail[0][s[0]] = 1;
  fail[0][s[0] ^ 1] = 0;
  fail[1][s[1]] = 2;
  fail[1][s[1] ^ 1] = s[0] != s[1];
  for (int i = 2; i < n; ++i) {
    fail[i][s[i]] = i + 1;
    fail[i][s[i] ^ 1] = fail[nxt[i]][s[i] ^ 1];
  }
  B[0] = Frac(0, 1);
  for (int i = 0; i < n; ++i)
    B[i + 1] = (Frac(1, 1) + B[i] - B[fail[i][s[i] ^ 1]] * p[s[i] ^ 1]) / p[s[i]];
  B[n].OutPut();
  return 0;
}
