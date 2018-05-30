#include <cstdio>
double M[100050], S[100050];
int main() {
  int n, l = 1000;
  double a;
  scanf("%d%lf", &n, &a);
  for (int i = 1; i <= n; ++i) {
    scanf("%lf", &M[i]);
    int j = (int)(a * i + 1e-6);
    if (i > l)
      printf("%lf\n", M[i] * S[j] / (i - j * 0.5));
    else {
      double ans = 0.0;
      while (j) 
        ans += M[i] * M[j] / (i - j), j--;
      printf("%lf\n", ans);
    }
    S[i] = M[i] + S[i - 1];
  }
  return 0;
}
