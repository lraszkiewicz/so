#include <stdio.h>
#include <stdint.h>
#include <execinfo.h>

extern uint8_t __executable_start;
extern uint8_t __etext;
extern void *__libc_stack_end;

void stack_show() {
  printf("__executable_start: %016lx\n", (unsigned long)&__executable_start);
  printf("__etext:            %016lx\n", (unsigned long)&__etext);

  void *buffer[100];
  int bt = backtrace(buffer, 100);
  printf("backtrace() returned %d addresses\n", bt);
  for (int i = 0; i < bt; ++i)
    printf("%016lx\n", (unsigned long)buffer[i]);
  backtrace_symbols_fd(buffer, bt, 0);

  unsigned long x = 42;
  unsigned long *stack_ptr = &x;
  while (stack_ptr < (unsigned long *)__libc_stack_end) {
    if ((uint8_t *)*stack_ptr >= &__executable_start &&
        (uint8_t *)*stack_ptr < &__etext) {
      uint8_t *a = (uint8_t *)(*stack_ptr) - 5;
      if (a >= &__executable_start && *a == 0xe8) {
        printf("*stack_ptr:         %016lx\n", (unsigned long)*stack_ptr);
        printf("a:                  %016lx\n", (unsigned long)a);
        uint32_t *b = a + 1;
        printf("b:                  %08x\n", *b);
        uint32_t *c = a + 5 + *b;
        printf("b:                  %08x\n", c);

      }
    }
    ++stack_ptr;
  }

  return;
}