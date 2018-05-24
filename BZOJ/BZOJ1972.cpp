/**************************************************************
 * Problem: BZOJ1972
 * Author: Rqy
 * Date: 2017 Dec 08
 * Algorithm: 模拟
**************************************************************/
#include <algorithm>
#include <cstdio>
namespace rqy{
  const int NN = 15, M = 20050;
#define P 0
#define K 1
#define D 2
#define F 3
#define N 4
#define W 5
#define J 6
#define Z 7
#define forExcept(i, x) \
  for (int i = (x + 1) % n; i != x; i = (i + 1) % n) if (!dead[i])
#define forFrom(i, x) \
  for (int i = x, _ = 1; _ || i != x; _ = 0, i = (i + 1) % n) if (!dead[i])
#define forInHand(i, x) \
  for (int i = head[x]; i; i = nxt[i])
  int cardStack[M];
  int type[M], pre[M], nxt[M], head[NN], end[NN];
  int left[NN], right[NN];
  int n, m, cur, cnt;
  int MP, life[NN], side[NN];
  bool equip[NN];
  bool dead[NN];
  bool jumped[NN], Flike[NN];
  bool End;
  void playMP(int);
  void playFP(int);
  void playZP(int);
  void getCardFromStack(int);
  void kill(int, int);
  void damage(int, int);
  void doK(int, int);
  void doF(int, int);
  void doN(int);
  void doW(int);
  bool doJ(int, int);
  void addCard(int, int);
  void removeCard(int, int);
  void init();
  void print();
  inline int getCard(char c) {
    for (int i = 0; i < 8; ++i)
      if ("PKDFNWJZ"[i] == c)
        return i;
    return 8;
  }
  void main() {
    init();
    for(int x = 0; !End; x = (x + 1) % n) if (!dead[x]) {
      if (x == MP) playMP(x);
      else if (side[x] == 0) playZP(x);
      else playFP(x);
    }
    print();
  }
  void print() {
    if (dead[MP]) puts("FP");
    else puts("MP");
    for (int i = 0; i < n; ++i) {
      if (dead[i]) printf("DEAD\n");
      else {
        forInHand(j, i) {
          if (j != head[i]) putchar(' ');
          putchar("PKDFNWJZ"[type[j]]);
        }
        putchar('\n');
      }
    }
  }
  void init() {
    scanf("%d%d", &n, &m);
    char s[10];
    cnt = cur = 0;
    End = false;
    for (int i = 0; i < n; ++i) {
      life[i] = 4;
      equip[i] = dead[i] = jumped[i] = Flike[i] = head[i] = end[i] = 0;
      right[i] = i + 1;
      left[i] = i - 1;
      scanf("%s", s);
      side[i] = (s[0] == 'F');
      if (s[0] == 'M') jumped[MP = i] = 1;
      for (int j = 0; j < 4; ++j) {
        scanf("%s", s);
        addCard(i, getCard(s[0]));
      }
    }
    left[0] = n - 1;
    right[n - 1] = 0;
    for (int i = 0; i < m; ++i) {
      scanf("%s", s);
      cardStack[i] = getCard(s[0]);
    }
  }
  void removeCard(int x, int i) {
    if (head[x] == i) head[x] = nxt[i];
    else nxt[pre[i]] = nxt[i];
    if (end[x] == i) end[x] = pre[i];
    else pre[nxt[i]] = pre[i];
  }
  void addCard(int x, int c) {
    type[++cnt] = c;
    pre[cnt] = nxt[cnt] = 0;
    if (!head[x]) head[x] = end[x] = cnt;
    else {
      pre[nxt[end[x]] = cnt] = end[x];
      end[x] = cnt;
    }
  }
  bool doJ(int x, int si) {
      forFrom(y, x) if (side[y] == si) {
        forInHand(i, y) if (type[i] == J) {
          jumped[y] = 1;
          removeCard(y, i);
          return !doJ(y, si ^ 1);
        }
    }
    return false;
  }
  void doW(int x) {
    forExcept(y, x) {
      if (jumped[y] && doJ(x, side[y])) continue;
      else {
        bool ok = false;
        forInHand(i, y) if (type[i] == D) {
          removeCard(y, i);
          ok = true;
          break;
        }
        if (!ok) {
          damage(x, y);
          if (End) break;
        }
      }
    }
  }
  void doN(int x) {
    forExcept(y, x) {
      if (jumped[y] && doJ(x, side[y])) continue;
      else {
        bool ok = false;
        forInHand(i, y) if (type[i] == K) {
          removeCard(y, i);
          ok = true;
          break;
        }
        if (!ok) {
          damage(x, y);
          if (End) break;
        }
      }
    }
  }
  void doF(int x, int y) {
    jumped[x] = true;
    if (jumped[y] && doJ(x, side[y])) return;
    bool finish = false;
    while (!finish) {
      finish = true;
      if (side[y] != 0 || x != MP)
        forInHand(i, y) if (type[i] == K) {
          removeCard(y, i);
          std::swap(x, y);
          finish = false;
          break;
        }
    }
    damage(x, y);
  }
  void doK(int x, int y) {
    jumped[x] = 1;
    forInHand(i, y) if (type[i] == D) {
      removeCard(y, i);
      return;
    }
    damage(x, y);
  }
  void damage(int x, int y) {
    if (!(--life[y])) {
      forInHand(i, y) if (type[i] == P) {
        ++life[y];
        removeCard(y, i);
        break;
      }
      if (!life[y]) kill(x, y);
    }
    if (y == MP) Flike[x] = true;
  }
  void kill(int x, int y) {
    dead[y] = 1;
    left[right[y]] = left[y];
    right[left[y]] = right[y];
    if (side[y] == 1) {
      End = true;
      for (int i = 0; i < n; ++i)
        if (side[i] == 1 && !dead[i])
          End = false;
      if (End) return;
      getCardFromStack(x);
      getCardFromStack(x);
      getCardFromStack(x);
    } else if (y != MP) {
      if (x == MP) {
        equip[x] = 0;
        while (head[x]) removeCard(x, head[x]);
      }
    } else
      End = true;
  }
  void getCardFromStack(int x) {
    addCard(x, cardStack[cur]);
    if (cur < m - 1) cur++;
  }
  void playZP(int x) {
    getCardFromStack(x);
    getCardFromStack(x);
    bool has_kill = false;
    bool ok = true;
    while (ok && !End && !dead[x]) {
      ok = false;
      forInHand(i, x) {
        switch (type[i]) {
          case K:
            if (has_kill && !equip[x]) break;
            if (side[right[x]] == 1 && jumped[right[x]]) {
              doK(x, right[x]);
              has_kill = ok = true;
              break;
            }
            break;
          case P:
            if (life[x] != 4) {
              ++life[x];
              ok = true;
            }
            break;
          case F:
            forExcept(y, x) if (side[y] == 1 && jumped[y]) {
              doF(x, y);
              ok = true;
              break;
            }
            break;
          case N:
            doN(x);
            ok = true;
            break;
          case W:
            doW(x);
            ok = true;
            break;
          case Z:
            equip[x] = true;
            ok = true;
            break;
        }
        if (ok) {
          removeCard(x, i);
          break;
        }
      }
    }
  }
  void playFP(int x) {
    getCardFromStack(x);
    getCardFromStack(x);
    bool has_kill = false;
    bool ok = true;
    while (ok && !End && !dead[x]) {
      ok = false;
      forInHand(i, x) {
        switch (type[i]) {
          case K:
            if (has_kill && !equip[x]) break;
            if (side[right[x]] == 0 && jumped[right[x]]) {
              doK(x, right[x]);
              has_kill = ok = true;
              break;
            }
            break;
          case P:
            if (life[x] != 4) {
              ++life[x];
              ok = true;
            }
            break;
          case F:
            doF(x, MP);
            ok = true;
            break;
          case N:
            doN(x);
            ok = true;
            break;
          case W:
            doW(x);
            ok = true;
            break;
          case Z:
            equip[x] = true;
            ok = true;
            break;
        }
        if (ok) {
          removeCard(x, i);
          break;
        }
      }
    }
  }
  void playMP(int x) {
    getCardFromStack(x);
    getCardFromStack(x);
    bool has_kill = false;
    bool ok = true;
    while (ok && !End && !dead[x]) {
      ok = false;
      forInHand(i, x) {
        switch (type[i]) {
          case K:
            if (has_kill && !equip[x]) break;
            if (jumped[right[x]] ? side[right[x]] == 1 : Flike[right[x]]) {
              doK(x, right[x]);
              has_kill = ok = true;
              break;
            }
            break;
          case P:
            if (life[x] != 4) {
              ++life[x];
              ok = true;
            }
            break;
          case F:
            forExcept(y, x) if (jumped[y] ? side[y] == 1 : Flike[y]) {
              doF(x, y);
              ok = true;
              break;
            }
            break;
          case N:
            doN(x);
            ok = true;
            break;
          case W:
            doW(x);
            ok = true;
            break;
          case Z:
            equip[x] = true;
            ok = true;
            break;
        }
        if (ok) {
          removeCard(x, i);
          break;
        }
      }
    }
  }
};
int main() {
  rqy::main();
}
