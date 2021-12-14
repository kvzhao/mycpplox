#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "token.hpp"

class Scanner {
public:

  Scanner(std::string_view source);


private:

  static const std::unordered_map<std::string, TokenType> keywords;

  std::string_view source;
  std::vector<Token> tokens;

  int start = 0;
  int current = 0;
  int line = 1;
};