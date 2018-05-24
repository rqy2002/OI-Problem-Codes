/**************************************************************
 * Problem: Luogu P1822
 * Author: Rqy
 * Date: 2017 Dec 23
 * Algorithm: DFS, BFS
**************************************************************/
#include <algorithm>
#include <cstdio>
typedef long long LL;
bool mm[10000050];
int p[10], A, B;
int queue[40000], num, head, tail;
void dfs(int x, LL y, int p10) {
  if (y > B) return;
  if (x == 0) {
    int last = y / (p10 / 10);
    if (!last) return;
    dfs(x, y + (LL)last * p10, p10 * 10);
    if (y >= A && y <= B) ++num;
    if (p10 < B) queue[tail++] = y;
    return;
  }
  int last = y / (p10 / 10), nxt = x % 10;
  x /= 10;
  if (last - nxt >= 0) dfs(x, y + p10 * (last - nxt), p10 * 10);
  if (nxt && last + nxt < 10) dfs(x, y + p10 * (last + nxt), p10 * 10);
}
int main() {
  scanf("%d%d", &A, &B);
  head = tail = num = 0;
  queue[tail++] = 7;
  if (A <= 7 && B >= 7) ++num;
  do
    for (int i = 0; i < 10; ++i)
      dfs(queue[head], i, 10);
  while (++head < tail);
  printf("%d\n", num);
  return 0;
}
