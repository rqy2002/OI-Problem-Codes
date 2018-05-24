/**************************************************************
 * Problem: BZOJ2550
 * Author: Rqy
 * Date: 2018 Feb 28
 * Algorithm: 
**************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
char **s;
enum Type{
  NONE, CHAR, EDIT, FRAC, MATRIX
};
struct Object{
  int height, width, middle;
  Object *left, *right, *father;
  Object(Object *fa);
  virtual Type getType() = 0;
  virtual void draw(int x, int y) = 0;
  virtual void calcSize() = 0;
};
struct None : Object{
  None(Object *fa);
  virtual Type getType() { return NONE; }
  virtual void draw(int x, int y);
  virtual void calcSize();
};
struct Char : Object{
  char c;
  Char(Object *fa, char c);
  virtual Type getType() { return CHAR; }
  virtual void draw(int x, int y);
  virtual void calcSize();
};
struct Edit : Object{
  Object *head, *tail;
  Edit(Object *fa);
  virtual Type getType() { return EDIT; }
  virtual void draw(int x, int y);
  virtual void calcSize();
};
struct Frac : Object{
  Edit *num, *den;
  Frac(Object *fa);
  virtual Type getType() { return FRAC; }
  virtual void draw(int x, int y);
  virtual void calcSize();
};
struct Matrix : Object{
  Edit* **data;
  int n, m;
  Matrix(Object *fa);
  None* addRow(Edit *p);
  None* addCol(Edit *p);
  void find(Edit *p, int &x, int &y);
  virtual Type getType() { return MATRIX; }
  virtual void draw(int x, int y);
  virtual void calcSize();
};

Object::Object(Object *fa) : left(NULL), right(NULL), father(fa) {}

None::None(Object *fa) : Object(fa) { calcSize(); }
void None::calcSize() { height = 1; width = 0; middle = 0; }
void None::draw(int, int) {}

Char::Char(Object *fa, char c) : Object(fa), c(c) { calcSize(); }
void Char::calcSize() { height = 1; width = (c == '-' ? 3 : 1); middle = 0; }
void Char::draw(int x, int y) {
  if (c == '-') s[x][y] = s[x][y + 2] = ' ', s[x][y + 1] = '-';
  else s[x][y] = c;
}

Edit::Edit(Object *fa) : Object(fa) {
  head = tail = new None(this);  calcSize();
}
void Edit::calcSize() {
  Object *mh = head;
  for (Object *i = head; i != NULL; i = i->right)
    if (i->middle > mh->middle) mh = i;
  middle = mh->middle;
  height = 0, width = 0;
  for (Object *i = head; i != NULL; i = i->right) {
    width += i->width;
    height = std::max(height, i->height - i->middle + middle);
  }
}
void Edit::draw(int x, int y) {
  for (Object *i = head; i != NULL; i = i->right) {
    i->draw(x, y);
    y += i->width;
  }
}

Frac::Frac(Object *fa) : Object(fa) {
  num = new Edit(this); den = new Edit(this); calcSize();
}
void Frac::calcSize() {
  width = std::max(num->width, den->width) + 2;
  height = num->height + den->height + 1;
  middle = num->height;
}
void Frac::draw(int x, int y) {
  num->draw(x - (num->height - num->middle), y + (width - num->width) / 2);
  for (int i = 0; i < width; ++i)
    s[x][y + i] = '-';
  den->draw(x + den->middle + 1, y + (width - den->width) / 2);
}

Matrix::Matrix(Object *fa) : Object(fa), n(1), m(1) {
  data = new Edit**[1];
  data[0] = new Edit*[1];
  data[0][0] = new Edit(this);
  calcSize();
}
void Matrix::calcSize() {
  height = n - 1;
  for (int i = 0; i < n; ++i) {
    int h1 = 0, h2 = 0;
    for (int j = 0; j < m; ++j) {
      h1 = std::max(h1, data[i][j]->middle);
      h2 = std::max(h2, data[i][j]->height - data[i][j]->middle);
    }
    height += h1 + h2;
  }
  width = m + 1;
  for (int j = 0; j < m; ++j) {
    int w = 0;
    for (int i = 0; i < n; ++i)
      w = std::max(w, data[i][j]->width);
    width += w;
  }
  middle = (n + 1) / 2 - 1;
  for (int i = 0; i < (n + 1) / 2; ++i) {
    int h1 = 0, h2 = 0;
    for (int j = 0; j < m; ++j) {
      h1 = std::max(h1, data[i][j]->middle);
      h2 = std::max(h2, data[i][j]->height - data[i][j]->middle);
    }
    middle += h1;
    if (i * 2 < n - 1) middle += h2;
  }
}
void Matrix::draw(int x, int y) {
  int *w = new int[m];
  for (int j = 0; j < m; ++j)
    for (int i = w[j] = 0; i < n; ++i)
      w[j] = std::max(w[j], data[i][j]->width);
  x -= middle;
  for (int i = 0; i < n; ++i) {
    int h1 = 0, h2 = 0;
    for (int j = 0; j < m; ++j) {
      h1 = std::max(h1, data[i][j]->middle);
      h2 = std::max(h2, data[i][j]->height - data[i][j]->middle);
    }
    s[x + h1][y] = '[';
    for (int j = 0, y0 = y + 1; j < m; ++j) {
      data[i][j]->draw(x + h1, y0 + (w[j] - data[i][j]->width) / 2);
      y0 += w[j] + 1;
    }
    s[x + h1][y + width - 1] = ']';
    x += h1 + h2 + 1;
  }
  delete []w;
}
None* Matrix::addRow(Edit *p) {
  int x, y;
  find(p, x, y);
  Edit ***new_data = new Edit**[n + 1];
  for (int i = 0; i < n + 1; ++i)
    new_data[i] = new Edit*[m];
  for (int i = 0; i < n + 1; ++i)
    for (int j = 0; j < m; ++j)
      if (i != x)
        new_data[i][j] = data[i - (i > x)][j];
      else
        new_data[i][j] = new Edit(this);
  data = new_data;
  ++n;
  calcSize();
  return dynamic_cast<None*>(data[x][y]->head);
}
None* Matrix::addCol(Edit *p) {
  int x, y;
  find(p, x, y);
  Edit ***new_data = new Edit**[n];
  for (int i = 0; i < n; ++i)
    new_data[i] = new Edit*[m + 1];
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m + 1; ++j)
      if (j != y)
        new_data[i][j] = data[i][j - (j > y)];
      else
        new_data[i][j] = new Edit(this);
  data = new_data;
  ++m;
  calcSize();
  return dynamic_cast<None*>(data[x][y]->head);
}
void Matrix::find(Edit *p, int &x, int &y) {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (data[i][j] == p) {
        x = i;
        y = j;
        return;
      }
}

None *cur;
void Home() {
  cur = dynamic_cast<None*>(dynamic_cast<Edit*>(cur->father)->head);
}
void End() {
  cur = dynamic_cast<None*>(dynamic_cast<Edit*>(cur->father)->tail);
}
void Left() {
  if (cur->left == NULL) {
    Edit *fa = dynamic_cast<Edit*>(cur->father);
    if (fa->father) {
      if (fa->father->getType() == MATRIX) {
        Matrix *g = dynamic_cast<Matrix*>(fa->father);
        int x, y;
        g->find(fa, x, y);
        if (y) {
          cur = dynamic_cast<None*>(g->data[x][y - 1]->tail);
          return;
        }
      }
      cur = dynamic_cast<None*>(fa->father->left);
    }
  } else if (cur->left->getType() == FRAC)
    cur = dynamic_cast<None*>(dynamic_cast<Frac*>(cur->left)->num->tail);
  else if (cur->left->getType() == MATRIX) {
    Matrix *le = dynamic_cast<Matrix*>(cur->left);
    cur = dynamic_cast<None*>(le->data[(le->n + 1) / 2 - 1][le->m - 1]->tail);
  } else
    cur = dynamic_cast<None*>(cur->left->left);
}
void Right() {
  if (cur->right == NULL) {
    Edit *fa = dynamic_cast<Edit*>(cur->father);
    if (fa->father) {
      if (fa->father->getType() == MATRIX) {
        Matrix *g = dynamic_cast<Matrix*>(fa->father);
        int x, y;
        g->find(fa, x, y);
        if (y < g->m - 1) {
          cur = dynamic_cast<None*>(g->data[x][y + 1]->head);
          return;
        }
      }
      cur = dynamic_cast<None*>(fa->father->right);
    }
  } else if (cur->right->getType() == FRAC)
    cur = dynamic_cast<None*>(dynamic_cast<Frac*>(cur->right)->num->head);
  else if (cur->right->getType() == MATRIX) {
    Matrix *ri = dynamic_cast<Matrix*>(cur->right);
    cur = dynamic_cast<None*>(ri->data[(ri->n + 1) / 2 - 1][0]->head);
  } else
    cur = dynamic_cast<None*>(cur->right->right);
}
void Up() {
  for (None* c = cur; c->father->father != NULL;) {
    Edit *f = dynamic_cast<Edit*>(c->father);
    Object *g = f->father;
    if (g->getType() == FRAC && f == dynamic_cast<Frac*>(g)->den) {
      cur = dynamic_cast<None*>(dynamic_cast<Frac*>(g)->num->head);
      return;
    } else if (g->getType() == MATRIX) {
      Matrix *gg = dynamic_cast<Matrix*>(g);
      int x, y; gg->find(f, x, y);
      if (x) {
        cur = dynamic_cast<None*>(gg->data[x - 1][y]->head);
        return;
      }
    }
    if (f->father->father == NULL) return;
    c = dynamic_cast<None*>(dynamic_cast<Edit*>(f->father->father)->head);
  }
}
void Down() {
  for (None* c = cur; c->father->father != NULL;) {
    Edit *f = dynamic_cast<Edit*>(c->father);
    Object *g = f->father;
    if (g->getType() == FRAC && f == dynamic_cast<Frac*>(g)->num) {
      cur = dynamic_cast<None*>(dynamic_cast<Frac*>(g)->den->head);
      return;
    } else if (g->getType() == MATRIX) {
      Matrix *gg = dynamic_cast<Matrix*>(g);
      int x, y; gg->find(f, x, y);
      if (x < gg->n - 1) {
        cur = dynamic_cast<None*>(gg->data[x + 1][y]->head);
        return;
      }
    }
    if (f->father->father == NULL) return;
    c = dynamic_cast<None*>(dynamic_cast<Edit*>(f->father->father)->head);
  }
}
void Insert(Object *ne) {
  None* new_cur = new None(cur->father);
  if (cur->right != NULL) cur->right->left = new_cur;
  new_cur->right = cur->right;
  ne->left = cur;
  cur->right = ne;
  ne->right = new_cur;
  new_cur->left = ne;
  if (cur == dynamic_cast<Edit*>(cur->father)->tail)
    dynamic_cast<Edit*>(cur->father)->tail = new_cur;
  for (Object *o = cur; o != NULL; o = o->father) o->calcSize();
  Right();
}
void AddRow() {
  for (Object *e = cur; e->father != NULL; e = e->father)
    if (e->father->getType() == MATRIX) {
      cur = dynamic_cast<Matrix*>(e->father)->addRow(dynamic_cast<Edit*>(e));
      break;
    }
  for (Object *o = cur; o != NULL; o = o->father) o->calcSize();
}
void AddCol() {
  for (Object *e = cur; e->father != NULL; e = e->father)
    if (e->father->getType() == MATRIX) {
      cur = dynamic_cast<Matrix*>(e->father)->addCol(dynamic_cast<Edit*>(e));
      break;
    }
  for (Object *o = cur; o != NULL; o = o->father) o->calcSize();
}
Edit *root;
char op[100];
void Draw() {
  int n = root->height, m = root->width;
  s = new char*[n];
  for (int i = 0; i < n; ++i) {
    s[i] = new char[m + 1];
    for (int j = 0; j < m + 1; ++j)
      s[i][j] = ' ';
  }
  root->draw(root->middle, 0);
  for (int i = 0; i < n; ++i) {
    int y = m;
    while (s[i][y] == ' ') --y;
    s[i][y + 1] = '\0';
    puts(s[i]);
  }
}
int main() {
  root = new Edit(NULL);
  cur = dynamic_cast<None*>(root->head);
  while (scanf("%s", op) != EOF) {
    if (strlen(op) == 1) Insert(new Char(cur->father, op[0]));
    else if (!strcmp(op, "Fraction")) Insert(new Frac(cur->father));
    else if (!strcmp(op, "Matrix")) Insert(new Matrix(cur->father));
    else if (!strcmp(op, "Home")) Home();
    else if (!strcmp(op, "End")) End();
    else if (!strcmp(op, "Left")) Left();
    else if (!strcmp(op, "Right")) Right();
    else if (!strcmp(op, "Up")) Up();
    else if (!strcmp(op, "Down")) Down();
    else if (!strcmp(op, "AddRow")) AddRow();
    else if (!strcmp(op, "AddCol")) AddCol();
    //Draw();
  }
  Draw();
  return 0;
}
