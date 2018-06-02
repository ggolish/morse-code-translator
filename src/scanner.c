#include "scanner.h"

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct {
  const char *current;
  int line;
} scanner_t;

static scanner_t scanner;

static bool finished();
static char advance();
static char peek();
static token_t make_token(token_type_t type);

void init_scanner(const char *plaintext)
{
  scanner.current = plaintext;
  scanner.line = 1;
}

token_t scan_token()
{
  char c = advance();

  if(finished()) return make_token(TOKEN_EOF);

  if(isdigit(c)) return make_token(TOKEN_DIGIT);
  if(isalpha(c)) return make_token(TOKEN_LETTER);

  switch(c) {
    case ' ':
    case '\t':
      while(peek() == ' ' || peek() == '\t') advance();
      return make_token(TOKEN_SPACE);
    case '\n':
      scanner.line++;
      return scan_token();
    default:
      return make_token(TOKEN_UNKNOWN);
  }
}

static bool finished()
{
  return *scanner.current == '\0';
}

static char advance()
{
  scanner.current++;
  return scanner.current[-1];
}

static char peek()
{
  if(finished()) return '\0';
  return *scanner.current;
}

static token_t make_token(token_type_t type)
{
  token_t token;
  token.type = type;
  token.character = scanner.current[-1];
  token.line = scanner.line;
  return token;
}
