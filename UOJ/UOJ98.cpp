#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>

const char *TokenTypeName[] = { "RESERVED", "NAME", "LITER", "LBRACE", "RBRACE", "LPAREN", "RPAREN", "LBRACK", "RBRACK", "HASH", "SEMI", "COMMA", "INPUT", "OUTPUT", "NOT", "ADD", "SUB", "MUL", "DIV", "MOD", "LT", "LE", "GT", "GE", "EQ", "NE", "XOR", "AND", "OR", "ASSIGN", "EOF" };

const int TOKEN_RESERVED = 0;
const int TOKEN_NAME = 1;
const int TOKEN_LITER = 2;
const int TOKEN_LBRACE = 3;
const int TOKEN_RBRACE = 4;
const int TOKEN_LPAREN = 5;
const int TOKEN_RPAREN = 6;
const int TOKEN_LBRACK = 7;
const int TOKEN_RBRACK = 8;
const int TOKEN_HASH = 9;
const int TOKEN_SEMI = 10;
const int TOKEN_COMMA = 11;
const int TOKEN_INPUT = 12;
const int TOKEN_OUTPUT = 13;
const int TOKEN_NOT = 14;
const int TOKEN_ADD = 15;
const int TOKEN_SUB = 16;
const int TOKEN_MUL = 17;
const int TOKEN_DIV = 18;
const int TOKEN_MOD = 19;
const int TOKEN_LT = 20;
const int TOKEN_LE = 21;
const int TOKEN_GT = 22;
const int TOKEN_GE = 23;
const int TOKEN_EQ = 24;
const int TOKEN_NE = 25;
const int TOKEN_XOR = 26;
const int TOKEN_AND = 27;
const int TOKEN_OR = 28;
const int TOKEN_ASSIGN = 29;
const int TOKEN_EOF = 30;

std::set<std::string> reversed = {
  "int", "if", "else", "for", "while", "return", "cin", "cout", "endl"
};

std::map<std::string, int> signs = {
  {"{", TOKEN_LBRACE}, {"}", TOKEN_RBRACE},
  {"(", TOKEN_LPAREN}, {")", TOKEN_RPAREN},
  {"[", TOKEN_LBRACK}, {"]", TOKEN_RBRACK},
  {"#", TOKEN_HASH}, {";", TOKEN_SEMI}, {",", TOKEN_COMMA},
  {">>", TOKEN_INPUT}, {"<<", TOKEN_OUTPUT},
  {"!", TOKEN_NOT}, {"+", TOKEN_ADD}, {"-", TOKEN_SUB},
  {"*", TOKEN_MUL}, {"/", TOKEN_DIV}, {"%", TOKEN_MOD},
  {"<", TOKEN_LT}, {"<=", TOKEN_LE}, {">", TOKEN_GT},
  {">=", TOKEN_GE}, {"==", TOKEN_EQ}, {"!=", TOKEN_NE},
  {"^", TOKEN_XOR}, {"&&", TOKEN_AND}, {"||", TOKEN_OR}, {"=", TOKEN_ASSIGN}
};

struct Token{
  int type;
  std::string name;
  int value;
  Token(int t, std::string s) : type(t), name(s), value(0) {}
  Token(int t, int v) : type(t), name(""), value(v) {}
};

class Tokenizer{
 public:
  Tokenizer() {}
  Tokenizer(const std::string &content);
  void Tokenize(std::vector<Token> &tokens);
 private:
  inline void advance();
  void skip_spaces();
  int parseInt();
  std::string parseName();
  Token getToken();
  char current_char;
  std::string content;
  std::string::iterator p;
} tokenizer;

Tokenizer::Tokenizer(const std::string &content) : content(content) {
  p = this->content.begin();
  current_char = *p;
}

void Tokenizer::Tokenize(std::vector<Token> &tokens) {
  while (current_char != '\0')
    tokens.push_back(getToken());
}

inline void Tokenizer::advance() {
  if (p != content.end()) ++p;
  current_char = p == content.end() ? '\0' : *p;
}

void Tokenizer::skip_spaces() {
  while (isspace(current_char)) advance();
}

int Tokenizer::parseInt() {
  int ans = 0;
  while (isdigit(current_char)) {
    ans = ans * 10 + current_char - '0';
    advance();
  }
  return ans;
}

