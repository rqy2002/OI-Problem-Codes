/**************************************************************
 * Problem: BZOJ4819
 * Author: Rqy
 * Date: 2018 Feb 24
 * Algorithm: 
**************************************************************/
#include<cstdio>
#include<cctype>
#include<algorithm>
#include<cmath>
using std::max;
using std::min;
const int INF = 998244353;
const int N = 105;
const double eps = 1e-7;
double w[N][N], n;
double lx[N], ly[N];
int link[N];
int visx[N], visy[N], dfsnum;
double slack[N];
bool dfs(int x) {
  visx[x] = dfsnum;
  for (int y = 0; y <= n; ++y) if (visy[y] < dfsnum) {
    double t = lx[x] + ly[y] - w[x][y];
    if (fabs(t) < eps) {
      visy[y] = dfsnum;
      if (link[y] < 0 || dfs(link[y])) {
        link[y] = x;
        return true;
      }
    } else if (slack[y] > t)
      slack[y] = t;
  }
  return false;
}
double solve() {
  for (int i = 0; i < n; ++i) {
    lx[i] = -(double)INF;
    ly[i] = 0.0;
    link[i] = -1;
    visx[i] = visy[i] = 0;
    for (int j = 0; j < n; ++j)
      lx[i] = max(lx[i], w[i][j]);
  }
  dfsnum = 0;
  for (int x = 0; x < n; ++x) {
    for (int i = 0; i < n; ++i)
      slack[i] = (double)INF;
    while (1) {
      ++dfsnum;
      if (dfs(x)) break;
      double d = (double)INF;
      for (int i = 0; i < n; ++i)
        if (visy[i] < dfsnum)
          d = min(d, slack[i]);
      if (fabs(d - INF) < eps) return -INF;
      for (int i = 0; i < n; ++i)
        if (visx[i] == dfsnum)
          lx[i] -= d;
      for (int i = 0; i < n; ++i)
        if (visy[i] == dfsnum)
          ly[i] += d;
        else
          slack[i] -= d;
    }
  }
  double ans = 0;
  for (int i = 0; i < n; ++i)
    ans += w[link[i]][i];
  return ans;
}
inline int readInt() {
  int ans = 0, c;
  while (!isdigit(c = getchar()));
  do ans = ans * 10 + c - '0';
  while (isdigit(c = getchar()));
  return ans;
}
int a[N][N], b[N][N];
int main() {
  n = readInt();
  double l = 100000000.0, r = 0.0;
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < n; ++j)
      a[i][j] = readInt();
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < n; ++j) {
      b[i][j] = readInt();
      l = min(l, (double)a[i][j] / b[i][j] - eps);
      r = max(r, (double)a[i][j] / b[i][j] + eps);
    }
  for (int _k = 0; _k < 50 && r - l > eps; ++_k) {
    double mid = (l + r) / 2;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        w[i][j] = a[i][j] - b[i][j] * mid;
    if (solve() > -eps) l = mid;
    else r = mid; 
  }
  printf("%.6lf\n", l);
  return 0;
}
