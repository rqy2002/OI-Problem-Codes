#include <cstdio>
int len, ans[5050];
void mul(int x) {
  int i, c;
  for (i = 0, c = 0; i < len || c; ++i) {
    c = (ans[i] = ans[i] * x + c) / 10;
    ans[i] %= 10;
  }
  len = i;
}
const int e[] = {0, 0, 0, 0, 4, 6, 9, 12, 18, 27};
int main() {
  int n;
  scanf("%d", &n);
  len = 1, ans[0] = 1;
  while (n >= 10) {
    mul(9);
    n -= 6;
  }
  mul(e[n]);
  printf("%d\n", len);
  for (int i = len - 1; ~i && i >= len - 100; --i)
    printf("%d", ans[i]);
  return 0;
}
