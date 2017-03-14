#include <stdio.h>

#include "stack_show.c"

int f3() {
  printf("f3\n");
  stack_show();
  return 5;
}

int f2() {
  printf("f2\n");
  return f3() + 1;
}

int f1() {
  printf("f1\n");
  return f2() + 2;
}

int main() {
  printf("main\n");
  f1();
  return 0;
}