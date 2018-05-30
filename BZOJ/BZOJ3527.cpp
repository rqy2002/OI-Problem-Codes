#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>
typedef std::complex<double> Complex;
const double pi = acos(-1.0);
const int N = 400000;
double E[N], Q[N];
Complex A[N], B[N];
void FFT(Complex *P, int len, int opt) {
  for (int i = 1, j = len >> 1; i < len; ++i) {
    if (i < j) std::swap(P[i], P[j]);
    int k = len;
    do {
      k >>= 1;
      j ^= k;
    } while (~j & k);
  }
  for (int h = 2; h <= len; h <<= 1) {
    Complex wn(cos(2 * pi * opt / h), sin(2 * pi * opt / h));
    for (int j = 0; j < len; j += h) {
      Complex w(1.0, 0.0);
      for (int k = 0; k < h / 2; ++k) {
        Complex t1 = P[j + k] , t2 = P[j + k + h / 2] * w;
        P[j + k] = t1 + t2;
        P[j + k + h / 2] = t1 - t2;
        w *= wn;
      }
    }
  }
  if (opt == -1) {
    for (int i = 0; i < len; ++i)
      P[i] /= len;
  }
}
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%lf", &Q[i]);
  int len = 1;
  while (len < 2 * n) len <<= 1;
  for (int i = 0; i < n; ++i) A[i] = Q[i];
  for (int i = n; i < len; ++i) A[i] = 0.0;
  B[0] = 0.0;
  for (int i = 1; i < n; ++i) B[i] = 1.0 / i / i;
  for (int i = n; i < len; ++i) B[i] = 0.0;
  FFT(A, len, 1);
  FFT(B, len, 1);
  for (int i = 0; i < len; ++i) A[i] *= B[i];
  FFT(A, len, -1);
  for (int i = 0; i < n; ++i) E[i] += A[i].real();
  for (int i = 0; i < n; ++i) A[i] = Q[n - i - 1];
  for (int i = n; i < len; ++i) A[i] = 0.0;
  B[0] = 0.0;
  for (int i = 1; i < n; ++i) B[i] = 1.0 / i / i;
  for (int i = n; i < len; ++i) B[i] = 0.0;
  FFT(A, len, 1);
  FFT(B, len, 1);
  for (int i = 0; i < len; ++i) A[i] *= B[i];
  FFT(A, len, -1);
  for (int i = 0; i < n; ++i) E[n - i - 1] -= A[i].real();
  for (int i = 0; i < n; ++i) printf("%.10lf\n", E[i]);
  return 0;
}
