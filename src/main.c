#include <ctype.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  unsigned long lines;
  unsigned long words;
  unsigned long bytes;
} Counts;

typedef struct {
  int lines, words, bytes;
} Flags;

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

static void print_counts(const Counts *c, const Flags *fl, const char *name) {
  if (fl->bytes)
    printf("bytes: %lu \n", c->bytes);
  if (fl->lines)
    printf("lines: %lu \n", c->lines);
  if (fl->words)
    printf("words: %lu \n", c->words);
  if (name) {
    printf("%s\n", name);
  }
}

int main(int argc, char **argv) {
  Flags fl = {0, 0, 0};
  int i = 1;
  for (; i < argc && argv[i][0] == '-' && argv[i][1]; i++) {
    for (const char *p = argv[i] + 1; *p; p++) {
      switch (*p) {
      case 'l':
        fl.lines = 1;
        break;
      case 'w':
        fl.words = 1;
        break;
      case 'c':
        fl.bytes = 1;
        break;
      default:
        fprintf(stderr, "usage: %s [-lwc] [file...]\n", argv[0]);
        return 1;
      }
    }
  }
  if (!fl.lines && !fl.words && !fl.bytes) {
    fl.lines = fl.words = fl.bytes = 1;
  }
  Counts total = {0, 0, 0};
  int status = 0;
  int files = 0;
  if (i >= argc) {
    Counts c;
    count_stream(stdin, &c);
    print_counts(&c, &fl, NULL);
    return 0;
  }
  for (; i < argc; i++) {
    FILE *file = fopen(argv[i], "rb");
    if (file == NULL) {
      perror(argv[i]);
      status = 1;
      continue;
    }

    Counts c;
    count_stream(file, &c);
    fclose(file);
    print_counts(&c, &fl, argv[i]);
    total.lines += c.lines;
    total.words += c.words;
    total.bytes += c.bytes;
    files++;
  }
  if (files > 1) {
    print_counts(&total, &fl, "total");
  }
  return status;
}
