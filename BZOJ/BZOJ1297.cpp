#include <cstdio>
#include <cstring>
const int N = 15;
const int mod = 2009;
int nn;
struct Matrix{
  int v[N * 9][N * 9];
  Matrix() {
    memset(v, 0, sizeof v);
  }
  friend Matrix operator*(const Matrix &a, const Matrix &b) {
    Matrix ans;
    for (int i = 0; i < nn; ++i) 
      for (int j = 0; j < nn; ++j) if (a.v[i][j])
        for (int k = 0; k < nn; ++k)
          ans.v[i][k] = (ans.v[i][k] + a.v[i][j] * b.v[j][k]) % mod;
    return ans;
  }
  friend Matrix operator+(const Matrix &a, const Matrix &b) {
    Matrix ans;
    for (int i = 0; i < nn; ++i)
      for (int j = 0; j < nn; ++j)
        ans.v[i][j] = (a.v[i][j] + b.v[i][j]) % mod;
    return ans;
  }
};
Matrix D;
Matrix ans;
int main() {
  int n, t;
  scanf("%d%d", &n, &t);
  nn = n * 9;
  int x;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) {
      scanf("%1d", &x);
      if (x) D.v[i][(x - 1) * n + j] = 1;
    }
  for (int i = 0; i < 8 * n; ++i)
    D.v[i + n][i] = 1;
  for (int i = 0; i < n; ++i)
    ans.v[i][i] = 1;
  for (; t; D = D * D, t >>= 1)
    if (t & 1) ans = ans * D;
  printf("%d\n", ans.v[0][n - 1]);
  return 0;
}