std::string Tokenizer::parseName() {
  std::string ans;
  while (isalnum(current_char) || current_char == '_') {
    ans += current_char;
    advance();
  }
  return ans;
}

Token Tokenizer::getToken() {
  while (current_char != '\0') {
    if (isspace(current_char)) {
      skip_spaces();
      continue;
    }
    if (isalpha(current_char) || current_char == '_') {
      std::string s = parseName();
      if (reversed.count(s))
        return Token(TOKEN_RESERVED, s);
      else
        return Token(TOKEN_NAME, s);
    } else if (isdigit(current_char)) {
      return Token(TOKEN_LITER, parseInt());
    } else {
      std::string s(1, current_char);
      advance();
      if (signs.count(s + current_char)) {
        s += current_char;
        advance();
      }
      if (signs.count(s))
        return Token(signs[s], s);
    }
  }
  return Token(TOKEN_EOF, "");
}

const int AST_VARIABLE = 0;
const int AST_FUNCTION_CALL = 1;
const int AST_INT_LITERAL = 2;
const int AST_FUNCTION_DECL = 3;
const int AST_VARIABLE_DECL = 4;
const int AST_VARIABLE_DECLS = 5;
const int AST_IF = 6;
const int AST_FOR = 7;
const int AST_WHILE = 8;
const int AST_RETURN = 9;
const int AST_BRACK = 10;
const int AST_CIN = 11;
const int AST_COUT = 12;
const int AST_ENDL = 13;
const int AST_NOT = 14;
const int AST_POS = 15;
const int AST_NEG = 16;
const int AST_ADD = 17;
const int AST_SUB = 18;
const int AST_MUL = 19;
const int AST_DIV = 20;
const int AST_MOD = 21;
const int AST_LT = 22;
const int AST_LE = 23;
const int AST_GT = 24;
const int AST_GE = 25;
const int AST_EQ = 26;
const int AST_NE = 27;
const int AST_XOR = 28;
const int AST_AND = 29;
const int AST_OR = 30;
const int AST_INPUT = 31;
const int AST_OUTPUT = 32;
const int AST_ASSIGN = 33;
const int AST_STATEMENTS = 34;
const int AST_PROGRAM = 35;
const int AST_NOP = 36;

const char *ASTTypeName[] = { "VARIABLE", "FUNCTION_CALL", "INT_LITERAL", "FUNCTION_DECL", "VARIABLE_DECL", "VARIABLE_DECLS", "IF", "FOR", "WHILE", "RETURN", "BRACK", "CIN", "COUT", "ENDL", "NOT", "POS", "NEG", "ADD", "SUB", "MUL", "DIV", "MOD", "LT", "LE", "GT", "GE", "EQ", "NE", "XOR", "AND", "OR", "INPUT", "OUTPUT", "ASSIGN", "STATEMENTS", "PROGRAM", "NOP" };

struct Linked{
  Linked(int x, Linked *next = NULL) : x(x), next(next) {}
  int x;
  Linked *next;
};

struct ASTNode{
  ASTNode(int ty) : type(ty), s0(NULL), s1(NULL), s2(NULL), s3(NULL), value(0), name(), children(), arr_lens(NULL) {}
  int type;
  ASTNode *s0, *s1, *s2, *s3;
  int value;
  std::string name;
  std::vector<std::string> params; // only for function
  std::vector<ASTNode*> children; // only for statements, vardecls, functioncall
  Linked *arr_lens;
};

class Parser{
 public:
  Parser() {}
  Parser(const std::vector<Token> &_tokens);
  ASTNode* parseProgram();
 private: 
  inline void eat(int ty);
  Token peek(int step = 1);
  ASTNode* parseFuntiondecl();
  ASTNode* parseVardecls();
  ASTNode* parseStatement();
  ASTNode* parseStatements();
  ASTNode* parseIf();
  ASTNode* parseFor();
  ASTNode* parseWhile();
  ASTNode* parseReturn();
  ASTNode* parseExpression();
  ASTNode* UNIT0_();
  ASTNode* UNIT0();
  ASTNode* UNIT1();
  ASTNode* UNIT2();
  ASTNode* UNIT3();
  ASTNode* UNIT4();
  ASTNode* UNIT5();
  ASTNode* UNIT6();
  ASTNode* UNIT7();
  ASTNode* UNIT8();
  ASTNode* UNIT9();
  std::vector<Token> tokens;
  std::vector<Token>::iterator cur;
} parser;

