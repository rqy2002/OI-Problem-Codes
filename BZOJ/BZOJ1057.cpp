#include<cstdio>
#include<cstring>
#include<stack>
using std::stack;
stack<int> S;
const int maxn = 2010;
int high[maxn], L[maxn], R[maxn];
int A[maxn], B[maxn];
inline int max(int a, int b) {
  return a > b ? a : b;
}
inline int min(int a, int b) {
  return a < b ? a : b;
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  int ans1 = 0, ans2 = 0;
  memset(high, 0, sizeof(high));
  for(int i = 0; i < n; i++)
  {
    while (!S.empty()) S.pop();
    S.push(0);
    for(int j = 1; j <= m; j++)
    {
      scanf("%1d", &A[j]);
      high[j] = (!i || B[j] != A[j]) ? high[j] + 1 : 1;
      B[j] = A[j];
      if (j > 1 && A[j] == A[j - 1]) {
        while (!S.empty()) S.pop();
        L[j] = j;
        S.push(j);
      } else {
        while (S.size() > 1 && high[S.top()] >= high[j]) S.pop();
        L[j] = high[S.top()] >= high[j] ? S.top() : S.top() + 1;
        S.push(j);
      }
    }
    while (!S.empty()) S.pop();
    S.push(m + 1);
    for(int j = m; j; j--)
    {
      if (j < m && A[j] == A[j + 1]) {
        while (!S.empty()) S.pop();
        R[j] = j;
        S.push(j);
      } else {
        while (S.size() > 1 && high[S.top()] >= high[j]) S.pop();
        R[j] = high[S.top()] >= high[j] ? S.top() + 1 : S.top();
        S.push(j);
      }
      ans1 = max(ans1, min(R[j] - L[j], high[j]) * min(R[j] - L[j], high[j]));
      ans2 = max(ans2, (R[j] - L[j]) * high[j]);
    }
  }
  printf("%d\n%d\n", ans1, ans2);
  return 0;
}
