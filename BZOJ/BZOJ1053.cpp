#include <cstdio>
typedef long long LL;
int n;
int ans;
int divnum;
const int prime[20] = {
  2, 3, 5, 7, 11,
  13, 17, 19, 23, 29,
  31, 37, 41, 43, 47,
  53, 59, 61, 67, 71
};
void dfs(int x, int y, int la, int d) {
  if (d > divnum || d == divnum && ans > y) {
    ans = y;
    divnum = d;
  }
  if (x >= 20) return;
  for (int i = 0, j = 1; i <= la && n / j >= y; ++i, j *= prime[x])
    dfs(x + 1, y * j, i, d * (i + 1));
}
int main() {
  scanf("%d", &n);
  divnum = 0;
  dfs(0, 1, 10000, 1);
  printf("%d\n", ans);
  return 0;
}