Parser::Parser(const std::vector<Token> &_tokens) : tokens(_tokens) {
  cur = tokens.begin();
}

Token Parser::peek(int step) {
  std::vector<Token>::iterator _tmp = cur;
  return *(_tmp + step);
}

inline void Parser::eat(int ty) {
  assert(cur->type == ty);
  ++cur;
}

#define eat_cur() eat(cur->type)
#define _eat(x) eat(TOKEN_##x)
#define _check(x) (cur->type == TOKEN_##x)

ASTNode* Parser::parseProgram() {
  // #include <iostream>
  _eat(HASH); _eat(NAME); _eat(LT); _eat(NAME); _eat(GT);
  // #include <cstdio>
  _eat(HASH); _eat(NAME); _eat(LT); _eat(NAME); _eat(GT);
  // using namespace std;
  _eat(NAME); _eat(NAME); _eat(NAME); _eat(SEMI);

  ASTNode* prog = new ASTNode(AST_PROGRAM);
  while (cur->type != TOKEN_EOF) {
    if (peek(2).type == TOKEN_LPAREN)
      prog->children.push_back(parseFuntiondecl());
    else {
      prog->children.push_back(parseVardecls());
      _eat(SEMI);
    }
  }

  _eat(EOF);
  return prog;
}

ASTNode* Parser::parseFuntiondecl() {
  _eat(RESERVED);
  ASTNode *func = new ASTNode(AST_FUNCTION_DECL);
  func->name = cur->name;
  _eat(NAME); _eat(LPAREN);
  while (cur->type != TOKEN_RPAREN) {
    _eat(RESERVED);
    func->params.push_back(cur->name);
    _eat(NAME);
    if (!_check(RPAREN))
      _eat(COMMA);
  }
  _eat(RPAREN);
  _eat(LBRACE);
  func->s0 = parseStatements();
  _eat(RBRACE);
  return func;
}

ASTNode* Parser::parseVardecls() {
  ASTNode *decls = new ASTNode(AST_VARIABLE_DECLS);
  _eat(RESERVED);
  while (true) {
    ASTNode *vardecl = new ASTNode(AST_VARIABLE_DECL);
    vardecl->name = cur->name;
    _eat(NAME);
    Linked **x = &vardecl->arr_lens;
    while (_check(LBRACK)) {
      _eat(LBRACK);
      *x = new Linked(cur->value);
      x = &(*x)->next;
      _eat(LITER);
      _eat(RBRACK);
    }
    decls->children.push_back(vardecl);
    if (!_check(COMMA))
      break;
    else
      _eat(COMMA);
  }
  return decls;
}

ASTNode* Parser::parseStatement() {
  ASTNode *ans;
  switch (cur->type) {
    case TOKEN_LBRACE:
      _eat(LBRACE);
      ans = parseStatements();
      _eat(RBRACE);
      break;
    case TOKEN_RESERVED:
      if (cur->name == "int") {
        ans = parseVardecls();
        _eat(SEMI);
        break;
      } else if (cur->name == "if") {
        ans = parseIf();
        break;
      } else if (cur->name == "for") {
        ans = parseFor();
        break;
      } else if (cur->name == "while") {
        ans = parseWhile();
        break;
      } else if (cur->name == "return") {
        ans = parseReturn();
        break;
      }
    case TOKEN_LITER:
    case TOKEN_NAME:
    case TOKEN_ADD:
    case TOKEN_SUB:
    case TOKEN_NOT:
    case TOKEN_LPAREN:
      ans = parseExpression();
      _eat(SEMI);
      break;
    default:
      ans = NULL;
  }
  return ans;
}

ASTNode* Parser::parseStatements() {
  ASTNode *stats = new ASTNode(AST_STATEMENTS);
  while (true) {
    ASTNode *stat = parseStatement();
    if (stat == NULL) break;
    stats->children.push_back(stat);
  }
  return stats;
}

