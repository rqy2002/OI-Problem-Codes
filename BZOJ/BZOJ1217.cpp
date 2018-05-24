/**************************************************************
 * Problem: BZOJ1217
 * Author: Rqy
 * Date: 2018 Feb 25
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <vector>
const int N = 1050;
int a[N], dep[N], p[N];
std::vector<int> to[N];
int mark[N];
inline bool cmp(int a, int b) { return dep[a] > dep[b]; }
int main() {
  int n;
  scanf("%d", &n);
  int ans = 0;
  for (int i = 2; i <= n; ++i) {
    scanf("%d", &a[p[i] = i]);
    dep[i] = dep[a[i]] + 1;
    to[a[i]].push_back(i);
  }
  a[1] = p[1] = 1;
  std::sort(p + 1, p + n + 1, cmp);
  for (int o = 1; o <= n; ++o) {
    int i = p[o];
    if (mark[i]) continue;
    i = a[a[i]];
    ++ans;
    mark[a[a[i]]] = mark[a[i]] = true;
    for (int j = 0; j < to[a[i]].size(); ++j) mark[to[a[i]][j]] = true;
    for (int j = 0; j < to[i].size(); ++j) {
      int t = to[i][j];
      mark[t] = true;
      for (int b = 0; b < to[t].size(); ++b)
        mark[to[t][b]] = true;
    }
  }
  printf("%d\n", ans);
  return 0;
}
