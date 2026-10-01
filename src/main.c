#include <stdio.h>

int main() {
  FILE *file = fopen("ex.txt", "r");
  if (file == NULL) {
    printf("Error with file opening");
    return 1;
  }

  char buffer[256];
  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    printf("%s", buffer);
  }

  fclose(file);
  return 0;
}
