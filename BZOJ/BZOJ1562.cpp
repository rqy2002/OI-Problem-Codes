#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 10050;
int A[N][2];
int mx[N], my[N], vis[N], time;
bool match(int x) {
  for (int i = 0; i < 2; ++i) {
    int y = A[x][i];
    if (vis[y] == time) continue;
    vis[y] = time;
    if (my[y] == -1 || match(my[y])) {
      mx[my[y] = x] = y;
      return true;
    }
  }
  return false;
}
int main() {
  int n, x;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &x);
    A[i][0] = (i - x + n) % n;
    A[i][1] = (i + x) % n;
    if (A[i][0] > A[i][1]) std::swap(A[i][0], A[i][1]);
    mx[i] = my[i] = -1;
  }
  for (int i = n - 1; ~i; --i) {
    ++time;
    if (!match(i)) {
      printf("No Answer");
      return 0;
    }
  }
  for (int i = 0; i < n; ++i)
    printf("%d%c", mx[i], i == n - 1 ? '\n' : ' ');
  return 0;
}
