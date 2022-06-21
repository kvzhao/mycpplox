#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "token.hpp"

class Scanner {
public:
  Scanner(std::string_view source);

  std::vector<Token> ScanTokens();

private:
  void ScanToken();
  void AddToken(TokenType type);
  void AddToken(TokenType tpye, std::any literal);

  char Peek();
  char PeekNext();
  char Advance();
  bool Match(char expected);

  void Number();
  void String();
  void Identifier();

  bool IsAtEnd();
  bool IsDigit(char c);
  bool IsAlpha(char c);
  bool IsAlphaNumeric(char c);

  static const std::unordered_map<std::string, TokenType> keywords;

  std::string_view source;
  std::vector<Token> tokens;

  int start = 0;
  int current = 0;
  int line = 1;
};