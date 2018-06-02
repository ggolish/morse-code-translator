#ifndef MORSE_SCANNER_H
#define MORSE_SCANNER_H

typedef enum {
  TOKEN_EOF,
  TOKEN_DIGIT,
  TOKEN_LETTER,
  TOKEN_SPACE,
  TOKEN_UNKNOWN
} token_type_t;

typedef struct {
  token_type_t type;
  int line;
  char character;
} token_t;

extern void init_scanner(const char *plaintext);
extern token_t scan_token();

#endif /* end of include guard: MORSE_SCANNER_H */
