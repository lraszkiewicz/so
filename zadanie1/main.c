#include <stdio.h>

#include "stack_show.c"

void f3() {
  stack_show();
}

void f2() {
  f3();
}

void f1() {
  f2();
}

int main() {
  f1();
  return 0;
}