/**************************************************************
 * Problem: BZOJ4821
 * Author: Rqy
 * Date: 2018 Feb 26
 * Algorithm: 
**************************************************************/
#include <cctype>
#include <cstdio>
typedef long long LL;
const int N = 100050;
const int N2 = N * 4;
LL x[N], y[N];
double Sx2[N2], Sx[N2], Sy[N2], Sxy[N2];
bool setv[N2];
double addx[N2], addy[N2];
inline LL Si(LL l, LL r) {
  return (l + r) * (r - l + 1) / 2;
}
inline LL Si2(LL l, LL r) {
  return (r * (r + 1) * (2 * r + 1) - (l - 1) * l * (2 * l - 1)) / 6;
}
void upd(int o, int l, int r) {
  if (setv[o]) {
    Sx2[o] = Sxy[o] = Si2(l, r);
    Sx[o] = Sy[o] = Si(l, r);
  } else if (l == r) {
    Sx2[o] = x[l] * x[l];
    Sx[o] = x[l];
    Sy[o] = y[l];
    Sxy[o] = x[l] * y[l];
  } else {
    Sx2[o] = Sx2[o * 2] + Sx2[o * 2 + 1];
    Sx[o] = Sx[o * 2] + Sx[o * 2 + 1];
    Sy[o] = Sy[o * 2] + Sy[o * 2 + 1];
    Sxy[o] = Sxy[o * 2] + Sxy[o * 2 + 1];
  }
  Sxy[o] += addx[o] * Sy[o] + addy[o] * Sx[o] + (r - l + 1) * addx[o] * addy[o];
  Sx2[o] += 2 * addx[o] * Sx[o] + (r - l + 1) * addx[o] * addx[o];
  Sx[o] += addx[o] * (r - l + 1);
  Sy[o] += addy[o] * (r - l + 1);
}
void pd(int o, int l, int r) {
  if (l != r) {
    if (setv[o]) {
      addx[o * 2] = addy[o * 2] = addx[o * 2 + 1] = addy[o * 2 + 1] = 0;
      setv[o * 2] = setv[o * 2 + 1] = 1;
      setv[o] = 0;
    }
    addx[o * 2] += addx[o];
    addx[o * 2 + 1] += addx[o];
    addy[o * 2] += addy[o];
    addy[o * 2 + 1] += addy[o];
    addx[o] = addy[o] = 0;
  } else {
    if (setv[o]) {
      x[l] = y[l] = l;
      setv[o] = 0;
    }
    x[l] += addx[o];
    y[l] += addy[o];
    addx[o] = addy[o] = 0;
  }
}
void build(int o, int l, int r) {
  if (l != r) {
    int mid = (l + r) / 2;
    build(o * 2, l, mid);
    build(o * 2 + 1, mid + 1, r);
  }
  upd(o, l, r);
}
int value, L, R;
void add(int o, int l, int r, double *a) {
  if (L <= l && r <= R)
    a[o] += value;
  else {
    pd(o, l, r);
    int mid = (l + r) / 2;
    if (L <= mid) add(o * 2, l, mid, a); else upd(o * 2, l, mid);
    if (R > mid) add(o * 2 + 1, mid + 1, r, a); else upd(o * 2 + 1, mid + 1, r);
  }
  upd(o, l, r);
}
void set(int o, int l, int r) {
  if (L <= l && r <= R) {
    setv[o] = 1;
    addx[o] = addy[o] = 0;
  } else {
    pd(o, l, r);
    int mid = (l + r) / 2;
    if (L <= mid) set(o * 2, l, mid); else upd(o * 2, l, mid);
    if (R > mid) set(o * 2 + 1, mid + 1, r); else upd(o * 2 + 1, mid + 1, r);
  }
  upd(o, l, r);
}
double ansx, ansy, ansxy, ansx2;
void query(int o, int l, int r) {
  upd(o, l, r);
  if (L <= l && r <= R) {
    ansx += Sx[o];
    ansy += Sy[o];
    ansxy += Sxy[o];
    ansx2 += Sx2[o];
  } else {
    pd(o, l, r);
    int mid = (l + r) / 2;
    if (L <= mid) query(o * 2, l, mid); else upd(o * 2, l, mid);
    if (R > mid) query(o * 2 + 1, mid + 1, r); else upd(o * 2 + 1, mid + 1, r);
  }
}
inline int readInt() {
  int ans = 0, f = 1, c;
  do c = getchar(); while (!isdigit(c) && c != '-');
  if (c == '-') { f = -1; c = getchar(); }
  do ans = ans * 10 + c - '0';
  while (isdigit(c = getchar()));
  return ans * f;
}
int main() {
  int n, m;
  n = readInt();
  m = readInt();
  for (int i = 1; i <= n; ++i)
    x[i] = readInt();
  for (int i = 1; i <= n; ++i)
    y[i] = readInt();
  build(1, 1, n);
  for (int k = 0; k < m; ++k) {
    int tp = readInt();
    L = readInt();
    R = readInt();
    if (tp == 1) {
      ansx = ansy = ansxy = ansx2 = 0;
      query(1, 1, n);
      printf("%.9lf\n",
          (double)(ansxy - (double)ansx * ansy / (R - L + 1))
        / (ansx2 - (double)ansx * ansx / (R- L + 1)));
    } else {
      if (tp == 3)
        set(1, 1, n);
      value = readInt();
      add(1, 1, n, addx);
      value = readInt();
      add(1, 1, n, addy);
    }
  }
  return 0;
}
