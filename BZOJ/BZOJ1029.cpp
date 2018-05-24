/**************************************************************
 * Problem: BZOJ1029
 * Author: Rqy
 * Date: 2018 Feb 25
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <queue>
const int N = 150050;
std::priority_queue<int> Q;
struct P{ int a, b; }p[N];
bool operator<(const P &x, const P &y) { return x.b < y.b; }
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d%d", &p[i].a, &p[i].b);
  std::sort(p, p + n);
  for (int i = 0, t = 0; i < n; ++i)
    if (t + p[i].a < p[i].b) Q.push(p[i].a), t += p[i].a;
    else if (p[i].a < Q.top()) t += p[i].a - Q.top(), Q.pop(), Q.push(p[i].a);
  printf("%d\n", Q.size());
  return 0;
}
