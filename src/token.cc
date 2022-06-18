
#include "token.hpp"
#include "token_type.hpp"

std::string Token2String(TokenType type) {
  static const std::string strings[] = {
      "LEFT_PAREN", "RIGHT_PAREN",   "LEFT_BRACE", "RIGHT_BRACE", "COMMA",
      "DOT",        "MINUS",         "PLUS",       "SEMICOLON",   "SLASH",
      "STAR",       "BANG",          "BANG_EQUAL", "EQUAL",       "EQUAL_EQUAL",
      "GREATER",    "GREATER_EQUAL", "LESS",       "LESS_EQUAL",  "IDENTIFIER",
      "STRING",     "NUMBER",        "AND",        "CLASS",       "ELSE",
      "FALSE",      "FUN",           "FOR",        "IF",          "NIL",
      "OR",         "PRINT",         "RETURN",     "SUPER",       "THIS",
      "TRUE",       "VAR",           "WHILE",      "END_OF_FILE"};
  return strings[static_cast<int>(type)];
}

std::string Token::toString() const {
  std::string literal_text;

  switch (type) {

  case IDENTIFIER:
    literal_text = lexeme;
    break;

  case (TRUE):
    literal_text = "true";
    break;

  case (FALSE):
    literal_text = "false";
    break;

  case NUMBER:
    literal_text = std::to_string(std::any_cast<double>(literal));
    break;

  case STRING:
    literal_text = std::any_cast<std::string>(literal);
    break;

  default:
    literal_text = "nil";
    break;
  }

  return Token2String(type) + " " + lexeme + " " + literal_text;
}