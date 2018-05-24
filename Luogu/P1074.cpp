/**************************************************************
 * Problem: Luogu P1074
 * Author: Rqy
 * Date: 2018 Feb 09
 * Algorithm: DLX
**************************************************************/
#include <algorithm>
#include <cstdio>
const int M = 4000;
namespace DLX{
int T[M], U[M], D[M], L[M], R[M], pt[M], cnt;
int S[M];
void init(int n) {
  for (int i = 0; i <= n; ++i) {
    U[i] = D[i] = T[i] = i;
    L[i] = i - 1;
    R[i] = i + 1;
  }
  R[L[0] = n] = 0;
  cnt = n + 1;
}
void addLine(int *A, int n, int p) {
  int left = cnt;
  for (int i = 0; i < n; ++i) {
    ++S[T[cnt] = A[i]];
    D[U[cnt] = U[A[i]]] = cnt;
    U[D[cnt] = A[i]] = cnt;
    L[cnt] = cnt - 1;
    R[cnt] = cnt + 1;
    pt[cnt] = p;
    ++cnt;
  }
  R[L[left] = cnt - 1] = left;
}
#define F(i, A, a) for (int i = A[a]; i != a; i = A[i])
void remove(int a) {
  L[R[a]] = L[a];
  R[L[a]] = R[a];
  F(i, D, a) F(j, R, i) {
    --S[T[j]];
    U[D[j]] = U[j];
    D[U[j]] = D[j];
  }
}
void restore(int a) {
  F(i, U, a) F(j, L, i) {
    D[U[j]] = j;
    U[D[j]] = j;
    ++S[T[j]];
  }
  R[L[a]] = a;
  L[R[a]] = a;
}
int dfs() {
  if (!R[0]) return 0;
  int ans = -0x3fffffff;
  int x = R[0];
  F(i, R, 0) if (S[i] <= S[x])
    x = i;
  remove(x);
  F(i, D, x) {
    F(j, R, i) remove(T[j]);
    ans = std::max(ans, dfs() + pt[i]);
    F(j, L, i) restore(T[j]);
  }
  restore(x);
  return ans;
}
};
int A[9][9];
inline int encode(int a, int b, int c) {
  return (a * 9 + b) * 9 + c;
}
const int p[9][9] = {
  {6, 6, 6, 6, 6, 6, 6, 6, 6},
  {6, 7, 7, 7, 7, 7, 7, 7, 6},
  {6, 7, 8, 8, 8, 8, 8, 7, 6},
  {6, 7, 8, 9, 9, 9, 8, 7, 6},
  {6, 7, 8, 9, 10, 9, 8, 7, 6},
  {6, 7, 8, 9, 9, 9, 8, 7, 6},
  {6, 7, 8, 8, 8, 8, 8, 7, 6},
  {6, 7, 7, 7, 7, 7, 7, 7, 6},
  {6, 6, 6, 6, 6, 6, 6, 6, 6},
};
void addNum(int a, int b, int c) {
  int P[4] = {
    encode(0, a, c),
    encode(1, b, c),
    encode(2, (a / 3) * 3 + (b / 3), c),
    encode(3, a, b + 1)
  };
  DLX::addLine(P, 4, c * p[a][b]);
}
int main() {
  DLX::init(9 * 9 * 4);
  for (int i = 0; i < 9; ++i)
    for (int j = 0; j < 9; ++j) {
      scanf("%d", &A[i][j]);
      if (A[i][j]) addNum(i, j, A[i][j]);
      else for (int t = 1; t <= 9; ++t)
        addNum(i, j, t);
    }
  printf("%d\n", std::max(DLX::dfs(), -1));
  return 0;
}

