#include "fileio.h"
#include "morse_translate.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 1024

static void translate_file(char *path);
static void repl();

int main(int argc, char *argv[])
{
  if(argc == 1) {
    repl();
  } else if(argc == 2) {
    translate_file(argv[1]);
  } else {
    fprintf(stderr, "Usage: %s [path]\n", argv[0]);
    exit(69);
  }
}

static void translate_file(char *path)
{
    char *plaintext = read_file(path);

    if(plaintext == NULL) {
      fprintf(stderr, "Error: %s\n", fileio_error());
      exit(69);
    }

    char *ciphertext = morse_translate(plaintext);

    if(ciphertext == NULL) {
      fprintf(stderr, "Morse code translation failed!\n");
      exit(69);
    }

    printf("%s\n", ciphertext);
    free(plaintext);
    morse_free();
}

static void repl()
{
  char buffer[MAX_LINE];
  for(;;) {
    printf("> ");
    if(fgets(buffer, sizeof(buffer), stdin) != NULL) {
      char *ciphertext = morse_translate(buffer);

      if(ciphertext == NULL) {
        fprintf(stderr, "Morse code translation failed!\n");
        continue;
      }

      printf("%s\n", ciphertext);
      morse_free();
    } else {
      printf("Goodbye.\n");
      exit(0);
    }
  }
}
