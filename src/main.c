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

static void print_counts(const Counts *c, const char *name) {
  printf("bytes: %lu \n", c->bytes);
  printf("lines: %lu \n", c->lines);
  printf("words: %lu \n", c->words);
  if (name) {
    printf("%s", name);
    putchar('\n');
  }
}
int main(int argc, char **argv) {
  Counts total = {0, 0, 0};
  int status = 0;
  if (argc < 2) {
    Counts c;
    count_stream(stdin, &c);
    print_counts(&c, NULL);
    return 0;
  }
  for (int i = 1; i < argc; i++) {
    FILE *file = fopen(argv[i], "rb");
    if (file == NULL) {
      perror(argv[i]);
      status = 1;
      continue;
    }

    Counts c;
    count_stream(file, &c);
    fclose(file);
    print_counts(&c, argv[i]);
    total.lines += c.lines;
    total.words += c.words;
    total.bytes += c.bytes;
  }
  if (argc > 2) {
    print_counts(&total, "total");
  }
  return status;
}