ASTNode* Parser::parseIf() {
  ASTNode* ifstat = new ASTNode(AST_IF);
  _eat(RESERVED);
  _eat(LPAREN);
  ifstat->s0 = parseExpression();
  _eat(RPAREN);
  ifstat->s1 = parseStatement();
  if (_check(RESERVED) && cur->name == "else") {
    _eat(RESERVED);
    ifstat->s2 = parseStatement();
  } else
    ifstat->s2 = new ASTNode(AST_NOP);
  return ifstat;
}

ASTNode* Parser::parseFor() {
  ASTNode *forstat = new ASTNode(AST_FOR);
  _eat(RESERVED);
  _eat(LPAREN);
  if (_check(RESERVED) && cur->name == "int")
    forstat->s0 = parseVardecls();
  else if (_check(SEMI))
    forstat->s0 = new ASTNode(AST_NOP);
  else
    forstat->s0 = parseExpression();
  _eat(SEMI);
  if (cur->type != TOKEN_SEMI)
    forstat->s1 = parseExpression();
  else
    forstat->s1 = new ASTNode(AST_NOP);
  _eat(SEMI);
  if (_check(RESERVED) && cur->name == "int")
    forstat->s2 = parseVardecls();
  else if (_check(RPAREN))
    forstat->s2 = new ASTNode(AST_NOP);
  else
    forstat->s2 = parseExpression();
  _eat(RPAREN);
  forstat->s3 = parseStatement();
  return forstat;
}

ASTNode* Parser::parseWhile() {
  ASTNode* whilestat = new ASTNode(AST_WHILE);
  _eat(RESERVED);
  _eat(LPAREN);
  whilestat->s0 = parseExpression();
  _eat(RPAREN);
  whilestat->s1 = parseStatement();
  return whilestat;
}

ASTNode* Parser::parseReturn() {
  ASTNode *returnstat = new ASTNode(AST_RETURN);
  _eat(RESERVED);
  returnstat->s0 = parseExpression();
  _eat(SEMI);
  return returnstat;
}

ASTNode* Parser::parseExpression() {
  ASTNode* ans = UNIT9();
  while (_check(INPUT) || _check(OUTPUT)) {
    ASTNode *_tmp = new ASTNode(_check(INPUT) ? AST_INPUT : AST_OUTPUT);
    eat_cur();
    _tmp->s0 = ans;
    _tmp->s1 = UNIT9();
    ans = _tmp;
  }
  return ans;
}

ASTNode* Parser::UNIT0_() {
  ASTNode *ans;
  std::string name;
  switch (cur->type) {
    case TOKEN_LITER:
      ans = new ASTNode(AST_INT_LITERAL);
      ans->value = cur->value;
      _eat(LITER);
      break;
    case TOKEN_LPAREN:
      _eat(LPAREN);
      ans = parseExpression();
      _eat(RPAREN);
      break;
    case TOKEN_NAME:
      name = cur->name;
      _eat(NAME);
      if (_check(LPAREN)) {
        ans = new ASTNode(AST_FUNCTION_CALL);
        ans->name = name;
        _eat(LPAREN);
        while (cur->type != TOKEN_RPAREN) {
          ans->children.push_back(parseExpression());
          if (_check(COMMA))
            _eat(COMMA);
        }
        _eat(RPAREN);
      } else {
        ans = new ASTNode(AST_VARIABLE);
        ans->name = name;
      }
      break;
    case TOKEN_RESERVED:
      if (cur->name == "cin") {
        _eat(RESERVED);
        ans = new ASTNode(AST_CIN);
        break;
      } else if (cur->name == "cout") {
        _eat(RESERVED);
        ans = new ASTNode(AST_COUT);
        break;
      } else if (cur->name == "endl") {
        _eat(RESERVED);
        ans = new ASTNode(AST_ENDL);
        break;
      }
    default:
      assert(false);
  }
  return ans;
}

ASTNode* Parser::UNIT0() {
  ASTNode* ans = UNIT0_();
  while (_check(LBRACK)) {
    _eat(LBRACK);
    ASTNode *_tmp = new ASTNode(AST_BRACK);
    _tmp->s0 = ans;
    _tmp->s1 = parseExpression();
    _eat(RBRACK);
    ans = _tmp;
  }
  return ans;
}

ASTNode* Parser::UNIT1() {
  if (_check(ADD) || _check(SUB) || _check(NOT)) {
    ASTNode* ans = new ASTNode(
        _check(ADD) ? AST_POS : _check(SUB) ? AST_NEG : AST_NOT);
    eat_cur();
    ans->s0 = UNIT1();
    return ans;
  } else {
    return UNIT0();
  }
}

