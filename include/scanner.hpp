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

  // movement operation
  char peek();
  char advance();
  bool isAtEnd();

  static const std::unordered_map<std::string, TokenType> keywords;

  std::string_view source;
  std::vector<Token> tokens;

  int start = 0;
  int current = 0;
  int line = 1;
};