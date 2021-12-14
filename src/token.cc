
#include "token.hpp"
#include "token_type.hpp"

std::string Token2String(TokenType type) {
  static const std::string strings[] = {
    "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE",
    "COMMA", "DOT", "MINUS", "PLUS", "SEMICOLON", "SLASH", "STAR",
    "BANG", "BANG_EQUAL",
    "EQUAL", "EQUAL_EQUAL",
    "GREATER", "GREATER_EQUAL",
    "LESS", "LESS_EQUAL",
    "IDENTIFIER", "STRING", "NUMBER",
    "AND", "CLASS", "ELSE", "FALSE", "FUN", "FOR", "IF", "NIL", "OR",
    "PRINT", "RETURN", "SUPER", "THIS", "TRUE", "VAR", "WHILE",
    "END_OF_FILE"
  };
  return strings[static_cast<int>(type)];
}

std::string Token::toString() const {
  std::string literal_text;

  switch(type) {
    default:
      literal_text = "nil";
      break;
  }

  return Token2String(type) + " " + lexeme + " " + literal_text;
}