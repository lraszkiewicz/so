#include <stdio.h>
#include <stdint.h>

extern uint8_t __executable_start;
extern uint8_t __etext;
extern void *__libc_stack_end;

void stack_show() {
  uint64_t x = 42;
  uint64_t *stack_ptr = &x;
  // while stack_ptr is not out of stack
  while (stack_ptr < (uint64_t *)__libc_stack_end) {
    // if stack_ptr points to something inside the executable text
    if ((uint8_t *)*stack_ptr >= &__executable_start &&
        (uint8_t *)*stack_ptr < &__etext) {
      uint8_t *call_ptr = (uint8_t *)(*stack_ptr) - 5;
      // check if call_ptr actually points to a call instruction
      if (call_ptr >= &__executable_start && *call_ptr == 0xe8) {
        int32_t *offset = (int32_t *)(call_ptr + 1);
        uint64_t func_addr = (uint64_t)call_ptr + 5 + *offset;
        printf("%016lx\n", func_addr);
      }
    }
    ++stack_ptr;
  }
  return;
}