/**************************************************************
 * Problem: BZOJ1972
 * Author: Rqy
 * Date: 2017 Dec 12
 * Algorithm: 模拟
**************************************************************/
#include <algorithm>
#include <cstdio>
namespace rqy{
  enum CardType{
    NoneCard, CardK, CardD, CardP,
    CardN, CardW, CardJ, CardZ, CardF
  };
  enum Role{ NoneRole, MP, ZP, FP };
  struct Card;
  struct Pig;
  void dont(Pig*, Pig*);
  void doK(Pig*, Pig*);
  void doP(Pig*, Pig*);
  void doN(Pig*, Pig*);
  void doW(Pig*, Pig*);
  void doZ(Pig*, Pig*);
  void doF(Pig*, Pig*);
  bool canDoSelf(const Pig*, const Pig*);
  bool cannotDo(const Pig*, const Pig*);
  bool canDoK(const Pig*, const Pig*);
  bool canDoP(const Pig*, const Pig*);
  bool canDoF(const Pig*, const Pig*);
  void (*const (useTo[]))(Pig*, Pig*) = {
    dont, doK, dont, doP,
    doN, doW, dont, doZ, doF
  };
  bool (*const (canUseTo[]))(const Pig*, const Pig*) = {
    cannotDo, canDoK, cannotDo, canDoP,
    canDoSelf, canDoSelf, cannotDo, canDoSelf, canDoF
  };
  const int N = 12, M = 10000;
  int n, m, sth;
  bool ended;
  struct Card{
    CardType type;
    Card *pre, *nxt;
    void (*useTo)(Pig*, Pig*);
    bool (*canUseTo)(const Pig*, const Pig*);
    Card(CardType t = NoneCard, Card *nxt = NULL, Card *pre = NULL)
      : type(t), pre(pre), nxt(nxt) {
        useTo = rqy::useTo[t];
        canUseTo = rqy::canUseTo[t];
      }
    void remove() {
      if (pre != NULL) pre->nxt = nxt;
      if (nxt != NULL) nxt->pre = pre;
    }
  }cards[M], *end = cards;
  struct Pig{
    Role role;
    Pig *right;
    Card *head;
    bool jumped, hitMP, equiped, doKed;
    int life;
    Pig(Role role = NoneRole, Pig *right = NULL)
      : role(role), right(right) {
        head = NULL;
        jumped = role == MP;
        equiped = hitMP = false;
        life = 4;
      }
    Card* findCard(CardType t) {
      Card *c = head;
      while (c != NULL && c->type != t) c = c->nxt;
      return c;
    }
    void addCard(CardType t) {
      *end = Card(t);
      if (head == NULL) head = end++;
      else {
        Card *c = head;
        while (c->nxt != NULL) c = c->nxt;
        (c->nxt = end++)->pre = c;
      }
    }
    void act() {
      Card *c = head->nxt;
      while (life > 0 && c != NULL) {
        bool ok = false;
        Pig *p = this;
        do if (c->canUseTo(this, p)) {
          c->remove(); c->useTo(this, p); ok = true;
        } while (!ok && (p = p->right) != this);
        if (ok) c = head; else c = c->nxt;
      }
    }
  }pigs[N], *now;
  CardType getCardType(char c) {
    for (int i = 0; i < 8; ++i)
      if ("KDPNWJZF"[i] == c)
        return (CardType)(i + 1);
    return NoneCard;
  }
  CardType stack[M];
  void init() {
    scanf("%d%d", &n, &m);
    char s[5];
    for (int i = 0; i < n; ++i) {
      scanf("%s", s);
      Role r;
      if (s[0] == 'M') r = MP;
      else if (s[0] == 'Z') r = ZP;
      else r = FP;
      pigs[i] = Pig(r, &pigs[(i + 1) % n]);
      pigs[i].addCard(NoneCard);
      for (int j = 0; j < 4; ++j) {
        scanf("%s", s);
        pigs[i].addCard(getCardType(s[0]));
      }
    }
    for (int i = 0; i < m; ++i) {
      scanf("%s", s);
      stack[i] = getCardType(s[0]);
    }
    ended = false;
    now = pigs;
  }
  void print(bool MPwin) {
    if (ended) return;
    ended = true;
    printf("%s\n", MPwin ? "MP" : "FP");
    for (int i = 0; i < n; ++i) {
      printf("%d %d ", pigs[i].jumped, pigs[i].life);
      if (pigs[i].life == 0) printf("DEAD");
      else for (Card *j = pigs[i].head->nxt; j != NULL; j = j->nxt) {
        printf("%c", "KDPNWJZF"[j->type - 1]);
        if (j->nxt != NULL) printf(" ");
      }
      printf("\n");
    }
  }
#define getCard(p)\
  p->addCard(stack[sth]);\
  if (sth < m - 1) ++sth;
  void main() {
    init();
    while (!ended) {
      getCard(now); getCard(now);
      now->doKed = false;
      now->act();
      now = now->right;
    }
  }
  bool MPto(const Pig *t) {
    return t->jumped ? t->role == FP : t->hitMP;
  }
  bool canDoF(const Pig *from, const Pig *to) {
    if (from->role == FP) return to->role == MP;
    else if (from->role == ZP) return to->role == FP && to->jumped;
    else return MPto(to);
  }
  bool canDoP(const Pig *from, const Pig *to) {
    return from == to && from->life < 4;
  }
  bool canDoK(const Pig *from, const Pig *to) {
    if (from->right != to) return false;
    if (!from->equiped && from->doKed) return false;
    if (from->role == FP) return to->role != FP && to->jumped;
    else if (from->role == ZP) return to->role == FP && to->jumped;
    else return MPto(to);
  }
  bool cannotDo(const Pig*, const Pig*) { return false; }
  bool canDoSelf(const Pig *a, const Pig *b) { return a == b; }
  bool canDoJ(Pig *t, bool isFP) {
    Pig *p = t;
    do if ((p->role == FP) == isFP) {
      Card *c = p->findCard(CardJ);
      if (c != NULL) {
        c->remove(); p->jumped = true;
        return !canDoJ(p, !isFP);
      }
    } while ((p = p->right) != t);
    return false;
  }
  void kill(Pig *from, Pig *to) {
    if (to->role == MP) print(false);
    else if (to->role == FP) {
      int i;
      for (i = 0; i < n && (pigs[i].role != FP || pigs[i].life == 0); ++i);
      if (i >= n) print(true);
      getCard(from); getCard(from); getCard(from);
    } else if (from->role == MP) from->head->nxt = NULL, from->equiped = false;
    for (int i = 0; i < n; ++i) if (pigs[i].right == to)
        pigs[i].right = to->right;
  }
  void damage(Pig *from, Pig *to) {
    if (to->role == MP) from->hitMP = true;
    if (!--to->life) {
      Card* c = to->findCard(CardP);
      if (c == NULL) kill(from, to);
      else { c->remove(); ++to->life; };
    }
  }
  void doF(Pig *from, Pig *to) {
    from->jumped = true;
    if (to->jumped && canDoJ(from, to->role == FP)) return;
    if (from->role != MP || to->role != ZP)
      while (1) {
        Card *c = to->findCard(CardK);
        if (c == NULL) break;
        c->remove(); std::swap(from, to);
      }
    damage(from, to);
  }
  void doZ(Pig *a, Pig*) { a->equiped = true; }
  void doW(Pig *from, Pig*) {
    for (Pig *p = from->right; p != from; p = p->right) {
      if (p->jumped && canDoJ(from, p->role == FP)) continue;
      Card *c = p->findCard(CardD);
      if (c == NULL) damage(from, p);
      else c->remove();
    }
  }
  void doN(Pig *from, Pig*) {
    for (Pig *p = from->right; p != from; p = p->right) {
      if (p->jumped && canDoJ(from, p->role == FP)) continue;
      Card *c = p->findCard(CardK);
      if (c == NULL) damage(from, p);
      else c->remove();
    }
  }
  void doP(Pig *a, Pig*) { ++a->life; }
  void doK(Pig *from, Pig *to) {
    from->doKed = true;
    from->jumped = true;
    Card *c = to->findCard(CardD);
    if (c == NULL) damage(from, to);
    else c->remove();
  }
  void dont(Pig*, Pig*) {}
};
int main() {
  rqy::main();
}
