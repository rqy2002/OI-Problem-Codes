#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 105;
int A[N], B[N], C[N];
char s[105];
void div2() {
  for (int i = A[0]; i; --i) {
    if (i && (A[i] & 1)) A[i - 1] += 10;
    A[i] >>= 1;
  }
  while (A[0] && !A[A[0]]) --A[0];
}
void add(int *a, int *b) {
  int t = 0;
  for (int i = 1; i <= b[0] || t; ++i) {
    t = (a[i] += b[i] + t) / 10;
    a[i] %= 10;
  }
  a[0] = std::max(a[0], b[0]);
  while (a[a[0] + 1]) ++a[0];
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%s", s);
    if (!strcmp(s, "0")) {
      puts("0");
      continue;
    }
    A[0] = strlen(s);
    for (int i = 0; i < A[0]; ++i)
      A[A[0] - i] = s[i] - '0';
    memset(B, 0, sizeof B);
    memset(C, 0, sizeof C);
    B[0] = B[1] = 1;
    while (A[0]) {
      if (A[1] & 1) add(C, B);
      else add(B, C);
      div2();
    }
    for (int i = C[0]; i; --i)
      putchar(C[i] + '0');
    putchar('\n');
  }
  return 0;
}
