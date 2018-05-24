#include <cstdio>
#include <cstring>
char a[30];
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%s", a);
    int b = 0, l = strlen(a);
    for (int i = 0; i < l; ++i)
      b = b * 9 + a[i]  - '0' - (a[i] > '7');
    printf("%d\n", b);
  }
  return 0;
}