ASTNode* Parser::UNIT2() {
  ASTNode* ans = UNIT1();
  while (_check(MUL) || _check(DIV) || _check(MOD)) {
    ASTNode *_tmp = new ASTNode(
        _check(MUL) ? AST_MUL : _check(DIV) ? AST_DIV : AST_MOD);
    eat_cur();
    _tmp->s0 = ans;
    _tmp->s1 = UNIT1();
    ans = _tmp;
  }
  return ans;
}

ASTNode* Parser::UNIT3() {
  ASTNode* ans = UNIT2();
  while (_check(ADD) || _check(SUB)) {
    ASTNode *_tmp = new ASTNode(_check(ADD) ? AST_ADD : AST_SUB);
    eat_cur();
    _tmp->s0 = ans;
    _tmp->s1 = UNIT2();
    ans = _tmp;
  }
  return ans;
}

ASTNode* Parser::UNIT4() {
  ASTNode* ans = UNIT3();
  while (_check(LT) || _check(LE) || _check(GT) || _check(GE)) {
    ASTNode *_tmp = new ASTNode(
        _check(LT) ? AST_LT :
        _check(LE) ? AST_LE :
        _check(GT) ? AST_GT : AST_GE);
    eat_cur();
    _tmp->s0 = ans;
    _tmp->s1 = UNIT3();
    ans = _tmp;
  }
  return ans;
}

ASTNode* Parser::UNIT5() {
  ASTNode* ans = UNIT4();
  while (_check(EQ) || _check(NE)) {
    ASTNode *_tmp = new ASTNode(_check(EQ) ? AST_EQ : AST_NE);
    eat_cur();
    _tmp->s0 = ans;
    _tmp->s1 = UNIT4();
    ans = _tmp;
  }
  return ans;
}

#define ASSL1(n, x, pre)\
ASTNode* Parser::UNIT##n() {\
  ASTNode* ans = UNIT##pre();\
  while (_check(x)) {\
    ASTNode *_tmp = new ASTNode(AST_##x);\
    _eat(x);\
    _tmp->s0 = ans;\
    _tmp->s1 = UNIT##pre();\
    ans = _tmp;\
  }\
  return ans;\
}

ASSL1(6, XOR, 5);
ASSL1(7, AND, 6);
ASSL1(8, OR, 7);

#undef ASSL1

ASTNode* Parser::UNIT9() {
  ASTNode *ans = UNIT8();
  ASTNode *rightfa = NULL;
  while (_check(ASSIGN)) {
    _eat(ASSIGN);
    if (rightfa == NULL) {
      rightfa = new ASTNode(AST_ASSIGN);
      rightfa->s0 = ans;
      rightfa->s1 = UNIT8();
      ans = rightfa;
    } else {
      ASTNode *_tmp = new ASTNode(AST_ASSIGN);
      _tmp->s0 = rightfa->s1;
      _tmp->s1 = UNIT8();
      rightfa->s1 = _tmp;
      rightfa = _tmp;
    }
  }
  return ans;
}

#undef eat_cur
#undef _eat
#undef _check

std::vector<int> inputs;
std::vector<int>::iterator input_p;
std::vector<Token> ans;

void Input() {
  int n, x;
  scanf("%d", &n);
  while (n--) {
    scanf("%d", &x);
    inputs.push_back(x);
  }
  input_p = inputs.begin();
  static char s[1000000];
  fread(s, 1, 1000000, stdin);
  tokenizer = Tokenizer(std::string(s));
  tokenizer.Tokenize(ans);
}

