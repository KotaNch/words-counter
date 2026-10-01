#include <ctype.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  unsigned long lines;
  unsigned long words;
  unsigned long bytes;
} Counts;

static void count_stream(FILE *f, Counts *out) {
  int c, in_word = 0;
  memset(out, 0, sizeof *out);
  while ((c = getc(f)) != EOF) {
    out->bytes++;
    if (c == '\n') {
      out->lines++;
    }
    if (isspace(c)) {
      in_word = 0;
    } else if (!in_word) {
      in_word = 1;
      out->words++;
    }
  }
}
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

  Counts c;
  count_stream(file, &c);
  fclose(file);
  printf("bytes: %lu \n", c.bytes);
  printf("lines: %lu \n", c.lines);
  printf("words: %lu \n", c.words);
  return 0;
}
