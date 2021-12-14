#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "token.hpp"

class Scanner {
public:

  Scanner(std::string_view source);

  std::vector<Token> scanTokens();

private:

  void scanToken();
  void addToken(TokenType type);
  void addToken(TokenType tpye, std::any literal);

  char peek();
  char peekNext();
  char advance();
  bool match(char expected);

  void number();
  void string();
  void identifier();

  bool isAtEnd();
  bool isDigit(char c);
  bool isAlpha(char c);
  bool isAlphaNumeric(char c);

  static const std::unordered_map<std::string, TokenType> keywords;

  std::string_view source;
  std::vector<Token> tokens;

  int start = 0;
  int current = 0;
  int line = 1;
};