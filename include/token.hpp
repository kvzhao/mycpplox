#pragma once

#include <string>
#include <vector>
#include <any>

#include "token_type.hpp"

class Token {

public:
  Token(TokenType type, std::string lexeme, std::any literal, int line)
    : type{type},
      lexeme{std::move(lexeme)},
      literal{std::move(literal)},
      line{line} 
  {};

  std::string toString() const;

  const TokenType type;
  const std::string lexeme;
  const std::any literal;
  const int line;
};