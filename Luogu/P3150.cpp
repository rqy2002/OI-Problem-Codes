#include <algorithm>
#include <cstdio>
int main() {
  int n;
  scanf("%d", &n);
  while (n--) {
    int x;
    scanf("%d", &x);
    puts(x & 1 ? "zs wins" : "pb wins");
  }
  return 0;
}
