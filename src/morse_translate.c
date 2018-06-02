#include "morse_translate.h"
#include "scanner.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define CHUNK 8

static char *ciphertext = NULL;
static int length = 0;
static int capacity = 0;

static bool freed = false;

static void dot();
static void dash();
static void intra_character_gap();
static void short_gap();
static void long_gap();

static void add_string(const char *s);
static void add_char(char c);

char *morse_translate(const char *plaintext)
{
  init_scanner(plaintext);

  if(freed == false) {
    morse_free();
  } else {
    freed = false;
  }

  for(;;) {
    token_t token = scan_token();
    switch(token.type) {
      case TOKEN_LETTER:
        short_gap();
        switch(tolower(token.character)) {
          case 'a':
            dot();
            dash();
            break;
          case 'b':
            dash();
            dot();
            dot();
            dot();
            break;
          case 'c':
            dash();
            dot();
            dash();
            dot();
            break;
          case 'd':
            dash();
            dot();
            dot();
            break;
          case 'e':
            dot();
            break;
          case 'f':
            dot();
            dot();
            dash();
            dot();
            break;
          case 'g':
            dash();
            dash();
            dot();
            break;
          case 'h':
            dot();
            dot();
            dot();
            dot();
            break;
          case 'i':
            dot();
            dot();
            break;
          case 'j':
            dot();
            dash();
            dash();
            dash();
            break;
          case 'k':
            dash();
            dot();
            dash();
            break;
          case 'l':
            dot();
            dash();
            dot();
            dot();
            break;
          case 'm':
            dash();
            dash();
            break;
          case 'n':
            dash();
            dot();
            break;
          case 'o':
            dash();
            dash();
            dash();
            break;
          case 'p':
            dot();
            dash();
            dash();
            dot();
            break;
          case 'q':
            dash();
            dash();
            dot();
            dash();
            break;
          case 'r':
            dot();
            dash();
            dot();
            break;
          case 's':
            dot();
            dot();
            dot();
            break;
          case 't':
            dash();
            break;
          case 'u':
            dot();
            dot();
            dash();
            break;
          case 'v':
            dot();
            dot();
            dot();
            dash();
            break;
          case 'w':
            dot();
            dash();
            dash();
            break;
          case 'x':
            dash();
            dot();
            dot();
            dash();
            break;
          case 'y':
            dash();
            dot();
            dash();
            dash();
            break;
          case 'z':
            dash();
            dash();
            dot();
            dot();
            break;
          default:
            break;
        }
        break;
      case TOKEN_SPACE:
        long_gap();
        break;
      case TOKEN_DIGIT:
        short_gap();
        switch(token.character) {
          case '0':
            dash();
            dash();
            dash();
            dash();
            dash();
            break;
          case '1':
            dot();
            dash();
            dash();
            dash();
            dash();
            break;
          case '2':
            dot();
            dot();
            dash();
            dash();
            dash();
            break;
          case '3':
            dot();
            dot();
            dot();
            dash();
            dash();
            break;
          case '4':
            dot();
            dot();
            dot();
            dot();
            dash();
            break;
          case '5':
            dot();
            dot();
            dot();
            dot();
            dot();
            break;
          case '6':
            dash();
            dot();
            dot();
            dot();
            dot();
            break;
          case '7':
            dash();
            dash();
            dot();
            dot();
            dot();
            break;
          case '8':
            dash();
            dash();
            dash();
            dot();
            dot();
            break;
          case '9':
            dash();
            dash();
            dash();
            dash();
            dot();
            break;
          default:
            break;
        }
        break;
      case TOKEN_UNKNOWN:
        break;
      case TOKEN_EOF:
        if(ciphertext) ciphertext[length] = '\0';
        return ciphertext;
    }
  }

  return NULL;
}

void morse_free()
{
  if(ciphertext == NULL) return;
  freed = true;
  free(ciphertext);
  ciphertext = NULL;
  length = capacity = 0;
}

static void dot()
{
  if(length >= 1 && ciphertext[length - 1] == '1') {
    intra_character_gap();
  }
  add_string("1");
}

static void dash()
{
  if(length >= 1 && ciphertext[length - 1] == '1') {
    intra_character_gap();
  }
  add_string("111");
}

static void intra_character_gap()
{
  add_string("0");
}

static void short_gap()
{
  if(length >= 1 && ciphertext[length - 1] == '1') add_string("000");
}

static void long_gap()
{
  if(length >= 3 && strncmp(ciphertext + length - 3, "000", 3) == 0) {
    add_string("0000");
  } else {
    add_string("0000000");
  }
}

static void add_string(const char *s)
{
  for(int i = 0; i < strlen(s); ++i) {
    add_char(s[i]);
  }
}

static void add_char(char c)
{
  if(length > capacity - 1) {
    capacity = (capacity == 0) ? CHUNK : capacity * 2;
    ciphertext = (char *)realloc(ciphertext, sizeof(char) * capacity * CHUNK);
  }
  ciphertext[length++] = c;
}
