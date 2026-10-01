#include <stdio.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "usage: %s file\n", argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[1], "rb");
  if (file == NULL) {
    perror(argv[1]);
    return 1;
  }

  unsigned long bytes = 0;
  int c;
  unsigned long lines = 0;

  while ((c = getc(file)) != EOF) {
    if (c == '\n') {
      lines++;
    }
    bytes++;
  }
  fclose(file);
  printf("%lu %s\n", bytes, argv[1]);
  printf("lines: %lu \n", lines);
  return 0;
}
