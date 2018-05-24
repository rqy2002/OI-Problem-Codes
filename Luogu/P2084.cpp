#include <algorithm>
#include <cstdio>
#include <cstring>
int m;
char n[1005];
int main() {
  scanf("%d%s", &m, n);
  int l = strlen(n);
  bool fst = true;
  for (int i = 0; i < l; ++i) if (n[i] != '0') {
    if (fst) fst = false;
    else printf("+");
    printf("%c*%d^%d", n[i], m, l - i - 1);
  }
  if (fst) printf("0");
  return 0;
}
