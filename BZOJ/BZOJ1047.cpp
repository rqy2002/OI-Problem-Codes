#include <algorithm>
#include <cstdio>
#include <deque>
using std::deque;
const int N = 1050;
int A[N][N];
int _ans[2][N][N];
int a, b, n;
struct MQ{
  int v[N];
  deque<int> DQ;
  int ttop, end;
  void clear() {
    DQ.clear();
    ttop = end = 0;
  }
  void push(int x) {
    v[end] = x;
    while (!DQ.empty() && x < v[DQ.back()]) DQ.pop_back();
    DQ.push_back(end++);
  }
  int top() {
    return v[DQ.front()];
  }
  void pop() {
    if (DQ.front() == ttop++)
      DQ.pop_front();
  }
};
MQ C[N], R;
void solve(int x) {
  int (*ans)[N] = _ans[x];
  for (int i = 0; i < b; ++i) {
    C[i].clear();
    for (int j = 0; j < n; ++j)
      C[i].push(A[j][i]);
  }
  for (int i = 0; i + n - 1 < a; ++i) {
    R.clear();
    for (int j = 0; j < n; ++j) R.push(C[j].top());
    for (int j = 0; j + n - 1 < b; ++j) {
      ans[i][j] = R.top();
      R.pop();
      if (j + n < b) R.push(C[j + n].top());
    }
    for (int j = 0; j < b; ++j) {
      C[j].pop();
      C[j].push(A[i + n][j]);
    }
  }
}
int main() {
  scanf("%d%d%d", &a, &b, &n);
  for (int i = 0; i < a; ++i)
    for (int j = 0; j < b; ++j)
      scanf("%d", &A[i][j]);
  solve(0);
  for (int i = 0; i < a; ++i)
    for (int j = 0; j < b; ++j)
      A[i][j] *= -1;
  solve(1);
  int ans = 1000000000;
  for (int i = 0; i + n - 1 < a; ++i)
    for (int j = 0; j + n - 1 < b; ++j)
      ans = std::min(ans, -(_ans[0][i][j] + _ans[1][i][j]));
  printf("%d\n", ans);
  return 0;
}
