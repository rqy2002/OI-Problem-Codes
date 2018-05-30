#include <cstdio>
#include <cstring>
int f[3], n;
char s[1000];
void outPut() {
  s[n] = '\0';
  printf("%s4\n", s);
}
int main() {
  scanf("%s", s);
  n = strlen(s);
  if (s[n - 1] == '4') {
    s[n - 1] = '\0';
    printf("%s1\n%s2\n%s3\n", s, s, s);
    return 0;
  }
  int a;
  while (--n)
    if (!f[a = s[n] - '1']) {
      outPut();
      f[a] = 1;
    }
  return 0;
}
