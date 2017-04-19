#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: ./test uid\n");
    return 1;
  }

  myps(atoi(argv[1]));
  return 0;
}