void output(ASTNode *ans, int indent, bool first_indent = true) {
  if (ans == NULL) return;
  if (first_indent)
    for (int i = 0; i < indent; ++i) putchar(' ');
  printf("{%s %d", ASTTypeName[ans->type], ans->value);
  if (ans->name.length() > 0)
    printf(" \"%s\"", ans->name.c_str());
  if (ans->type == AST_VARIABLE_DECL)
    for (Linked *i = ans->arr_lens; i != NULL; i = i->next)
      printf("[%d]", i->x);
  bool f_ = true;
  if (ans->type == AST_FUNCTION_DECL) {
    if (f_) puts(""), f_ = false;
    for (int i = 0; i < indent + 1; ++i) putchar(' ');
    printf("params = {");
    bool first = true;
    for (auto s : ans->params) {
      if (first) first = false;
      else printf(", ");
      printf("\"%s\"", s.c_str());
    }
    printf("}\n");
  }
  if (ans->s0 != NULL) {
    if (f_) puts(""), f_ = false;
    for (int i = 0; i < indent + 1; ++i) putchar(' ');
    printf("s0=");
    output(ans->s0, indent + 4, false);
  }
  if (ans->s1 != NULL) {
    for (int i = 0; i < indent + 1; ++i) putchar(' ');
    printf("s1=");
    output(ans->s1, indent + 4, false);
  }
  if (ans->s2 != NULL) {
    for (int i = 0; i < indent + 1; ++i) putchar(' ');
    printf("s2=");
    output(ans->s2, indent + 4, false);
  }
  if (ans->s3 != NULL) {
    for (int i = 0; i < indent + 1; ++i) putchar(' ');
    printf("s3=");
    output(ans->s3, indent + 4, false);
  }
  if (ans->children.size() > 0) {
    if (f_) puts(""), f_ = false;
    for (int i = 0; i < indent + 1; ++i) putchar(' ');
    printf("children = {\n");
    for (auto it : ans->children)
      output(it, indent + 2);
    for (int i = 0; i < indent + 1; ++i) putchar(' ');
    printf("}\n");
  }
  if (!f_)
    for (int i = 0; i < indent; ++i) putchar(' ');
  printf("}\n");
}

struct Var{
  Var(int v = 0) : val(v), arr(NULL) {}
  int val;
  Var *arr;
};

void newVar(const Linked *s, Var &v) {
  if (s == NULL) {
    v.arr = NULL;
    v.val = 0;
  } else {
    v.arr = new Var[s->x];
    for (int i = 0; i < s->x; ++i)
      newVar(s->next, v.arr[i]);
  }
}

inline Var* newVar(const Linked *s) {
  Var *v = new Var();
  newVar(s, *v);
  return v;
}

typedef std::map<std::string, Var*> VarMap;

VarMap globalVarMap;
std::map<std::string, ASTNode*> functions;
bool returned;
int returned_value;

inline void declareVariable(VarMap &map, const std::string &name, int v) {
  assert(!map.count(name));
  map[name] = new Var(v);
}

inline void declareVariable(VarMap &map, const std::string &name, const Linked *arr_lens) {
  assert(!map.count(name));
  map[name] = newVar(arr_lens);
}

void declareVariables(VarMap &map, const ASTNode *vardecls) {
  for (const ASTNode *c : vardecls->children)
    declareVariable(map, c->name, c->arr_lens);
}

Var* findVar(std::vector<VarMap> &localVarMaps, std::string name) {
  int n = localVarMaps.size();
  for (int i = n - 1; i >= 0; --i)
    if (localVarMaps[i].count(name))
      return localVarMaps[i][name];
  return globalVarMap[name];
}

int execFunction(ASTNode* func, const std::vector<int> &paramValue);
int execExpression(ASTNode *expr, std::vector<VarMap> &localVarMaps);

Var* execVar(ASTNode *expr, std::vector<VarMap> &localVarMaps) {
  if (expr->type == AST_VARIABLE) return findVar(localVarMaps, expr->name);
  else /* expr->type == AST_BRACK */ {
    Var *left = execVar(expr->s0, localVarMaps);
    int right = execExpression(expr->s1, localVarMaps);
    return left->arr + right;
  }
}

