#include <stdio.h>

#define MB 1048576
#define FILE_SIZE 128  // megabytes

void create_file(char *filename, char (*generator)(int,int)) {
  fclose(fopen(filename, "wb")); // clear the file if exists
  FILE *f = fopen(filename, "w+b");
  for (int i = 0; i < FILE_SIZE; ++i) {
    // append values to file megabyte by megabyte
    char t[MB];
    for (int j = 0; j < MB; ++j) {
      t[j] = (*generator)(i, j);
    }
    fwrite(t, 1, MB, f);
  }
  fclose(f);
}

char only_zeroes(int megabyte, int position) {
  return 0;
}

char sandwich(int megabyte, int position) {
  // first quarter and last quarter are ones
  // middle half is zeroes
  if (megabyte < FILE_SIZE / 4 || megabyte >= FILE_SIZE - FILE_SIZE / 4)
    return 1;
  return 0;
}

char only_ones(int megabyte, int position) {
  return 1;
}

int main() {
  create_file("only_zeroes", &only_zeroes);
  create_file("sandwich", &sandwich);
  create_file("only_ones", &only_ones);
  return 0;
}
