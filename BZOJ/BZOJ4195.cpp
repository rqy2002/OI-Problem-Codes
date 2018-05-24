/**************************************************************
 * Problem: BZOJ4195
 * Author: Rqy
 * Date: 2018 Feb 28
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
const int N = 200050;
int a[N], b[N], cnt;
std::map<int, int> M;
int fa[N];
int find(int x) { return fa[x] ? fa[x] = find(fa[x]) : x; }
void merge(int x, int y) { if ((x = find(x)) != (y = find(y))) fa[x] = y; }
int get(int x) { return M.count(x) ? M[x] : M[x] = cnt++; }
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, m = cnt = 0;
    scanf("%d", &n);
    int x, y, e;
    M.clear();
    memset(fa, 0, sizeof fa);
    while (n--) {
      scanf("%d%d%d", &x, &y, &e);
      x = get(x); y = get(y);
      if (e) merge(x, y);
      else { a[m] = x; b[m++] = y; }
    }
    bool ok = true;
    while (m--) ok = ok && find(a[m]) != find(b[m]);
    puts(ok ? "YES" : "NO");
  }
  return 0;
}