int execExpression(ASTNode *expr, std::vector<VarMap> &localVarMaps) {
#define eval(x) execExpression(x, localVarMaps)
  int a, b;
  switch (expr->type) {
    case AST_INT_LITERAL:
      return expr->value;
    case AST_VARIABLE:
    case AST_BRACK:
      return execVar(expr, localVarMaps)->val;
    case AST_FUNCTION_CALL:
      {
        std::vector<int> paramValue;
        for (ASTNode *c : expr->children)
          paramValue.push_back(eval(c));
        if (expr->name == "putchar")
          return putchar(paramValue[0]);
        else
          return execFunction(functions[expr->name], paramValue);
      }
    case AST_CIN:
    case AST_COUT:
    case AST_ENDL:
      return 0;
    case AST_POS: return eval(expr->s0);
    case AST_NEG: return -eval(expr->s0);
    case AST_NOT: return !eval(expr->s0);
#define BinOp(type, f) case type: a = eval(expr->s0); b = eval(expr->s1); return f
    BinOp(AST_MUL, a * b);
    BinOp(AST_DIV, a / b);
    BinOp(AST_MOD, a % b);
    BinOp(AST_ADD, a + b);
    BinOp(AST_SUB, a - b);
    BinOp(AST_LT, a < b);
    BinOp(AST_LE, a <= b);
    BinOp(AST_GT, a > b);
    BinOp(AST_GE, a >= b);
    BinOp(AST_EQ, a == b);
    BinOp(AST_NE, a != b);
    BinOp(AST_XOR, (a != 0) ^ (b != 0));
    BinOp(AST_AND, (a != 0) && (b != 0));
    BinOp(AST_OR, (a != 0) || (b != 0));
    case AST_ASSIGN:
      return execVar(expr->s0, localVarMaps)->val = eval(expr->s1);
    case AST_INPUT:
      eval(expr->s0);
      execVar(expr->s1, localVarMaps)->val = *(input_p++);
      return 0;
    case AST_OUTPUT:
      eval(expr->s0);
      if (expr->s1->type == AST_ENDL) {
        puts("");
        return 0;
      } else {
        a = eval(expr->s1);
        printf("%d", a);
        return 0;
      }
    default:
      assert(false);
  }
}

void execStatements(ASTNode* stats, std::vector<VarMap> &localVarMaps);

void execStatement(ASTNode* stat, std::vector<VarMap> &localVarMaps) {
  if (stat->type == AST_NOP) return;
  if (stat->type == AST_VARIABLE_DECLS) {
    declareVariables(localVarMaps.back(), stat);
  } else if (stat->type == AST_STATEMENTS) {
    localVarMaps.push_back(VarMap());
    execStatements(stat, localVarMaps);
    localVarMaps.pop_back();
  } else if (stat->type == AST_IF) {
    if (execExpression(stat->s0, localVarMaps))
      execStatement(stat->s1, localVarMaps);
    else
      execStatement(stat->s2, localVarMaps);
  } else if (stat->type == AST_FOR) {
    localVarMaps.push_back(VarMap());
    execStatement(stat->s0, localVarMaps);
    while (stat->s1->type == AST_NOP || execExpression(stat->s1, localVarMaps)) {
      execStatement(stat->s3, localVarMaps);
      if (returned) {
        localVarMaps.pop_back();
        return;
      }
      execStatement(stat->s2, localVarMaps);
    }
    localVarMaps.pop_back();
  } else if (stat->type == AST_WHILE) {
    while (execExpression(stat->s0, localVarMaps)) {
      execStatement(stat->s1, localVarMaps);
      if (returned) return;
    }
  } else if (stat->type == AST_RETURN) {
    returned_value = execExpression(stat->s0, localVarMaps);
    returned = true;
  } else /* Expression */ {
    execExpression(stat, localVarMaps);
  }
}

void execStatements(ASTNode* stats, std::vector<VarMap> &localVarMaps) {
  for (ASTNode* c : stats->children) {
    execStatement(c, localVarMaps);
    if (returned) return;
  }
}

int execFunction(ASTNode* func, const std::vector<int> &paramValue) {
  assert(func->params.size() == paramValue.size());
  std::vector<VarMap> localVarMaps;
  localVarMaps.push_back(VarMap());
  for (int i = 0; i < paramValue.size(); ++i)
    declareVariable(localVarMaps[0], func->params[i], paramValue[i]);
  execStatements(func->s0, localVarMaps);
  if (returned) return returned = false, returned_value;
  else return 0;
}

void execProgram(ASTNode* prog) {
  for (ASTNode *c : prog->children) {
    if (c->type == AST_VARIABLE_DECLS)
      declareVariables(globalVarMap, c);
    else // c->type == AST_FUNCTION_DECL
      functions[c->name] = c;
  }
  assert(functions.count("main"));
  execFunction(functions["main"], std::vector<int>());
}

int main() {
  Input();
  parser = Parser(ans);
  ASTNode *ans = parser.parseProgram();
  execProgram(ans);
  return 0;
}
