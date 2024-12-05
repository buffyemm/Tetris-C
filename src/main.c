#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char *filename = "text.txt";
  char c;
  int x = 0;
  FILE *fp = fopen(filename, "r");
  if (fp) {
    while ((c = fgetc(fp)) != EOF) {
      putc(c, stdout);
      if (c == '.' || c == '!' || c == '?') {
        x++;
      }
    }
    printf("%d", x);
  }
}