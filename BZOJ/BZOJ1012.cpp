#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
const int N = 200050;
int A[N], M[N];
inline int readInt() {
  int ans = 0;
  char c;
  do c = getchar(); while (!isdigit(c));
  do {
    ans = ans * 10 + c - '0';
    c = getchar();
  } while (isdigit(c));
  return ans;
}
inline char readChar() {
  char c;
  do c = getchar(); while (isspace(c));
  return c;
}
int main() {
  int m = readInt();
  int d = readInt();
  int last_ans = 0, n = 0, cnt = 0;
  for (int i = 0; i < m; ++i) {
    char c = readChar();
    int x = readInt();
    if (c == 'A') {
      x = (x + last_ans) % d;
      while (cnt && A[M[cnt - 1]] < x) --cnt;
      A[M[cnt++] = n++] = x;
    } else
      printf("%d\n", last_ans = A[*std::lower_bound(M, M + cnt, n - x)]);
  }
  return 0;
}
