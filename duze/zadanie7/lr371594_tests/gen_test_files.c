#include <stdio.h>
#include <stdlib.h>

#define MB 1048576  // bytes in a megabyte
int FILE_SIZE;  // megabytes

void create_test_file(char *filename, char (*generator)(int,int)) {
  // appending to file - it should not exist when running this program
  // prepare_tests.sh and prepare_with_time.sh delete them
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

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s MB_FILE_SIZE\n", argv[0]);
    return 1;
  }
  FILE_SIZE = atoi(argv[1]);
  if (FILE_SIZE <= 0) {
    printf("%s is not a valid file size.", argv[1]);
    return 2;
  }

  create_test_file("only_zeroes", &only_zeroes);
  create_test_file("sandwich", &sandwich);
  create_test_file("only_ones", &only_ones);
  return 0;
}
