#include <cstdio>
typedef long long LL;
const int mod = 1000000007;
struct Matrix{
  int v[2][2];
  Matrix() {
    v[0][0] = v[0][1] = v[1][0] = v[1][1] = 0;
  }
  friend Matrix operator*(const Matrix &a, const Matrix &b) {
    Matrix c;
    for (int i = 0; i < 2; ++i)
      for (int k = 0; k < 2; ++k)
        for (int j = 0; j < 2; ++j)
          c.v[i][j] = ((LL)a.v[i][k] * b.v[k][j] + c.v[i][j]) % mod;
    return c;
  }
  friend Matrix operator+(const Matrix &a, const Matrix &b) {
    Matrix c;
    for (int i = 0; i < 2; ++i)
      for (int j = 0; j < 2; ++j)
        c.v[i][j] = (a.v[i][j] + b.v[i][j]) % mod;
    return c;
  }
};
Matrix pow_mod(Matrix a, int b) {
  Matrix c;
  c.v[0][0] = c.v[1][1] = 1;
  for (; b; a = a * a, b >>= 1)
    if (b & 1) c = c * a;
  return c;
}
Matrix f[2000];
int t[2000];
Matrix F[2000];
int main() {
  int n, i;
  scanf("%d", &n);
  for (i = 1; i <= n; ++i)
    scanf("%1d", &t[i]); 
  F[0].v[0][0] = F[0].v[0][1] = F[0].v[1][0] = 1;
  for (i = 1; i <= n; ++i) F[i] = pow_mod(F[i - 1], 10);
  f[0].v[0][0] = 1;
  f[0].v[0][1] = f[0].v[1][0] = -1;
  f[0].v[1][1] = 2;
  for (i = 1; i <= n; ++i) {
    Matrix k;
    k.v[0][0] = k.v[1][1] = 1;
    for (int j = i; j; --j) {
      k = k * pow_mod(F[i - j], t[j]);
      f[i] = f[i] + k * f[j - 1];
    }
  }
  printf("%d\n", (f[n].v[0][0] + mod) % mod);
  return 0;
}
