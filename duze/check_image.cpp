#include <cstdio>

#define MB 1048576

void print_result(int result, int checked) {
  printf("%d MB checked: %d MB were only zeroes\n", checked, result);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s filename\n", argv[0]);
    return 1;
  }
  FILE *f = fopen(argv[1], "rb");
  char buf[MB];
  int result = 0, checked = 0;
  while (fread(buf, 1, MB, f) == MB) {
    bool only_zeroes = true;
    for (int i = 0; i < MB; ++i) {
      if (buf[i] != 0) {
        only_zeroes = false;
        break;
      }
    }
    if (only_zeroes)
      ++result;
    ++checked;
    if (checked % 100 == 0)
      print_result(result, checked);
  }
  print_result(result, checked);
  fclose(f);
  return 0;
}
