/**************************************************************
 * Problem: JCYZOJ 1037
 * Author: Rqy
 * Date: 2018 Feb 13
 * Algorithm: 
**************************************************************/
#include <cstdio>
void solve(int n, char A, char B, char C) {
  if (!n) return;
  solve(n - 1, A, C, B);
  printf("%d from %c to %c\n", n, A, C);
  solve(n - 1, B, A, C);
}
int main() {
  int n;
  scanf("%d", &n);
  solve(n, 'A', 'B', 'C');
  return 0;
}
